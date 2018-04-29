//
// Created by Ben on 2018/4/15.
//

#include <iostream>
#include "Q3.h"

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

void Q3::readCustomer(std::ifstream &fin) {
    std::string line;
    while (getline(fin, line)) {
        customerTable.emplace_back(line);
    }
}

void Q3::readOrders(std::ifstream &fin) {
    std::string line;
    while (getline(fin, line)) {
        ordersTable.emplace_back(line);
    }
}

void Q3::readLineitem(std::ifstream &fin) {
    std::string line;
    while (getline(fin, line)) {
        lineitemTable.emplace_back(line);
    }
}

void Q3::closeTableFile(std::ifstream &fin) {
    fin.close();
}

void Q3::execute() {
    std::cout << "TPC-H Q3" << std::endl;

    std::ifstream fin;
    std::cout << "Reading customer.tbl...";
    fin = openTableFile("../data/customer.tbl");
    readCustomer(fin);
    closeTableFile(fin);
    std::cout << "done" << std::endl;

    std::cout << "Reading orders.tbl...";
    fin = openTableFile("../data/orders.tbl");
    readOrders(fin);
    closeTableFile(fin);
    std::cout << "done" << std::endl;

    std::cout << "Reading lineitem.tbl...";
    fin = openTableFile("../data/lineitem.tbl");
    readLineitem(fin);
    closeTableFile(fin);
    std::cout << "done" << std::endl;
}
