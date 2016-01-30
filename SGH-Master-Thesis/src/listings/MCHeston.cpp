double simulateHeston(std::vector<double> modelParams, 
                      std::vector<double> optionParams) {

    unsigned num_sims = 10000; 
    unsigned length = 1000;  
    // get initPrice, strike, riskFreeRate, initVol, expiry, rho,
    //     kappa, theta and sigma from modelParams and optionParams

    PayOff *payOffCall = new PayOffCall(strike);
    Option *call = new Option(strike, rfRate, expiry, payOffCall);
    HestonEuler hestEuler(call, kappa, theta, sigma, rho);

    std::vector<double> spotDraws(length, 0.0);  
    std::vector<double> volDraws(length, 0.0);  
    std::vector<double> spotPrices(length, initPrice);  
    std::vector<double> volPrices(length, initVol);   

    double payoffSum = 0.0;
    int matlabIndex = 0;
    for (unsigned i = 0; i < num_sims; i++) {
        generate_normal_correlation_paths(rho, spotDraws, volDraws);
        hestEuler.calc_vol_path(volDraws, volPrices);
        hestEuler.calc_spot_path(spotDraws, volPrices, spotPrices);
        payoffSum += call->pay_off->operator()(spotPrices[length-1]);
    }

    double discount = exp(-rfRate * expiry);
    double option_price = (payoffSum/static_cast<double>(num_sims));
    return option_price * discount;
}
