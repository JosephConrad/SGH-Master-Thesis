function [res]=costfunheston(h)
    global impvol; 
    global strike; 
    global expiry; 
    global F0; 
    global r;

    for i=1:length(expiry)
        res(i) = blsprice  (F0, strike(i), r, expiry(i), impvol(i)) - ... 
                 HestonCall(F0, strike(i), r, expiry(i), ...
                    h(1),h(2),h(3),h(4),h(5),0);
    end
