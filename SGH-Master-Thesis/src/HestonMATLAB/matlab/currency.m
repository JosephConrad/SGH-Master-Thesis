clc
clear all
close all

addpath ../lib

data = xlsread('../../data/usdrub1995.xlsx');
dates = data(:,1); 
usdrub = fints(dates, data(:,5),'USDRUB', 'd', 'USDRUB');
plot(usdrub);
datetick('x','dd mmm yy', 'keeplimits', 'keepticks'); 
xlabel('Time');
ylabel('Exchange Rate, RUB per USD');


saveTightFigure('../../figures/currencyUSDRUB.pdf');