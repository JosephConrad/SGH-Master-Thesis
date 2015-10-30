#include <math.h>
#include "MCBlackScholes.h"
#include "BoxMuller.h"

MCBlackScholes::MCBlackScholes(double Expiry, double Strike,
                               double Spot, double Vol, double r,
                               unsigned long NumberOfPaths)
        : Expiry(Expiry), Strike(Strike), Spot(Spot), Vol(Vol),
          r(r), NumberOfPaths(NumberOfPaths) { }


double MCBlackScholes::simulate() {
    double variance = Vol * Vol * Expiry;
    double rootVariance = sqrt(variance);
    double itoCorrection = -0.5 * variance;

    double movedSpot = Spot * exp(r * Expiry * itoCorrection);
    double thisSpot;
    double thisPayoff;
    double thisGaussian;
    double payoffSum = 0.0;

    BoxMuller &bm = BoxMuller::getInstance();

    for (auto i = 0; i < NumberOfPaths; ++i) {
        thisGaussian = bm.generateNormal();
        thisSpot = movedSpot * exp(rootVariance * thisGaussian);
        thisPayoff = thisSpot - Strike;
        thisPayoff = thisPayoff > 0 ? thisPayoff : 0;
        payoffSum += thisPayoff;
    }
    double payoff = payoffSum / NumberOfPaths;
    payoff *= exp(-r * Expiry);
    return payoff;
}

