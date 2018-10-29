#ifndef _BENCHMARK_H_
#define _BENCHMARK_H_

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <iostream>
#include <fstream>
#include <fcntl.h>
#include <unistd.h>
#include <sys/random.h>
#include <chrono>

using namespace std;

#define NUM_ESPERIMENTI 30
#define N 4

void initBuffer(long int);
void termBuffer(void);
void analysisWrite(long int, long int);
void analysisRead(long int, long int);

#endif //_BENCHMARK_H_
