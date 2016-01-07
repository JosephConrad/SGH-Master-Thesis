//
// Created by Konrad Lisiecki on 06/01/16.
//

#include "../header/Heston.h"

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
{
}

Heston::~Heston() { }
