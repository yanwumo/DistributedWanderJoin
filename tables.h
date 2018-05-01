//
// Created by yanwumo on 4/28/18.
//

#ifndef DISTRIBUTEDWANDERJOIN_TABLES_H
#define DISTRIBUTEDWANDERJOIN_TABLES_H

#include <vector>
#include <unordered_map>
#include <fstream>
#include "entries.h"
#include "index.h"

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
    std::unordered_map<uint32_t, Customer *> primaryKey;
    SecondaryIndex<uint32_t, Customer> indexNationkey;
    SecondaryIndex<std::string, Customer> indexMktsegment;
    void fromStream(std::ifstream &fin);
    void buildPrimaryKey();
    void buildSecondaryIndexes();
};

class OrdersTable {
public:
    std::vector<Orders> table;
    std::unordered_map<uint32_t, Orders *> primaryKey;
    SecondaryIndex<uint32_t, Orders> indexCustkey;
    void fromStream(std::ifstream &fin);
    void buildPrimaryKey();
    void buildSecondaryIndexes();
};

class LineitemTable {
public:
    std::vector<Lineitem> table;
    SecondaryIndex<uint32_t, Lineitem> indexOrderkey;
    void fromStream(std::ifstream &fin);
    void buildSecondaryIndexes();
};

class PartTable {
public:
    std::vector<Part> table;
    void fromStream(std::ifstream &fin);
};

#endif //DISTRIBUTEDWANDERJOIN_TABLES_H
