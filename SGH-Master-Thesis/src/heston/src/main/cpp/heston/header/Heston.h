//
// Created by Konrad Lisiecki on 18/01/16.
//

#ifndef HESTON_HESTON_H
#define HESTON_HESTON_H


#include <src/main/cpp/option/option.h>
#include <string>

class Heston {
protected:
    Option *option;
    double kappa;
    double theta;
    double epsilon;
    double rho;
public:

    Heston(Option *option,
           double kappa,
           double theta,
           double epsilon,
           double rho);

    virtual ~Heston();

    virtual std::string getName() = 0;


    double getRho() const;
};


#endif //HESTON_HESTON_H
