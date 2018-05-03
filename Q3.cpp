//
// Created by Ben on 2018/4/15.
//

#include <iostream>
#include "Q3.h"
#include "tables.h"

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

std::pair<bool, double> Q3::singleStepSamplingOverAllTables() {
    // The current best order is {0, 1, 2}

    // Sample from customer - orders - lineitem
    Customer *c = customerTable.sampleFromAllEntries();
    size_t cCount = customerTable.size();
    Orders *o = ordersTable.indexCustkey.sampleFromEntriesWhoseKeyEqualTo(c->c_custkey);
    size_t oCount = ordersTable.indexCustkey.getNumberOfEntriesWhoseKeyEqualTo(c->c_custkey);
    if (o == nullptr) return {false, 0.0};
    Lineitem *l = lineitemTable.indexOrderkey.sampleFromEntriesWhoseKeyEqualTo(o->o_orderkey);
    size_t lCount = lineitemTable.indexOrderkey.getNumberOfEntriesWhoseKeyEqualTo(o->o_orderkey);
    if (l == nullptr) return {false, 0.0};

    return {true, cCount * oCount * lCount * l->l_extendedprice * (1 - l->l_discount)};
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
    do {
        numSamples++;
        auto pair = singleStepSamplingOverAllTables();
        double singleStepResult = pair.second;
        sum += singleStepResult;
        average = sum / numSamples;
        sumSquared += singleStepResult * singleStepResult;

        if (std::chrono::duration_cast<double>(currentTime - stepStartTime) > stepTime) {
            double ci = confidenceInterval(sumSquared, sum, average, numSamples, 0.95);
            std::cout << "Confidence interval: " << ci << std::endl;
            stepStartTime = std::chrono::steady_clock::now();
        }
        currentTime = std::chrono::steady_clock::now();
    } while (std::chrono::duration_cast<double>(currentTime - startTime) < maxTime);
}
