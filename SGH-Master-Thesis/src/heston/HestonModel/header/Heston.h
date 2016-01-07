//
// Created by Konrad Lisiecki on 06/01/16.
//

#ifndef HESTON_HESTON_H
#define HESTON_HESTON_H


#include <cmath>
#include <vector>
#include "../../option.h"

// The HestonEuler class stores the necessary information
// for creating the volatility and spot paths based on the
// Heston Stochastic Volatility model.
class Heston {
protected:
    Option *pOption;
    double kappa;
    double theta;
    double xi;
    double rho;

public:

    Heston(Option *_pOption,
                double _kappa, double _theta,
                double _xi, double _rho);

    virtual ~Heston();

    // Calculate the volatility path
    virtual void calc_vol_path(const std::vector<double> &vol_draws,
                       std::vector<double> &vol_path) = 0;

    // Calculate the asset price path
    virtual void calc_spot_path(const std::vector<double> &spot_draws,
                        const std::vector<double> &vol_path,
                        std::vector<double> &spot_path) = 0;
};





#endif //HESTON_HESTON_H
