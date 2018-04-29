//
// Created by yanwumo on 4/28/18.
//

#ifndef DISTRIBUTEDWANDERJOIN_TABLES_H
#define DISTRIBUTEDWANDERJOIN_TABLES_H

#include <vector>
#include <fstream>
#include "entries.h"

class RegionTable {
public:
    std::vector<Region> table;
    void fromStream(std::ifstream &fin);
};

class NationTable {
public:
    std::vector<Nation> table;
    void fromStream(std::ifstream &fin);
};

class SupplierTable {
public:
    std::vector<Supplier> table;
    void fromStream(std::ifstream &fin);
};

class PartsuppTable {
public:
    std::vector<Partsupp> table;
    void fromStream(std::ifstream &fin);
};

class CustomerTable {
public:
    std::vector<Customer> table;
    void fromStream(std::ifstream &fin);
};

class OrdersTable {
public:
    std::vector<Orders> table;
    void fromStream(std::ifstream &fin);
};

class LineitemTable {
public:
    std::vector<Lineitem> table;
    void fromStream(std::ifstream &fin);
};

class PartTable {
public:
    std::vector<Part> table;
    void fromStream(std::ifstream &fin);
};

#endif //DISTRIBUTEDWANDERJOIN_TABLES_H
