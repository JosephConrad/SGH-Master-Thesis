#ifndef HESTON_HESTONANDERSEN_H
#define HESTON_HESTONANDERSEN_H

#include "HestonMC.h"

class HestonAndersen : public HestonMC {

protected:
    double a;
    std::vector<std::vector<double> > martingaleCorrectionCoeffs; // pis, a, b2, beta

    double PSI_CRITICAL = 1.5;

    double GAMMA1 = 0.5;
    double GAMMA2 = 0.5;


public:
    HestonAndersen(Option *option,
                   double kappa,
                   double theta,
                   double epsilon,
                   double rho);

    void simulateVolPath(const std::vector<double> &volDraws,
                         std::vector<double> &volPath);

    void simulateSpotPath(const std::vector<double> spotDraws,
                          const std::vector<double> &volPath,
                          std::vector<double> &spotPath);

    double modifiedExponentialInvertedCDF(double random,
                                          double p,
                                          double beta);

    double calcMartingaleCorrection(std::vector<double> &vector, double a, double d);
};


#endif
