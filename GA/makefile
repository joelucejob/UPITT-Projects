main: main.o fitness.o evolve.o
	g++ -g -o main main.o fitness.o evolve.o
	
main.o : main.cpp main.h fitness.h evolve.h
	g++ -c main.cpp
	
fitness.o : fitness.cpp fitness.h main.h
	g++ -c fitness.cpp
	
evolve.o : evolve.cpp evolve.h main.h
	g++ -c evolve.cpp