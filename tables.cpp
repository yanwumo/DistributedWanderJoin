//
// Created by yanwumo on 4/28/18.
//

#include "tables.h"

void RegionTable::fromStream(std::ifstream &fin) {
    std::string line;
    while (getline(fin, line)) {
        table.emplace_back(line);
    }
}

void NationTable::fromStream(std::ifstream &fin) {
    std::string line;
    while (getline(fin, line)) {
        table.emplace_back(line);
    }
}

void SupplierTable::fromStream(std::ifstream &fin) {
    std::string line;
    while (getline(fin, line)) {
        table.emplace_back(line);
    }
}

void PartsuppTable::fromStream(std::ifstream &fin) {
    std::string line;
    while (getline(fin, line)) {
        table.emplace_back(line);
    }
}

void CustomerTable::fromStream(std::ifstream &fin) {
    std::string line;
    while (getline(fin, line)) {
        table.emplace_back(line);
    }
}

void CustomerTable::buildPrimaryKey() {
    primaryKey.reserve(table.size());
    for (Customer &c : table) {
        primaryKey.insert(std::make_pair(c.c_custkey, &c));
    }
}

void CustomerTable::buildSecondaryIndexes() {
    for (const Customer &c : table) {
        indexMktsegment.insert(c.c_mktsegment, c);
    }
}

void OrdersTable::fromStream(std::ifstream &fin) {
    std::string line;
    while (getline(fin, line)) {
        table.emplace_back(line);
    }
}

void OrdersTable::buildPrimaryKey() {
    primaryKey.reserve(table.size());
    for (Orders &c : table) {
        primaryKey.insert(std::make_pair(c.o_orderkey, &c));
    }
}

void LineitemTable::fromStream(std::ifstream &fin) {
    std::string line;
    while (getline(fin, line)) {
        table.emplace_back(line);
    }
}

void PartTable::fromStream(std::ifstream &fin) {
    std::string line;
    while (getline(fin, line)) {
        table.emplace_back(line);
    }
}
