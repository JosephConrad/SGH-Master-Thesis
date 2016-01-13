#ifndef HESTON_HESTONANDERSEN_H
#define HESTON_HESTONANDERSEN_H

#include "Heston.h"

class HestonAndersen : Heston {

protected:

    double A;
    double a;
    double b2;
    double beta;
    std::vector<std::vector<double> > martingaleCorrectionCoeffs; // pis, a, b2, beta

    double PSI_CRITICAL = 1.5;


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

    double calcMartingaleCorrection(std::vector<double> &vector, double A, double B);
};


#endif
