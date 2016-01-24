//
// Created by Konrad Lisiecki on 18/05/15.
//

#ifndef __OPTION_CPP
#define __OPTION_CPP

#include <math.h>
#include "option.h"

Option::Option(double _K, double _r,
               double _T, double _S_0,
               double _v_0, PayOff *_pay_off) :
        K(_K), r(_r), T(_T), S_0(_S_0), v_0(_v_0), pay_off(_pay_off) { }

Option::~Option() { }

double Option::getDiscountFactor() {
    return exp(-r * T);
}

double Option::getDiscountFactor(double t) {
    return exp(-r * (T - t));
}


#endif