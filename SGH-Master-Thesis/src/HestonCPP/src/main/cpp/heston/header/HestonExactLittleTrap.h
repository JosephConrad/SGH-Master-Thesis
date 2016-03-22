//
// Created by Konrad Lisiecki on 21/03/16.
//

#ifndef HESTON_HESTONEXACTLITTLETRAP_H
#define HESTON_HESTONEXACTLITTLETRAP_H


#include "HestonExact.h"

class HestonExactLittleTrap : public HestonExact {

public:
    HestonExactLittleTrap(Option *option, double kappa, double theta,
                          double epsilon, double rho);

    virtual dcomp calc_C(double tau, double phi, int j);
    virtual dcomp calc_G(double tau, double phi, int j);
    virtual dcomp calc_D(double tau, double phi, int j);
    std::string getName();
};


#endif //HESTON_HESTONEXACTLITTLETRAP_H
