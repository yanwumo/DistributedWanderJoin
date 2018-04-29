//
// Created by Ben on 2018/4/14.
//

#ifndef DISTRIBUTEDWANDERJOIN_ENTRIES_H
#define DISTRIBUTEDWANDERJOIN_ENTRIES_H

#include <cstring>
#include <cstdint>
#include <string>
#include <sstream>
#include "date.h"

class Region {
public:
    uint32_t r_regionkey;
    char r_name[26];
    char r_comment[153];

    explicit Region(const std::string &s);
    Region &operator=(const Region &t);
};

class Nation {
public:
    uint32_t n_nationkey;
    char n_name[25];
    uint32_t n_regionkey;
    char n_comment[152];

    explicit Nation(const std::string &s);
    Nation &operator=(const Nation &t);
};

class Supplier {
public:
    uint32_t s_suppkey;
    char s_name[26];
    char s_address[41];
    uint32_t s_nationkey;
    char s_phone[16];
    double s_acctbal;
    char s_comment[102];

    explicit Supplier(const std::string &s);
    Supplier &operator=(const Supplier &t);
};

class Partsupp {
public:
    uint32_t ps_partkey;
    uint32_t ps_suppkey;
    int32_t ps_availqty;
    double ps_supplycost;
    char ps_comment[200];

    explicit Partsupp(const std::string &s);
    Partsupp &operator=(const Partsupp &t);
};

class Customer {
public:
    uint32_t c_custkey;
    char c_name[26];
    char c_address[41];
    uint32_t c_nationkey;
    char c_phone[16];
    double c_acctbal;
    char c_mktsegment[11];
    char c_comment[118];

    explicit Customer(const std::string &s);
    Customer &operator=(const Customer &t);
};

class Orders {
public:
    uint32_t o_orderkey;
    uint32_t o_custkey;
    char o_orderstatus;
    double o_totalprice;
    date_t o_orderdate;
    char o_orderpriority[16];
    char o_clerk[16];
    int32_t o_shippriority;
    char o_comment[80];

    explicit Orders(const std::string &s);
    Orders &operator=(const Orders &t);
};

class Lineitem {
public:
    uint32_t l_orderkey;
    uint32_t l_partkey;
    uint32_t l_suppkey;
    int32_t l_linenumber;
    double l_quantity;
    double l_extendedprice;
    double l_discount;
    double l_tax;
    char l_returnflag;
    char l_linestatus;
    date_t l_shipdate;
    date_t l_commitdate;
    date_t l_receiptdate;
    char l_shipinstruct[26];
    char l_shipmode[11];
    char l_comment[45];

    explicit Lineitem(const std::string &s);
    Lineitem &operator=(const Lineitem &t);
};

class Part {
public:
    uint32_t p_partkey;
    char p_name[56];
    char p_mfgr[26];
    char p_brand[11];
    char p_type[25];
    int32_t p_size;
    char p_container[11];
    double p_retailprice;
    char p_comment[24];

    explicit Part(const std::string &s);
    Part &operator=(const Part &t);
};

#endif //DISTRIBUTEDWANDERJOIN_ENTRIES_H
