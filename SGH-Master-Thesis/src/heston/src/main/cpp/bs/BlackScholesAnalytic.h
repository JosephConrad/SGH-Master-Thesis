//
// Created by Konrad Lisiecki on 25/01/16.
//

#ifndef HESTON_BLACKSCHOLESANALYTIC_H
#define HESTON_BLACKSCHOLESANALYTIC_H


class BlackScholesAnalytic {
public:
    double call_price(const double &S, const double &K, const double &r, const double &v, const double &T);

    double put_price(const double &S, const double &K, const double &r, const double &v, const double &T);

    double impliedVolatility(const double S, const double T, const double C);
};


#endif //HESTON_BLACKSCHOLESANALYTIC_H
