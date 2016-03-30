load '../data/hestonPrices.txt'; 
addpath('../../lib/');
addpath('../../lib/VolatilitySurface/');

S_vector = hestonPrices(:,1);
r_vector = hestonPrices(:,3);

K = hestonPrices(:,2);
T = hestonPrices(:,4);
HP = hestonPrices(:,5);

S = S_vector(1);
r = r_vector(1);

surface=VolatilitySurface(S, r, T, K, HP);

saveTightFigure('../figs/hestonVolSurfaceExampleSAndP.pdf');





% for i=1:length(T)
%     Volatility(i) = blsimpv(S_vector(i), K(i), r_vector(i), T(i), HP(i));
%     fprintf('%s\n', sprintf('%12.3f;%12.3f;%12.3f;%12.3f', S_vector(i), K(i), Volatility(i),  T(i)));
% end