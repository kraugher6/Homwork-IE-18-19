#ifndef _BENCHMARK_H_
#define _BENCHMARK_H_

#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <fcntl.h>
#include <unistd.h>
#include <sys/random.h>
#include <chrono>
#include <errno.h>

using namespace std;

#define NUM_ESPERIMENTI 30
#define N 3

void initBufferWrite(long int);
void initBuffe(void);
void initBufferRead(void);
void termBufferWrite(void);
void termBufferRead(void);
void analysisWrite(long int, long int);
void analysisRead(long int, long int);
long int fileSize();
void checkFileSize(long int);

#endif //_BENCHMARK_H_
