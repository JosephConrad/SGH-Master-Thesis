//
// Created by Konrad Lisiecki on 06/10/15.
//

#ifndef HESTON_ORDERBOOK_H
#define HESTON_ORDERBOOK_H


#include <map>
#include <set>
#include "Order.h"


struct priceComparator {
    bool operator()(const std::string &lhs, const std::string &rhs) const {
        return std::stod(lhs) < std::stod(rhs);
    }
};

class OrderBook {

public:

    void insert(Order &order);

    void erase(int orderId);

    double getHighestPrice();

    void manageOrder(Order &order);

private:

    std::map<int, Order> orders;
    std::map<std::string, int, priceComparator> prices;

};


#endif //HESTON_ORDERBOOK_H
