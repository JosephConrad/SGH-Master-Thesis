function C=HestonCall(St,K,r,T,vt,kap,th,sig,rho,lda) 
dphi=0.01;
maxphi=50;
phi=(eps:dphi:maxphi)';
 

f1 = CF_SVj(log(St),vt,T,r,kap*th,0.5,kap+lda-rho*sig,rho,sig,phi);
P1 = 0.5+(1/pi)*sum(real(exp(-i*phi*log(K)).*f1./(i*phi))*dphi);
f2 = CF_SVj(log(St),vt,T,r,kap*th,-0.5,kap+lda,rho,sig,phi);
P2 = 0.5+(1/pi)*sum(real(exp(-i*phi*log(K)).*f2./(i*phi))*dphi);
C = St*P1 -K*exp(-r*T)*P2;