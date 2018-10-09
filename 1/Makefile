CC = g++
CFLAG = -g -O2
OBJ = main.cpp function.cpp

all: main
	@echo Make has finished.

main: main.cpp function.cpp benchmark.hpp
	$(CC) $(CFLAG) $(OBJ) -o main

clean:
	rm -f *.o 
	rm -f *.gch
