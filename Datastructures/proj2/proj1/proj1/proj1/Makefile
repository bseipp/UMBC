test1: Graph.o test1.o
	g++ -Wall -o test1 Graph.o test1.o

test2: Graph.o test2.o
	g++ -Wall -o test2 Graph.o test2.o

Driver: Graph.o Driver.o
	g++ -Wall -o Driver Graph.o Driver.o

test2.o: test2.cpp Graph.h
	g++ -Wall -ansi -c test2.cpp

test1.o: test1.cpp Graph.h
	g++ -Wall -ansi -c test1.cpp

Driver.o: Driver.cpp Graph.h
	g++ -Wall -ansi -c Driver.cpp

Graph.o: Graph.cpp Graph.h
	g++ -Wall -ansi -c Graph.cpp

run: test1
	./test1

run2: test2
	./test2

rund: Driver
	./Driver

runv: test1
	valgrind ./test1

runv2: test2
	valgrind ./test2

runvd: Driver
	valgrind ./Driver

clean:
	rm test1 *.o

clean2: 
	rm test2 *.o

cleand: 
	rm driver *.o