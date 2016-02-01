global impvol; 
global strike; 
global expiry; 
global F0; 
global r;
 
initPoint  = [.5,.5,.5,.05,0]; 
lowerBound = [0.0001, 0.0001, 0.0001, 0.0001, -.9];
upperBound = [1, 100, 1, .5, .9];

F0 = 207.93; 
r  = 0.03; 

fname = sprintf('../../../../input/inputmatlab/calibration.txt');
calibrationInput = load(fname);

strike = calibrationInput(:,1);
impvol = calibrationInput(:,2);
expiry = calibrationInput(:,3)/365;
  
x = lsqnonlin(@costfunheston,initPoint,lowerBound,upperBound);
x
% fprintf('Answer: %s\n', sprintf('%d ', x));