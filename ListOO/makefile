#comment

a.out: list.o main.o makefile
	g++ list.o main.o

list.o: makefile list.cpp list.h
	g++ -c list.cpp
	whoami
main.o: main.cpp makefile list.h
	g++ -c main.cpp
