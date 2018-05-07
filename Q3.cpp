//
// Created by Ben on 2018/4/15.
//

#include <iostream>
#include "Q3.h"
#include "tables.h"
#include "mpi.h"

Q3::Q3(size_t rank, size_t size) : rank(rank), size(size) {
    auto seed = std::chrono::system_clock::now().time_since_epoch().count();
    randomNumberGenerator.seed(static_cast<unsigned int>(seed));
}

std::ifstream Q3::openTableFile(const std::string &s) {
    std::ifstream fin;
    fin.open(s, std::ifstream::in);
    if(!fin.good()) {
        std::cout << std::endl;
        std::cerr << "TPC-H data set missing. Put data files into data/*.tbl." << std::endl;
        exit(-1);
    }
    return fin;
}

void Q3::closeTableFile(std::ifstream &fin) {
    fin.close();
}

void Q3::execute() {
    std::cout << "TPC-H Q3" << std::endl;

    /*
     * SELECT ONLINE
     * SUM(l_extendedprice * (1 - l_discount)), COUNT(*)
     * FROM customer, orders, lineitem
     * WHERE c_mktsegment = 'BUILDING' AND c_custkey = o_custkey
     * AND l_orderkey = o_orderkey
     * WITHINTIME 20 CONFIDENCE 95 REPORTINTERVAL 1
     */

    std::ifstream fin;
    std::cout << "Reading customer.tbl..." << std::flush;
    fin = openTableFile("../data/customer.tbl");
    customerTable.fromStream(fin);
    closeTableFile(fin);
    std::cout << "done" << std::endl;
    std::cout << "Building indexes..." << std::flush;
    customerTable.buildPrimaryKey();
    customerTable.buildSecondaryIndexes();
    std::cout << "done" << std::endl;

    std::cout << "Reading orders.tbl..." << std::flush;
    fin = openTableFile("../data/orders.tbl");
    ordersTable.fromStream(fin);
    closeTableFile(fin);
    std::cout << "done" << std::endl;
    std::cout << "Building indexes..." << std::flush;
    ordersTable.buildPrimaryKey();
    ordersTable.buildSecondaryIndexes();
    std::cout << "done" << std::endl;

    std::cout << "Reading lineitem.tbl..." << std::flush;
    fin = openTableFile("../data/lineitem.tbl");
    lineitemTable.fromStream(fin);
    closeTableFile(fin);
    std::cout << "done" << std::endl;
    std::cout << "Building indexes..." << std::flush;
    lineitemTable.buildSecondaryIndexes();
    std::cout << "done" << std::endl;


    query(0.1, 20);
}

double Q3::singleStepSamplingOverAllTables() {
    // The current best order is {0, 1, 2}
    uint32_t buf[2 * size];

    // Sample from customer - orders - lineitem
    Customer *c = customerTable.sampleFromAllEntries();
    size_t cCount = customerTable.size() * size;
    MPI_Allgather(&c->c_custkey, 1, MPI_UINT32_T, buf, 1, MPI_UINT32_T, MPI_COMM_WORLD);

    uint32_t selectedCustkey = buf[getRandomNumberOfSize(size)];
    Orders *o = ordersTable.indexCustkey.sampleFromEntriesWhoseKeyEqualTo(selectedCustkey);
    size_t oCount = ordersTable.indexCustkey.getNumberOfEntriesWhoseKeyEqualTo(selectedCustkey);
    uint32_t tmp[2];
    tmp[0] = o != nullptr ? o->o_orderkey : UINT32_MAX;
    tmp[1] = static_cast<uint32_t>(oCount);
    MPI_Allgather(tmp, 2, MPI_UINT32_T, buf, 2, MPI_UINT32_T, MPI_COMM_WORLD);

    size_t index = getRandomNumberOfSize(size);
    uint32_t selectedOrderkey = buf[2 * index];
    size_t selectedOCount = buf[2 * index + 1] * size;
    Lineitem *l = lineitemTable.indexOrderkey.sampleFromEntriesWhoseKeyEqualTo(selectedOrderkey);
    size_t lCount = lineitemTable.indexOrderkey.getNumberOfEntriesWhoseKeyEqualTo(selectedOrderkey) * size;
    if (l == nullptr) return 0.0;

    return cCount * selectedOCount * lCount * l->l_extendedprice * (1 - l->l_discount);
}

void Q3::query(const double &stepTime, const double &maxTime) {
    std::chrono::steady_clock::time_point startTime = std::chrono::steady_clock::now();
    std::chrono::steady_clock::time_point stepStartTime = std::chrono::steady_clock::now();
    std::chrono::steady_clock::time_point currentTime = std::chrono::steady_clock::now();
    size_t numSamples = 0;
    double sum = 0.0;
    double sumSquared = 0.0;
    double average = 0.0;
    size_t decisionStep = 0;
    std::chrono::duration<double> timeSinceStart;
    do {
        numSamples += size;
        double singleStepResult = singleStepSamplingOverAllTables();
        double buf[size];
        MPI_Gather(&singleStepResult, 1, MPI_DOUBLE, buf, 1, MPI_DOUBLE, 0, MPI_COMM_WORLD);

        for (int i = 0; i < size; i++) {
            sum += buf[i];
            sumSquared += buf[i] * buf[i];
        }
        average = sum / numSamples;

        std::chrono::duration<double> timeSinceStep = currentTime - stepStartTime;
        if (rank == 0 && timeSinceStep.count() > stepTime) {
            double ci = confidenceInterval(sumSquared, sum, average, numSamples, 0.95);
            double displayTime = static_cast<int>(timeSinceStart.count() / stepTime) * stepTime;
            std::cout << "Time: " << displayTime << "s" << " Result: " << average << "  Confidence interval: " << ci << std::endl;
            stepStartTime = std::chrono::steady_clock::now();
        }
        currentTime = std::chrono::steady_clock::now();
        timeSinceStart = currentTime - startTime;
    } while (timeSinceStart.count() < maxTime);
}
