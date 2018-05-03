//
// Created by yanwumo on 4/28/18.
//

#ifndef DISTRIBUTEDWANDERJOIN_TABLES_H
#define DISTRIBUTEDWANDERJOIN_TABLES_H

#include <vector>
#include <unordered_map>
#include <fstream>
#include <random>
#include <chrono>
#include "entries.h"
#include "index.h"

template <class T>
class BaseTable {
private:
    std::mt19937 randomNumberGenerator;

protected:
    std::vector<T> table;

public:
    BaseTable() {
        auto seed = std::chrono::system_clock::now().time_since_epoch().count();
        randomNumberGenerator.seed(static_cast<unsigned int>(seed));
    }

    size_t size() {
        return table.size();
    }

    size_t getRandomNumberOfSize(const size_t &size) {
        std::uniform_int_distribution<size_t> distribution(0, size - 1);
        return distribution(randomNumberGenerator);
    }

    void fromStream(std::ifstream &fin) {
        std::string line;
        while (getline(fin, line)) {
            table.emplace_back(line);
        }
    }

    T *sampleFromAllEntries() {
        return &table[getRandomNumberOfSize(table.size())];
    }
};

class RegionTable : public BaseTable<Region> {
};

class NationTable : public BaseTable<Nation> {
};

class SupplierTable : public BaseTable<Supplier> {
};

class PartsuppTable : public BaseTable<Partsupp> {
};

class CustomerTable : public BaseTable<Customer> {
public:
    PrimaryKey<uint32_t, Customer> indexCustkey;
    SecondaryIndex<uint32_t, Customer> indexNationkey;
    SecondaryIndex<std::string, Customer> indexMktsegment;
    void buildPrimaryKey();
    void buildSecondaryIndexes();
};

class OrdersTable : public BaseTable<Orders> {
public:
    PrimaryKey<uint32_t, Orders> indexOrderkey;
    SecondaryIndex<uint32_t, Orders> indexCustkey;
    void buildPrimaryKey();
    void buildSecondaryIndexes();
};

class LineitemTable : public BaseTable<Lineitem> {
public:
    SecondaryIndex<uint32_t, Lineitem> indexOrderkey;
    void buildSecondaryIndexes();
};

class PartTable : public BaseTable<Part> {
};

#endif //DISTRIBUTEDWANDERJOIN_TABLES_H
