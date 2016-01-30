load inputChart.csv

addpath ../../lib

feature('DefaultCharacterSet', 'UTF8') 

[n,p] = size(inputChart);

t=linspace(205,210.5,12)

plot(t,inputChart),
legend('Options with 6 days to expiry','Options with 13 days to expiry','Options with 20 days to expiry','Location','NorthWest')
xlabel('strike'), ylabel('volatility')
title('Calibration input data')

saveTightFigure('../../../figures/calibrationInput.pdf');