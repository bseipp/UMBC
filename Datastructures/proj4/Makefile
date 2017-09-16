Driver: MinMaxHeap.o Driver.o
	g++ -Wall -o Driver MinMaxHeap.o Driver.o

Driver.o: Driver.cpp MinMaxHeap.h
	g++ -Wall -ansi -c Driver.cpp

MinMaxHeap.o: MinMaxHeap.cpp MinMaxHeap.h
	g++ -Wall -ansi -c MinMaxHeap.cpp

run: Driver
	./Driver

runv: Driver
	valgrind ./Driver

clean:
	rm Driver *.o