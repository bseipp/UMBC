Driver: HashTable.o Driver.o
	g++ -Wall -o Driver HashTable.o Driver.o

Driver.o: Driver.cpp HashTable.h
	g++ -Wall -ansi -c Driver.cpp

MinMaxHeap.o: HashTable.cpp HashTable.h
	g++ -Wall -ansi -c HashTable.cpp

run: Driver
	./Driver

runv: Driver
	valgrind ./Driver

clean:
	rm Driver *.o