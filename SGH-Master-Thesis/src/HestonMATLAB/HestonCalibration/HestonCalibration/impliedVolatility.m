
fname = '/Users/konrad/Dropbox/MastersTheses/SGH-Master-Thesis/src/heston/input/input.json';

load '/Users/konrad/Dropbox/MastersTheses/SGH-Master-Thesis/src/heston/impVol.txt'


% a = loadjson(fname);
% params.('asset')

S = impVol(:,1);
K = impVol(:,2);
r = impVol(:,3);
T = impVol(:,4);
HP = impVol(:,5);
for i=1:length(T)
    Volatility = blsimpv(S(i), K(i), r(i), T(i), HP(i)); 
    disp(Volatility);               
end

% for i=1:3 
%     params = a.('heston'){i};
%     Volatility = blsimpv(S[1], K[1], r[1], T[1], HP[i], 0.5, 0, [], {'Call'}); 
%                      
%     Volatility
% end
