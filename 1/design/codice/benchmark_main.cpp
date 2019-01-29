#include "benchmark.hpp"

//long int filesize[N] = {10485760, 104857600, 1073741824, 10737418240};
//long int blocksize[N] = {1024, 10240, 102400, 1048576};

//long int filesize[N] = {1048576, 104857600, 1073741824};
long int filesize[N] = {6*1048576, 24*10485760, 96*10485760};
long int blocksize[N] = {5*102400, 1048576, 3*1048576};
int n[N][N] = {0};

int main() {
	system("echo 3 > /proc/sys/vm/drop_caches");
	long int numIteraction = 0;
	unsigned int ex = 0, rep = 0;

	for(int i=0;i<N;i++) {
		for(int j=N-1;j>=0;j--) {
			numIteraction = filesize[i]/blocksize[j];
			cout << "RESULTS OF COMBINATION NUMBER: " << ++ex << endl;
			cout << "FILESIZE: " << filesize[i] << " BLOCKSIZE: " << blocksize[j] << " NUM OF ITERACTION: " << numIteraction << " NUM OF EXPERIMENT: " << n[i][j] << endl;			
			for(int k=n[i][j];k>0;--k) {
				cout << rep++%n[i][j] << ";";
				analysisWrite(blocksize[j], numIteraction);
				//checkFileSize(filesize[i]);
				analysisRead(blocksize[j], numIteraction);
			}
		}
	}
	system("echo 1 > /proc/sys/vm/drop_caches");
	return 0;
}
