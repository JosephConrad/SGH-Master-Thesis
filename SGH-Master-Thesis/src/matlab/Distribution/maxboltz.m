% File: http://web.mit.edu/8.13/matlab/Examples/maxboltz.m
% Date: 2008-June-13
% Author: Scott Sewell


%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% Plots a maxwell-boltzmann distribution of neutron velocities
% See Kittel and Kroemer 'Thermal Physics' for details
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
m= 29.0;            % amu air = 29
M= 0.029;           % kg/mol air = 0.029
T_neutrons= 273; 	% kelvin
k= 1.38066E-23; 	% Boltzmann constant in J/K
R= 8.3145;          % universal gas constant = kN(A) in J/mol K
vprob_273=sqrt(2*R*T_neutrons/M);	% m/s
v=[0:10:5*vprob_273];	% create a molecular speed variable of decent range
Nv_273=4*3.14*(M/(2*3.14*R*T_neutrons))^1.5*v.^2.*exp(-M*v.^2/(2*R*T_neutrons));
Nv_323=4*3.14*(M/(2*3.14*R*323))^1.5*v.^2.*exp(-M*v.^2/(2*R*323));	

figure; 
plot(v,Nv_273,'.');
title('Maxwell-Boltzmann Distribution of Thermal Neutron Velocities');
xlabel('Velocity [m s^{-1}]');
ylabel('N(v)dv');
hold on;
plot(v,Nv_323,'*');
legend('T=273K','T=323K');