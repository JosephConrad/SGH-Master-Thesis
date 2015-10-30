//
// Created by Konrad Lisiecki on 26/09/15.
//

#include <iostream>
#include <fstream>
#include <sstream>
#include "../SimulatedAnnealing/SimulatedAnnealing.h"
#include "../OrderBook/OrderBook.h"
#include "../SimpleMonteCarlo/MCBlackScholes.h"

#include <boost/algorithm/string/split.hpp>



// Assumed that for given id, INSERT is always first, followed by ERASE

int main(int argc, char **argv) {

    int iterations = 1;
    double coolingCoeff = 0.99998;
    double rho = -0.6;     // Correlation of asset and volatility
    double kappa = 6.1;   // Mean-reversion rate
    double theta = 0.09;  // Long run average volatility
    double xi = 0.31;
    std::vector<double> bestHestonPar = {rho, kappa, theta, xi};


    double S_0 = 100.0;    // Initial spot price
    double K = 100.0;      // Strike price
    double r = 0.0319;     // Risk-free rate
    double v_0 = 0.010201; // Initial volatility
    double Expiry = 1.00;       // One year until expiry
    MCBlackScholes *mcBlackScholes = new MCBlackScholes(Expiry, K, S_0, v_0, r, 100000);
    std::cout << mcBlackScholes->simulate();


    return 0;
}