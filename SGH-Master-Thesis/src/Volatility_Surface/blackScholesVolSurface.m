%   EXAMPLE 1
%   Downloaded from http://www.cboe.com/delayedquote/QuoteTableDownload.aspx
%   SPX -> download 
%   a table of N points (Maturity,Strike,CallPrice), this is N times 3
%   numbers. 
%   The risk-free rate is 0.66% per annum
%   and S0=770.05
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
clc
clear all 
close all

matFilename = sprintf('../../data/volatilitySurface.csv');
matData = load(matFilename);

S0=210.39;
r=3/100;

Maturity=matData(3:end,3);          % maturity
Strike=matData(3:end,1);            % moneyness
CallPrice=matData(3:end,2);         % option prices

tic
surface=VolatilitySurface(S0, r, Maturity, Strike, CallPrice);
toc

saveTightFigure('../../figures/blackScholesVolSurface.pdf');
