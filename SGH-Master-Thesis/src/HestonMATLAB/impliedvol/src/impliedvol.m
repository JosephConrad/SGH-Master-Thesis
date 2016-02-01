load '../data/hestonPrices.txt';

S = hestonPrices(:,1);
K = hestonPrices(:,2);
r = hestonPrices(:,3);
T = hestonPrices(:,4);
HP = hestonPrices(:,5);
for i=1:length(T)
    if (mod(i, 10) == 0)
        Volatility(i) = blsimpv(S(i), K(i), r(i), T(i), HP(i));
        fprintf('%s\n', sprintf('%d;%d;%d',  K(i), Volatility(i), HP(i)));
    end;
end