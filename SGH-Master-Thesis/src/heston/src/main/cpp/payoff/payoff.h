//
// Created by Konrad Lisiecki on 18/05/15.
//

#ifndef HESTON_PAYOFF_H
#define HESTON_PAYOFF_H


#include <algorithm> // This is needed for the std::max comparison function, used in the pay-off calculations

class PayOff {
public:
    PayOff(); // Default (no parameter) constructor
    virtual ~PayOff() { }; // Virtual destructor

    // Overloaded () operator, turns the PayOff into an abstract function object
    virtual double operator()(const double &S) const = 0;
};

class PayOffCall : public PayOff {
private:
    double K; // strike price

public:
    PayOffCall(const double &K_);

    virtual ~PayOffCall() { };

    // Virtual function is now over-ridden (not pure-virtual anymore)
    virtual double operator()(const double &S) const;
};

class PayOffPut : public PayOff {
private:
    double K; // strike

public:
    PayOffPut(const double &K_);

    virtual ~PayOffPut() { };

    virtual double operator()(const double &S) const;
};


#endif //HESTON_PAYOFF_H
