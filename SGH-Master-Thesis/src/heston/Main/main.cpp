//
// Created by Konrad Lisiecki on 26/09/15.
//

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include "../OrderBook/OrderBook.h"
#include "../SimpleMonteCarlo/MCBlackScholes.h"
#include "../MonteCarlo/MCHeston.h"

#include <boost/algorithm/string/split.hpp>



// Assumed that for given id, INSERT is always first, followed by ERASE

int main(int argc, char **argv) {

    double rho = 0.4031;     // Correlation of asset and volatility
    double kappa = 40.5962;   // Mean-reversion rate
    double theta = 0.0098;  // Long run average volatility
    double xi = 0.0022;
    std::vector<double> calibratedParams = {rho, kappa, theta, xi};

    double initPrice = 207.93;    // Initial spot price
    double strike = 207.93;      // strike price
    double riskFreeRate = 0.03;     // Risk-free rate
    double initVol = 0.15; // Initial volatility
    double expiry = 1.00;       // One year until expiry
    std::vector<double> initialParams = {initPrice, strike, riskFreeRate, initVol, expiry};

    MCHeston monteCarloSimulation = MCHeston();
    std::cout << monteCarloSimulation.simulateHeston(calibratedParams, initialParams);
    std::cout << "haha";
    MCBlackScholes *mcBlackScholes = new MCBlackScholes(expiry, strike, initPrice, initVol, riskFreeRate, 10000);
    std::cout << mcBlackScholes->simulate();


    return 0;
}