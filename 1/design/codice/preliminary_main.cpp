#include "benchmark.hpp"

//long int filesize[N] = {10485760, 104857600, 1073741824, 10737418240};
//long int blocksize[N] = {1024, 10240, 102400, 1048576};

//long int filesize[N] = {1048576, 104857600, 1073741824};
long int filesize[N] = {6*1048576, 24*10485760, 96*10485760};
long int blocksize[N] = {5*102400, 1048576, 3*1048576};

int main() {
	system("echo 3 > /proc/sys/vm/drop_caches");
	long int numIteraction = 0;
	unsigned int ex = 0, rep = 0;

	for(int i=0;i<N;i++) {
		for(int j=N-1;j>=0;j--) {
			numIteraction = filesize[i]/blocksize[j];
			cout << "RESULTS OF PRELIMINARY EXPERIMENT NUMBER: " << ++ex << endl;
			cout << "FILESIZE: " << filesize[i] << " BLOCKSIZE: " << blocksize[j] << " NUMINTERACTION: " << numIteraction << endl;
			for(int k=NUM_ESPERIMENTI_PRELIMINARI;k>0;--k) {
				cout << rep++%NUM_ESPERIMENTI_PRELIMINARI << ";";
				analysisWrite(blocksize[j], numIteraction);
				analysisRead(blocksize[j], numIteraction);
			}
		}
	}
	system("echo 1 > /proc/sys/vm/drop_caches");	
	return 0;
}
