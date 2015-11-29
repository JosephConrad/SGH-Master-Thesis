//
// Created by Konrad Lisiecki on 05/10/15.
//

#ifndef HESTON_MONTECARLOBLACKSCHOLES_H
#define HESTON_MONTECARLOBLACKSCHOLES_H


class MCBlackScholes {

public:

    MCBlackScholes(double Expiry, double Strike, double Spot, double Vol, double r, unsigned long NumberOfPaths);

    double simulate();

private:
    double expiry;
    double strike;
    double spot;
    double vol;
    double riskFree;
    unsigned long numberOfPaths;

    double GetGaussianBoxMuller();
};


#endif //HESTON_MONTECARLOBLACKSCHOLES_H