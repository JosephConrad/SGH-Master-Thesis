//
// Created by Konrad Lisiecki on 18/05/15.
//

#ifndef HESTON_OPTION_H
#define HESTON_OPTION_H


#include "src/main/cpp/payoff/payoff.h"

class Option {
public:
    PayOff *pay_off;
    double K;
    double r;
    double T;
    double S_0;
    double v_0;

    Option(double _K, double _r,
           double _T, double _S_0,
           double _v_0, PayOff *_pay_off);

    virtual ~Option();

    double getDiscountFactor();

    double getDiscountFactor(double t);
};


#endif //HESTON_OPTION_H
