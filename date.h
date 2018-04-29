//
// Created by Ben on 2018/4/14.
//

#ifndef DISTRIBUTEDWANDERJOIN_DATE_H
#define DISTRIBUTEDWANDERJOIN_DATE_H

#include <cstdint>
#include <cstring>
#include <sstream>

struct date_t {
    uint16_t year;
    uint8_t month;
    uint8_t day;

    date_t() : year(0), month(0), day(0) {}

    explicit date_t(const std::string &s) {
        std::stringstream dateStream(s);
        std::string dateToken;
        std::getline(dateStream, dateToken, '-');
        year = static_cast<uint16_t>(std::stoi(dateToken));
        std::getline(dateStream, dateToken, '-');
        month = static_cast<uint8_t>(std::stoi(dateToken));
        std::getline(dateStream, dateToken, '-');
        day = static_cast<uint8_t>(std::stoi(dateToken));
    }

    date_t &operator=(const date_t &t) {
        if (this == &t)
            return *this;
        if (this == &t)
            return *this;
        year = t.year;
        month = t.month;
        day = t.day;
        return *this;
    }
};

#endif //DISTRIBUTEDWANDERJOIN_DATE_H
