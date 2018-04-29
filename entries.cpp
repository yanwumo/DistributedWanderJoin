//
// Created by Ben on 2018/4/15.
//

#include "entries.h"

Region::Region(const std::string &s) : r_name(""), r_comment("") {
    std::stringstream stream(s);
    std::string item;
    std::getline(stream, item, '|');
    r_regionkey = static_cast<uint32_t>(std::stoull(item));
    std::getline(stream, item, '|');
    std::strncat(r_name, item.c_str(), sizeof(r_name) - 1);
    std::getline(stream, item, '|');
    std::strncat(r_comment, item.c_str(), sizeof(r_comment) - 1);
}

Region &Region::operator=(const Region &t) {
    if (this == &t)
        return *this;
    std::strncpy(r_name, t.r_name, sizeof(r_name));
    std::strncpy(r_comment, t.r_comment, sizeof(r_comment));
    r_regionkey = t.r_regionkey;
    return *this;
}

Nation::Nation(const std::string &s) : n_name(""), n_comment("") {
    std::stringstream stream(s);
    std::string item;
    std::getline(stream, item, '|');
    n_nationkey = static_cast<uint32_t>(std::stoull(item));
    std::getline(stream, item, '|');
    std::strncat(n_name, item.c_str(), sizeof(n_name) - 1);
    std::getline(stream, item, '|');
    n_regionkey = static_cast<uint32_t>(std::stoull(item));
    std::getline(stream, item, '|');
    std::strncat(n_comment, item.c_str(), sizeof(n_comment) - 1);
}

Nation &Nation::operator=(const Nation &t) {
    if (this == &t)
        return *this;
    n_nationkey = t.n_nationkey;
    std::strncpy(n_name, t.n_name, sizeof(n_name));
    n_regionkey = t.n_regionkey;
    std::strncpy(n_comment, t.n_comment, sizeof(n_comment));
    return *this;
}

Supplier::Supplier(const std::string &s) : s_name(""), s_address(""), s_phone(""), s_comment("") {
    std::stringstream stream(s);
    std::string item;
    std::getline(stream, item, '|');
    s_suppkey = static_cast<uint32_t>(std::stoull(item));
    std::getline(stream, item, '|');
    std::strncat(s_name, item.c_str(), sizeof(s_name) - 1);
    std::getline(stream, item, '|');
    std::strncat(s_address, item.c_str(), sizeof(s_address) - 1);
    std::getline(stream, item, '|');
    s_nationkey = static_cast<uint32_t>(std::stoull(item));
    std::getline(stream, item, '|');
    std::strncat(s_phone, item.c_str(), sizeof(s_phone) - 1);
    std::getline(stream, item, '|');
    s_acctbal = std::stod(item);
    std::getline(stream, item, '|');
    std::strncat(s_comment, item.c_str(), sizeof(s_comment) - 1);
}

Supplier &Supplier::operator=(const Supplier &t) {
    if (&t == this)
        return *this;
    s_suppkey = t.s_suppkey;
    std::strncpy(s_name, t.s_name, 26);
    std::strncpy(s_address, t.s_address, 41);
    s_nationkey = t.s_nationkey;
    std::strncpy(s_phone, t.s_phone, 16);
    s_acctbal = t.s_acctbal;
    std::strncpy(s_comment, t.s_comment, 102);
    return *this;
}

Partsupp::Partsupp(const std::string &s) : ps_comment("") {
    std::stringstream stream(s);
    std::string item;
    std::getline(stream, item, '|');
    ps_partkey = static_cast<uint32_t>(std::stoull(item));
    std::getline(stream, item, '|');
    ps_suppkey = static_cast<uint32_t>(std::stoull(item));
    std::getline(stream, item, '|');
    ps_availqty = std::stoi(item);
    std::getline(stream, item, '|');
    ps_supplycost = std::stod(item);
    std::getline(stream, item, '|');
    std::strncat(ps_comment, item.c_str(), sizeof(ps_comment) - 1);
}

Partsupp &Partsupp::operator=(const Partsupp &t) {
    if (&t == this)
        return *this;
    ps_partkey = t.ps_partkey;
    ps_suppkey = t.ps_suppkey;
    ps_availqty = t.ps_availqty;
    ps_supplycost = t.ps_supplycost;
    std::strncpy(ps_comment, t.ps_comment, 200);
    return *this;
}

Customer::Customer(const std::string &s) : c_name(""), c_address(""), c_phone(""), c_mktsegment(""), c_comment("") {
    std::stringstream stream(s);
    std::string item;
    std::getline(stream, item, '|');
    c_custkey = static_cast<uint32_t>(std::stoull(item));
    std::getline(stream, item, '|');
    std::strncat(c_name, item.c_str(), sizeof(c_name) - 1);
    std::getline(stream, item, '|');
    std::strncat(c_address, item.c_str(), sizeof(c_address) - 1);
    std::getline(stream, item, '|');
    c_nationkey = static_cast<uint32_t>(std::stoull(item));
    std::getline(stream, item, '|');
    std::strncat(c_phone, item.c_str(), sizeof(c_phone) - 1);
    std::getline(stream, item, '|');
    c_acctbal = std::stod(item);
    std::getline(stream, item, '|');
    std::strncat(c_mktsegment, item.c_str(), sizeof(c_mktsegment) - 1);
    std::getline(stream, item, '|');
    std::strncat(c_comment, item.c_str(), sizeof(c_comment) - 1);
}

Customer &Customer::operator=(const Customer &t) {
    if (this == &t)
        return *this;
    c_custkey = t.c_custkey;
    std::strncpy(c_name, t.c_name, 26);
    std::strncpy(c_address, t.c_address, 41);
    c_nationkey = t.c_nationkey;
    std::strncpy(c_phone, t.c_phone, 16);
    c_acctbal = t.c_acctbal;
    strncpy(c_mktsegment, t.c_mktsegment, 11);
    strncpy(c_comment, t.c_comment, 118);
    return *this;
}

Orders::Orders(const std::string &s) : o_orderpriority(""), o_clerk(""), o_comment("") {
    std::stringstream stream(s);
    std::string item;
    std::getline(stream, item, '|');
    o_orderkey = static_cast<uint32_t>(std::stoull(item));
    std::getline(stream, item, '|');
    o_custkey = static_cast<uint32_t>(std::stoull(item));
    std::getline(stream, item, '|');
    o_orderstatus = item[0];
    std::getline(stream, item, '|');
    o_totalprice = std::stod(item);
    std::getline(stream, item, '|');
    o_orderdate = date_t(item);
    std::getline(stream, item, '|');
    std::strncat(o_orderpriority, item.c_str(), sizeof(o_orderpriority) - 1);
    std::getline(stream, item, '|');
    std::strncat(o_clerk, item.c_str(), sizeof(o_clerk) - 1);
    std::getline(stream, item, '|');
    o_shippriority = std::stoi(item);
    std::getline(stream, item, '|');
    std::strncat(o_comment, item.c_str(), sizeof(o_comment) - 1);
}

Orders &Orders::operator=(const Orders &t) {
    if (this == &t)
        return *this;
    o_orderkey = t.o_orderkey;
    o_custkey = t.o_custkey;
    o_orderstatus = t.o_orderstatus;
    o_totalprice = t.o_totalprice;
    o_orderdate = t.o_orderdate;
    std::strncpy(o_orderpriority, t.o_orderpriority, 16);
    std::strncpy(o_clerk, t.o_clerk, 16);
    o_shippriority = t.o_shippriority;
    std::strncpy(o_comment, t.o_comment, 80);
    return *this;
}

Lineitem::Lineitem(const std::string &s) : l_shipinstruct(""), l_shipmode(""), l_comment("") {
    std::stringstream stream(s);
    std::string item;
    std::getline(stream, item, '|');
    l_orderkey = static_cast<uint32_t>(std::stoull(item));
    std::getline(stream, item, '|');
    l_partkey = static_cast<uint32_t>(std::stoull(item));
    std::getline(stream, item, '|');
    l_suppkey = static_cast<uint32_t>(std::stoull(item));
    std::getline(stream, item, '|');
    l_linenumber = std::stoi(item);
    std::getline(stream, item, '|');
    l_quantity = std::stod(item);
    std::getline(stream, item, '|');
    l_extendedprice = std::stod(item);
    std::getline(stream, item, '|');
    l_discount = std::stod(item);
    std::getline(stream, item, '|');
    l_tax = std::stod(item);
    std::getline(stream, item, '|');
    l_returnflag = item[0];
    std::getline(stream, item, '|');
    l_linestatus = item[0];
    std::getline(stream, item, '|');
    l_shipdate = date_t(item);
    std::getline(stream, item, '|');
    l_commitdate = date_t(item);
    std::getline(stream, item, '|');
    l_receiptdate = date_t(item);
    std::getline(stream, item, '|');
    std::strncat(l_shipinstruct, item.c_str(), sizeof(l_shipinstruct) - 1);
    std::getline(stream, item, '|');
    std::strncat(l_shipmode, item.c_str(), sizeof(l_shipmode) - 1);
    std::getline(stream, item, '|');
    std::strncat(l_comment, item.c_str(), sizeof(l_comment) - 1);
}

Lineitem &Lineitem::operator=(const Lineitem &t) {
    if (this == &t)
        return *this;
    l_orderkey = t.l_orderkey;
    l_partkey = t.l_partkey;
    l_suppkey = t.l_suppkey;
    l_linenumber = t.l_linenumber;
    l_quantity = t.l_quantity;
    l_extendedprice = t.l_extendedprice;
    l_discount = t.l_discount;
    l_tax = t.l_tax;
    l_returnflag = t.l_returnflag;
    l_linestatus = t.l_linestatus;
    l_shipdate = t.l_shipdate;
    l_commitdate = t.l_commitdate;
    l_receiptdate = t.l_receiptdate;
    std::strncpy(l_shipinstruct, t.l_shipinstruct, 26);
    std::strncpy(l_shipmode, t.l_shipmode, 11);
    std::strncpy(l_comment, t.l_comment, 45);
    return *this;
}

Part::Part(const std::string &s) : p_name(""), p_mfgr(""), p_brand(""), p_type(""), p_container(""), p_comment("") {
    std::stringstream stream(s);
    std::string item;
    std::getline(stream, item, '|');
    p_partkey = static_cast<uint32_t>(std::stoull(item));
    std::getline(stream, item, '|');
    std::strncat(p_name, item.c_str(), sizeof(p_name) - 1);
    std::getline(stream, item, '|');
    std::strncat(p_mfgr, item.c_str(), sizeof(p_mfgr) - 1);
    std::getline(stream, item, '|');
    std::strncat(p_brand, item.c_str(), sizeof(p_brand) - 1);
    std::getline(stream, item, '|');
    std::strncat(p_type, item.c_str(), sizeof(p_type) - 1);
    std::getline(stream, item, '|');
    p_size = std::stoi(item);
    std::getline(stream, item, '|');
    std::strncat(p_container, item.c_str(), sizeof(p_container) - 1);
    std::getline(stream, item, '|');
    p_retailprice = std::stod(item);
    std::getline(stream, item, '|');
    std::strncat(p_comment, item.c_str(), sizeof(p_comment) - 1);
}

Part &Part::operator=(const Part &t) {
    if (this == &t)
        return *this;
    p_partkey = t.p_partkey;
    std::strncpy(p_name, t.p_name, 56);
    std::strncpy(p_mfgr, t.p_mfgr, 26);
    std::strncpy(p_brand, t.p_brand, 11);
    std::strncpy(p_type, t.p_type, 25);
    p_size = t.p_size;
    std::strncpy(p_container, t.p_container, 11);
    p_retailprice = t.p_retailprice;
    std::strncpy(p_comment, t.p_comment, 24);

    return *this;
}