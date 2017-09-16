Driver: LazyBST.o Driver.o
	g++ -Wall -o Driver LazyBST.o Driver.o

test2: LazyBST.o test2.o
	g++ -Wall -o test2 LazyBST.o test2.o

test1: LazyBST.o test1.o
	g++ -Wall -o test1 LazyBST.o test1.o

Driver.o: Driver.cpp LazyBST.h
	g++ -Wall -ansi -c Driver.cpp

test2.o: test2.cpp LazyBST.h
	g++ -Wall -ansi -c test2.cpp

test1.o: test1.cpp LazyBST.h
	g++ -Wall -ansi -c test1.cpp

LazyBST.o: LazyBST.cpp LazyBST.h
	g++ -Wall -ansi -c LazyBST.cpp

rund: Driver
	./Driver

runvd: Driver
	valgrind ./Driver

run2: test2
	./test2

runv2: test2
	valgrind ./test2

run: test1
	./test1

runv: test1
	valgrind ./test1

clean:
	rm test1 test2 Driver *.o