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
}
