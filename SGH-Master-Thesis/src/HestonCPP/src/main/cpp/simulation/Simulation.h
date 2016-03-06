//
// Created by Konrad Lisiecki on 21/02/16.
//

#ifndef HESTON_SIMULATION_H
#define HESTON_SIMULATION_H

#include <string>
#include <boost/property_tree/ptree_fwd.hpp>
#include <vector>

using boost::property_tree::ptree;

class Simulation {
public:

    double asset;
    double riskFree;
    double expiry;
    double volatility;
    double kappa;
    double theta;
    double eps;
    double rho;

    int trials;

    std::vector<double> strikePrices;
    double truePrice;
    std::string description;


    Simulation(double asset, std::vector<double> strikePrices, double riskFree,
               double expiry, double volatility, double kappa, double theta,
               double eps, double rho, int trials, double truePrice,
               const std::string &description);

    virtual ~Simulation() { };

private:
};


#endif //HESTON_SIMULATION_H
