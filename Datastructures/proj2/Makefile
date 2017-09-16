Driver: Sally.o Driver.o
	g++ -Wall -o Driver Sally.o Driver.o

Driver.o: Driver.cpp Sally.h
	g++ -Wall -ansi -c Driver.cpp

Sally.o: Sally.cpp Sally.h
	g++ -Wall -ansi -c Sally.cpp

run: Driver
	./Driver

runv: Driver
	valgrind ./Driver

clean:
	rm Driver *.o