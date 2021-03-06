#include <iostream>
#include <src/main/cpp/heston/header/HestonExact.h>

HestonExact::HestonExact(
        Option *option,
        double kappa,
        double theta,
        double epsilon,
        double rho)
        : Heston(option, kappa, theta, epsilon, rho) {
    a = kappa * theta;
    u = {0, 0.5, -0.5};
    b = {0, kappa + LAMBDA - rho * epsilon, kappa + LAMBDA};
}

double HestonExact::optionPrice(double St, double vt, double t) {
    double K = option->K;
    double P1 = calc_P(St, vt, t, K, 1);
//    std::cout << P1 << std::endl;
    double P2 = calc_P(St, vt, t, K, 2);
//    std::cout << P2 << std::endl;
    double result = option->S_0 * P1 - K * P2 * option->getDiscountFactor(t);
    double temp1 = option->S_0 * P1;
    double temp2 = K * P2 * option->getDiscountFactor(t);
    return result;
}

double HestonExact::calc_P(double St, double vt, double t,
                           double K, double j) {
    double sum = 0.0;
    for (auto phi = INTEGRAL_LEFT; phi < INTEGRAL_RIGHT; phi += DPHI) {
        sum += integralFun(log(St), vt, t, phi, log(K), j);
    }
    return 0.5 + (1.0 / M_PI) * sum;
}

double HestonExact::integralFun(double xt, double vt, double t,
                                double phi, double lnK, double j) {
    dcomp f = calc_f(xt, vt, t, phi, j);
    dcomp exponent = exp(-DCOMP * phi * lnK);
    dcomp res = exponent * f / (DCOMP * phi);
    double real = std::real(res);
    return real * DPHI;
}

dcomp HestonExact::calc_f(double xt, double vt, double t,
                          double phi, double j) {
    dcomp aa = calc_C(option->T - t, phi, j);
    dcomp ab = calc_D(option->T - t, phi, j) * vt;
    dcomp ac = DCOMP * phi * xt;
    dcomp ad = exp(aa + ab + ac);
    return ad;
}

dcomp HestonExact::calc_C(double tau, double phi, int j) {
    dcomp G, d, g, x;
    g = calc_g(phi, j);
    d = calc_d(phi, j);
    x = calc_x(phi, j);
    G = calc_G(tau, phi, j);
    return (option->r * phi * DCOMP * tau)
           + (a / pow(eps, 2)) * ((x + d) * tau - 2.0 * log(G));
}

dcomp HestonExact::calc_G(double tau, double phi, int j) {
    dcomp d, g;
    g = calc_g(phi, j);
    d = calc_d(phi, j);
    return (1.0 - g * exp(d * tau)) / (1.0 - g);
}

dcomp HestonExact::calc_D(double tau, double phi, int j) {
    dcomp x, g, d;
    x = calc_x(phi, j);
    g = calc_g(phi, j);
    d = calc_d(phi, j);
    return ((x + d) / pow(eps, 2)) *
           ((1.0 - exp(d * tau)) / (1.0 - g * exp(d * tau)));
}

dcomp HestonExact::calc_g(double phi, int j) {
    dcomp x, d;
    x = calc_x(phi, j);
    d = calc_d(phi, j);
    return (x + d) / (x - d);
}

dcomp HestonExact::calc_d(double phi, int j) {
    double phi2 = pow(phi, 2);
    return sqrt(pow(rho * eps * phi * DCOMP - b[j], 2) -
                pow(eps, 2) * (2.0 * u[j] * phi * DCOMP - phi2));
}

dcomp HestonExact::calc_x(double phi, int j) {
    return b[j] - (rho * eps * phi * DCOMP);
}

std::string HestonExact::getName() {
    return "HESTON EXACT";
}