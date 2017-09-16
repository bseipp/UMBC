CPPFLAGS = -ansi -Wall

lab4: lab4.o Fraction.o
	g++ lab4.o Fraction.o -o lab4

lab4.o: lab4.cpp Fraction.h
	g++ -ansi -Wall -c lab4.cpp

Fraction.o: Fraction.cpp Fraction.h
	g++ -ansi -Wall -c Fraction.cpp