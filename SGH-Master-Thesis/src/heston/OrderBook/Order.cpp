//
// Created by Konrad Lisiecki on 06/10/15.
//

#include "Order.h"


Order::Order(unsigned int timestamp, const Operation &operation,
             unsigned int id, std::string &price)
        : timestamp(timestamp), operation(operation), id(id), price(price) { }

//int Order::Compare(const Order& order)
//{
//    return price - order.price
//}Order::Order(){
