//
// Created by Konrad Lisiecki on 21/03/16.
//

#include <src/main/cpp/heston/header/HestonExactLittleTrap.h>


HestonExactLittleTrap::HestonExactLittleTrap(
        Option *option,
        double kappa,
        double theta,
        double epsilon,
        double rho)
        : HestonExact(option, kappa, theta, epsilon, rho) { }

dcomp HestonExactLittleTrap::calc_C(double tau, double phi, int j) {
    dcomp G, d, x;
    d = calc_d(phi, j);
    x = calc_x(phi, j);
    G = calc_G(tau, phi, j);
    return (option->r * phi * DCOMP * tau)
           + (a / pow(eps, 2)) * ((x - d) * tau - 2.0 * log(G));
}

dcomp HestonExactLittleTrap::calc_G(double tau, double phi, int j) {
    dcomp d, c;
    c = 1.0 / calc_g(phi, j);
    d = calc_d(phi, j);
    return (1.0 - c * exp(-d * tau)) / (1.0 - c);
}

dcomp HestonExactLittleTrap::calc_D(double tau, double phi, int j) {
    dcomp x, c, d;
    x = calc_x(phi, j);
    c = 1.0 / calc_g(phi, j);
    d = calc_d(phi, j);
    return ((x - d) / pow(eps, 2)) *
           ((1.0 - exp(-d * tau)) / (1.0 - c * exp(-d * tau)));
}

std::string HestonExactLittleTrap::getName() {
    return "HESTON EXACT";
}
