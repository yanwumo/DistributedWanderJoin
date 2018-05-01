//
// Created by yanwumo on 4/28/18.
//

#include "tables.h"

void CustomerTable::buildPrimaryKey() {
    indexCustkey.reserve(table.size());
    for (Customer &c : table) {
        indexCustkey.insert(c.c_custkey, c);
    }
}

void CustomerTable::buildSecondaryIndexes() {
    indexNationkey.reserve(table.size());
    indexMktsegment.reserve(table.size());
    for (Customer &c : table) {
        indexNationkey.insert(c.c_nationkey, c);
        indexMktsegment.insert(c.c_mktsegment, c);
    }
}

void OrdersTable::buildPrimaryKey() {
    indexOrderkey.reserve(table.size());
    for (Orders &c : table) {
        indexOrderkey.insert(c.o_orderkey, c);
    }
}

void OrdersTable::buildSecondaryIndexes() {
    indexCustkey.reserve(table.size());
    for (Orders &o : table) {
        indexCustkey.insert(o.o_custkey, o);
    }
}

void LineitemTable::buildSecondaryIndexes() {
    for (Lineitem &l : table) {
        indexOrderkey.insert(l.l_orderkey, l);
    }
}
