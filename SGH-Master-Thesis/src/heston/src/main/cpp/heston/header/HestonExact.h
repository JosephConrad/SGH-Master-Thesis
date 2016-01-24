//
// Created by Konrad Lisiecki on 18/01/16.
//

#ifndef HESTON_HESTONEXACT_H
#define HESTON_HESTONEXACT_H


#include <src/main/cpp/heston/header/Heston.h>
#include <vector>
#include <complex>
#include "complex.h"


typedef std::complex<double> dcomp;


class HestonExact : public Heston {

private:
    const double LAMBDA = 2.0;
    const double DPHI = 0.01;
    dcomp DCOMP = std::complex<double>(0.0, 1.0);
    const double INTEGRATION_LEFT = std::numeric_limits<double>::epsilon();
    const double INTEGRATION_RIGHT = 50.0;

    double a;
    std::vector<double> u;
    std::vector<double> b;


public:

    HestonExact(Option *option,
                double kappa,
                double theta,
                double epsilon,
                double rho);

    double costFunction();

    double calcP(double x, double v, double t, double lgK, double j);

    dcomp calc_f(double x, double d, double t, double phi, double j);

    dcomp calcC(double tau, double phi, int j);

    dcomp calc_g(double phi, int j);

    dcomp calc_d(double phi, int j);

    dcomp calc_x(double phi, int j);

    dcomp calcD(double tau, double phi, int j);

    double integralFun(double xt, double vt, double t, double phi, double lnK, double j);

    double optionPrice(double xt, double vt, double t);

    std::string getName();
};


#endif //HESTON_HESTONEXACT_H
