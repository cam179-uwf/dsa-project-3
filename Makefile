main: main.cpp tsp-brute-force.o tsp-ga.o
	g++ -Wall -std=c++11 $^ -o main

tsp-brute-force.o: tsp-brute-force.cpp tsp-brute-force.hpp
	g++ -Wall -c $<

tsp-ga.o: tsp-ga.cpp tsp-ga.hpp
	g++ -Wall -c $<

clean:
	rm *.exe main *.o

wclean:
	del *.exe main *.o