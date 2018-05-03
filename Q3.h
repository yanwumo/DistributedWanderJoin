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
#include <boost/math/special_functions/erf.hpp>

class Q3 {
private:
    CustomerTable customerTable;
    OrdersTable ordersTable;
    LineitemTable lineitemTable;

    size_t decisionRound = 100;

    std::ifstream openTableFile(const std::string &s);

    void closeTableFile(std::ifstream &fin);

    double get_zp(const double &p) {
        return boost::math::erf_inv(p) * std::sqrt(2);
    }

    double variance(const double &sum_y2, const double &sum_y, const double &y_hat, const double &round) {
        return sum_y2 / (round - 1) + y_hat * y_hat * round / (round - 1) - 2 * sum_y * y_hat / (round - 1);
    }

    double confidenceInterval(const double &sum_y2, const double &sum_y, const double &y_hat, const double &round,
                              const double &prob) {
        if (round <= 1)
            return 0.0;
        double sigma = std::sqrt(variance(sum_y2, sum_y, y_hat, round));
        double ci = sigma / std::sqrt(round) * get_zp(prob);
        return ci;
    }

    double confidenceInterval(const double &var, const double &round, const double &prob) {
        if (round <= 1)
            return 0.0;
        double sigma = std::sqrt(var);
        double ci = sigma / std::sqrt(round) * get_zp(prob);
        return ci;
    }

public:
    void execute();

    std::pair<bool, double> singleStepSamplingOverAllTables();

    void query(const double &stepTime, const double &maxTime);
};


#endif //DISTRIBUTEDWANDERJOIN_Q3_H
