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

void OrdersTable::fromStream(std::ifstream &fin) {
    std::string line;
    while (getline(fin, line)) {
        table.emplace_back(line);
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
