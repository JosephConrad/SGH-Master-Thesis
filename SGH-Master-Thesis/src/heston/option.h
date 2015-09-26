//
// Created by Konrad Lisiecki on 18/05/15.
//

#ifndef HESTON_OPTION_H
#define HESTON_OPTION_H

#include "payoff.h"

class Option {
public:
    PayOff *pay_off;
    double K;
    double r;
    double T;

    Option(double _K, double _r,
           double _T, PayOff *_pay_off);

    virtual ~Option();
};


#endif //HESTON_OPTION_H
