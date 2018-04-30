//
// Created by Ben on 2018/4/15.
//

#ifndef DISTRIBUTEDWANDERJOIN_Q3_H
#define DISTRIBUTEDWANDERJOIN_Q3_H

#include <vector>
#include <fstream>
#include <string>
#include "entries.h"
#include "tables.h"

class Q3 {
private:
    CustomerTable customerTable;
    OrdersTable ordersTable;
    LineitemTable lineitemTable;
    std::ifstream openTableFile(const std::string &s);
    void closeTableFile(std::ifstream &fin);

public:
    void execute();
};


#endif //DISTRIBUTEDWANDERJOIN_Q3_H
