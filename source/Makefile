all: millerRabin.o utils.o rsa.o rsa

millerRabin.o: src/millerRabin.cpp include/millerRabin.hh include/InfInt.h
	g++ -Wall -c src/millerRabin.cpp

utils.o: src/utils.cpp include/utils.hh include/InfInt.h
	g++ -Wall -c src/utils.cpp

rsa.o: src/rsa.cpp include/rsa.hh include/InfInt.h
	g++ -Wall -c src/rsa.cpp

rsa: main.cpp
	g++ -Wall millerRabin.o utils.o rsa.o main.cpp -o rsa
clean: 
	\rm *.o  rsa 
