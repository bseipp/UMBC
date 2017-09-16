proj0test: joke.o proj0test.o
	g++ -Wall -o proj0test joke.o proj0test.o

driver: driver.o joke.o
	g++ -Wall -o driver driver.o joke.o

proj0test.o: proj0test.cpp joke.h
	g++ -Wall -ansi -c proj0test.cpp

driver.o: driver.cpp joke.h
	g++ -Wall -ansi -c driver.cpp

joke.o: joke.cpp joke.h
	g++ -Wall -ansi -c joke.cpp

run: driver
	./driver

runTest: proj0test
	./proj0test

clean:
	rm driver *.o

cleanTest: 
	rm proj0test *.o