#include <math.h>

#include <src/main/cpp/random/PolarGenerator.h>
#include <src/main/cpp/bs/MCBlackScholes.h>


MCBlackScholes::MCBlackScholes(double Expiry, double Strike,
                               double Spot, double Vol, double r,
                               unsigned long NumberOfPaths)
        : expiry(Expiry), strike(Strike), spot(Spot), vol(Vol),
          riskFree(r), simNumber(NumberOfPaths) { }


double MCBlackScholes::simulate() {

    double variance = vol * vol * expiry;
    double rootVariance = sqrt(variance);
    double itoCorrection = -0.5 * variance;
    double movedSpot = spot * exp(riskFree * expiry + itoCorrection);

    double payoffSum = 0.0;
    double spot, payoff;

    PolarGenerator &polarGen = PolarGenerator::getInstance();

    for (auto i = 0; i < simNumber; ++i) {
        auto normal = polarGen.genNorm();
        spot = movedSpot * exp(rootVariance * normal);
        payoff = spot - strike;
        payoffSum += payoff > 0 ? payoff : 0;
    }
    double payoffAvg = payoffSum / static_cast<double>(simNumber);
    return payoffAvg * exp(-riskFree * expiry);
}