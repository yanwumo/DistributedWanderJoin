//
// Created by Ben on 2018/4/15.
//

#ifndef DISTRIBUTEDWANDERJOIN_Q3_H
#define DISTRIBUTEDWANDERJOIN_Q3_H

#include <vector>
#include <fstream>
#include <string>
#include "entries.h"

class Q3 {
private:
    std::vector<Customer> customerTable;
    std::vector<Orders> ordersTable;
    std::vector<Lineitem> lineitemTable;
    std::ifstream openTableFile(const std::string &s);
    void readCustomer(std::ifstream &fin);
    void readOrders(std::ifstream &fin);
    void readLineitem(std::ifstream &fin);
    void closeTableFile(std::ifstream &fin);

public:
    void execute();
};


#endif //DISTRIBUTEDWANDERJOIN_Q3_H
