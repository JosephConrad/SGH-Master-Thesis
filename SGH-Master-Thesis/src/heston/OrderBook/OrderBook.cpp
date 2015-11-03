//
// Created by Konrad Lisiecki on 06/10/15.
//

#include <iostream>
#include "OrderBook.h"


void OrderBook::insert(Order &order) {
    std::string price = order.getPrice();
    if (prices.find(price) == prices.end()) {
        prices[price] = 1;
    } else {
        prices[price] += 1;
    }
    orders.insert(std::pair<int, Order>(order.getId(), order));
}

double OrderBook::getHighestPrice() {
    return std::stod(prices.rbegin()->first);
}

void OrderBook::erase(int orderId) {
    std::string price = orders[orderId].getPrice();
    prices[price] -= 1;
    if (prices[price] == 0) {
        prices.erase(price);
    }
    orders.erase(orderId);
}

void OrderBook::manageOrder(Order &currentOrder) {
    if (currentOrder.getOperation() == Operation::INSERT) {
        this->insert(currentOrder);
    } else {
        this->erase(currentOrder.getId());
    }
}
