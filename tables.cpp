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
    for (Customer &c : table) {
        indexNationkey.insert(c.c_nationkey, c);
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

void OrdersTable::buildSecondaryIndexes() {
    for (Orders &o : table) {
        indexCustkey.insert(o.o_custkey, o);
    }
}

void LineitemTable::fromStream(std::ifstream &fin) {
    std::string line;
    while (getline(fin, line)) {
        table.emplace_back(line);
    }
}

void LineitemTable::buildSecondaryIndexes() {
    for (Lineitem &l : table) {
        indexOrderkey.insert(l.l_orderkey, l);
    }
}

void PartTable::fromStream(std::ifstream &fin) {
    std::string line;
    while (getline(fin, line)) {
        table.emplace_back(line);
    }
}
