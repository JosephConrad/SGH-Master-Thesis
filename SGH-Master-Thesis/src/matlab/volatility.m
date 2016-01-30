
addpath ../lib


c = yahoo;
sec = 'SPY';
field = 'Close'; % retrieve closing price data
fromdate = '01/01/1970'; % beginning of date range for historical data 
todate = '11/11/2015'; % ending of date range for historical data 
SP500 = fetch(c,sec,field,fromdate,todate); 
close(c);
d = fetch(c,sec);
retSP500 = [0.0 price2ret(SP500(:,end))']; 

tsSP500 = fints(SP500(:,1),SP500(:,end));% 'FTSE100 ? , ? d ? , ? FTSE100 ? ) ;
retSP500 = fints(SP500(:,1), retSP500');%, 'SP500', 'd', 'SP500');

% figure(1);
% subplot 311;
% figure(1); % create first figure
subplot 211;
plot(tsSP500);
legend('Close price');
xlabel('Time');
ylabel('Close price, USD');

subplot 212
plot(retSP500);
legend('Return');
xlabel('Time');
ylabel('Return');

saveTightFigure('../../figures/volatilitySANDP.pdf');