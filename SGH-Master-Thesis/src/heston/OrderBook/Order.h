//
// Created by Konrad Lisiecki on 06/10/15.
//

#ifndef HESTON_ORDER_H
#define HESTON_ORDER_H


#include <iosfwd>
#include <string>
#include "Operation.h"

class Order {

public:

    unsigned int getTimestamp() const {
        return timestamp;
    }

    const Operation &getOperation() const {
        return operation;
    }

    unsigned int getId() const {
        return id;
    }

    std::string getPrice() const {
        return price;
    }

    Order(unsigned int timestamp, const Operation &operation, unsigned int id, std::string &price);

    Order() { }

private:
    unsigned int timestamp;
    Operation operation;
    unsigned int id;
    std::string price;
};


#endif //HESTON_ORDER_H
