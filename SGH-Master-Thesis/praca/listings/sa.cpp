std::vector<double> saCalibration(int iterations, double coolingCoeff) {

    double bestHestonPrice = hestonPrice(bestHestonParams);
    double newHestonPrice;
    double temperature = 1.0;

    std::vector<double> newHestonParams;
    int k = 0;

    while (k < iterations) {
        newHestonParams = mutateParams(bestHestonParams);
        newHestonPrice = hestonPrice(newHestonParams);

        if (metropolisRule(bestHestonPrice, newHestonPrice, temperature)) {
            bestHestonParams = newHestonParams;
            bestHestonPrice = newHestonPrice;
        }

        temperature = coolingSchedule(temperature, coolingCoeff);
        k++;
    }
    return bestHestonParams;
}
