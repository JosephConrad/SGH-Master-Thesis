ton: main.cpp heston_mc.o correlated_snd.o statistics.o option.o payoff.o
	gcc -o heston main.cpp heston_mc.o correlated_snd.o statistics.o option.o payoff.o  

heston_mc.o: heston_mc.cpp option.o
	gcc heston_mc.cpp option.o  

correlated_snd.o: correlated_snd.cpp statistics.o
	gcc correlated_snd.cpp statistics.o  

statistics.o: statistics.cpp 
	gcc  statistics.cpp  

option.o: option.cpp payoff.o
	gcc option.cpp payoff.o   

payoff.o: payoff.cpp
	gcc payoff.cpp  
