//
// Created by Konrad Lisiecki on 21/02/16.
//

#include "Simulation.h"


Simulation::Simulation(double asset, std::vector<double> strikePrices, double riskFree,
                       double expiry, double volatility, double kappa, double theta,
                       double eps, double rho, int trials, double truePrice,
                       const std::string &description)
        : asset(asset),
          strikePrices(strikePrices),
          riskFree(riskFree),
          expiry(expiry),
          volatility(volatility),
          kappa(kappa),
          theta(theta),
          eps(eps),
          rho(rho),
          trials(trials),
          truePrice(truePrice),
          description(description) { }
