CC = g++
CFLAG = -g 
BENCH_OBJ = benchmark_main.cpp function.cpp
PRELI_OBJ = preliminary_main.cpp function.cpp

all: preliminary_main benchmark_main
	@echo Make has finished.

preliminary_main: preliminary_main.cpp function.cpp benchmark.hpp
	$(CC) $(CFLAG) $(PRELI_OBJ) -o preliminary_main

benchmark_main: benchmark_main.cpp function.cpp benchmark.hpp
	$(CC) $(CFLAG) $(BENCH_OBJ) -o benchmark_main

clean:
	rm -f *.o 
	rm -f *.gch
