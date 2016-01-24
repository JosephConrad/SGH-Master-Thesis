//
// Created by Konrad Lisiecki on 18/01/16.
//


#include <src/main/cpp/heston/header/Heston.h>
#include <vector>
#include <src/main/cpp/option/option.h>

Heston::Heston(
        Option *option,
        double kappa,
        double theta,
        double epsilon,
        double rho)
        :
        option(option),
        kappa(kappa),
        theta(theta),
        epsilon(epsilon),
        rho(rho)
{ }

Heston::~Heston() { }

double Heston::getRho() const {
    return rho;
}

