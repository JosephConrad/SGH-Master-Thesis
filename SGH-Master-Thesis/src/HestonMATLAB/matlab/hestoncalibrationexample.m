                %Author: Moeti Ncube

%Comments: This code calibrates the heston model to any dataset of the form
%of the marketdata.txt file. It also simulates the heston model given the
%optimized parameters.

%Marketdata=[strike, maturity,impvol,time till expiry]

%Strike: Strike price of options
%Maturity: (1=Prompt month, 2=Prompt month+1,...)
%Impvol: Market Implied vol
%Time till expiry: Days until option expires

clear all

global impvol; global strike; global T; global F0; global r;

%Initial Parameter Guess for Hestion Model
%V(1), Kappa, Theta, Vol of Volatility (sig), Correlation (rho)
initPoint=[.5,.5,.5,.05,.5,.5];
%Constraints (Lower and Upper bounds on Parameters)
lowerBound = [0, 0, 0, 0, -.9, 0];
upperBound = [1, 100, 1, .5, .9];
%Number of MCMC simulations of Heston Model
M=50000;
%Current Asset Price (Prompt Month Price) and Interest rate
F0=207.93; r=0.03;

% x(6)=2*x(2)*x(3)-x(4)^2; %Feller condition

load optionInputChart.txt

T=optionInputChart(:,3)/365;
strike=optionInputChart(:,1);
impvol=optionInputChart(:,2);
 
      asset =100.0;
      strike1=100.0;
      volatility=0.010201;
      riskFree=0.0319;
      expiry=1.0;
      kappa=6.21;
      theta=0.019;
      epsilon=0.61;
      rho=-0.70;
      trials=10000;
%V(1), Kappa, Theta, Vol of Volatility (sig), Correlation (rho)
aa = HestonCall(asset,strike1,riskFree,expiry,volatility,kappa,theta, epsilon, rho,0); 
aa
% strike(1) ;
% T(1);
%  impvol(1);
%  //x = [0.0395,   40.5962,    0.0098,    0.0022,    0.4031];
x = lsqnonlin(@costf2,initPoint,lowerBound,upperBound);
%  y = HestonCall(F0,strike(1),r,T(1),x(1),x(2),x(3),x(4),x(5),0);           
%  z = blsprice(F0,strike(1),r,T(1),impvol(1));
 %Optimization
%   y
%   z
x
%Optimization
% x=fmincon(@costf2,x0,[],[],[],[],lb,ub,@Feller); 
% x = lsqnonlin(@costf2,initPoint,lowerBound,upperBound);
% 
% for k=1:length(T);
% %Initial asset price
% shes(1)=F0;
% %Number of Time Steps,time step size
% N=round(T(k)/(1/360));dt=T(k)/N;
% 
% %Heston Parameters
% vhes(1)=x(1);  kappa=x(2); theta=x(3); vsigma=x(4);rho=x(5); simPath=0;
% 
% %Simulation of Heston Model
% for i = 1:M  
% for j=1:N
% %heston model
% r1 = randn;
% r2 = rho*r1+sqrt(1-rho^2)*randn;   
% shes(j+1)=shes(j)*exp((-0.5*vhes(j))*dt+sqrt(vhes(j))*sqrt(dt)*r1);
% vhes(j+1)=vhes(j)*exp(((kappa*(theta - vhes(j))-0.5*vsigma^2)*dt)/vhes(j) + vsigma*(1/sqrt(vhes(j)))*sqrt(dt)*r2);
% end
% simPath = simPath + exp(-r*T(k)) * max(shes(j+1) - strike(k), 0);
% end
% simhes(k)=simPath/M;
% simimpvol(k)=blkimpv(shes(1), strike(k), r, T(k), simhes(k));
% modhes(k)=HestonCall(shes(1),strike(k),r,T(k),vhes(1),kappa,theta,vsigma,rho,0);
% hesimpvol(k)=blkimpv(shes(1), strike(k), r, T(k), modhes(k));
% end
% 
% for i=1:length(T)
% bsprice(i)=blsprice(F0,strike(i),r,T(i),impvol(i));
% end
% 
% %Output optimized Parameters
% x
% 
% %Compare blackscholes option price, analytical heston price, and simulated
% %heston prices for a given maturity and strike
% pricedata=[T,strike,bsprice',modhes',simhes']
% 
% %Compare blackscholes option IV, analytical heston IV, and simulated
% %heston IV for a given maturity and strike
% 
% voldata=[T,strike,impvol,hesimpvol',simimpvol']
% 
% 
