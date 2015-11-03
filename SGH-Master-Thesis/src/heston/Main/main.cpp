//
// Created by Konrad Lisiecki on 26/09/15.
//

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <iostream>
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

    for (int j = 1; j <= 12; ++j) {

        int i = j * 180;

        std::ofstream output;
                output.open("/Users/konrad/Dropbox/MastersTheses/SGH-Master-Thesis/outputs/heston" + std::to_string(i));
        std::cout << "Writing to file " + std::to_string(i) + "\n";
        double expiry = i / 360.0;       // One year until expiry
        std::vector<double> initialParams = {initPrice, strike, riskFreeRate, initVol, expiry};

        MCHeston monteCarloSimulation = MCHeston();
        double result;
        result = monteCarloSimulation.simulateHeston(calibratedParams, initialParams, output);
//        MCBlackScholes *mcBlackScholes = new MCBlackScholes(expiry, strike, initPrice, initVol, riskFreeRate, 10000);
//        output << mcBlackScholes->simulate();


    }





    return 0;
}