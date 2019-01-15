#include "benchmark.hpp"

void *bufferRead;
void *bufferWrite;

void termBuffer() {
	termBufferRead();
	termBufferWrite();
	remove("file_prova.bin");
}

void termBufferRead() {
	free(bufferRead);
}

void termBufferWrite() {
	free(bufferWrite);
}

void initBufferWrite(long int bs) {
	int errMemAlign = posix_memalign(&bufferWrite, 4096, bs);
	system("sync; echo 3 > /proc/sys/vm/drop_caches");	
	//cout << pathconf("file_prova.bin",_PC_REC_XFER_ALIGN) << endl;
	if (errMemAlign!=0) {
		cout << errMemAlign << endl;	
		exit(0);	
	}
	if (getrandom(bufferWrite, bs, GRND_NONBLOCK)==-1) {
		perror("get random error");
		termBuffer();
		exit(0);
	}
}

void initBufferRead(long int bs) {
	int errMemAlign = posix_memalign(&bufferRead, 4096, bs);
	//cout << pathconf("file_prova.bin",_PC_REC_XFER_ALIGN) << endl;
	if (errMemAlign!=0) {
		cout << errMemAlign << endl;	
		exit(0);	
	}
}

void analysisWrite(long int bs, long int num) {
	std::chrono::duration<double> elapsedAccumulatorWrite;
	elapsedAccumulatorWrite.zero();
	int writeSuccessful = 0;
	
	//open file and control
	int fd = open("file_prova.bin", O_CREAT|O_TRUNC|O_WRONLY|O_APPEND|O_DIRECT|O_SYNC, S_IRWXU);
	if(fd==-1) {
		perror("open file error");
		termBuffer();
		exit(0);
	}

	for(int i=num-1;i>=0;--i) {

		//initialize buffer
		initBufferWrite(bs);

		//start timer
		auto start_time = std::chrono::system_clock::now();

		//write buffer
		writeSuccessful = write(fd, bufferWrite, bs);
	
		//end timer
		auto end_time = std::chrono::system_clock::now();

		//control write
		if (writeSuccessful != bs) {
			perror("write error");
			termBuffer();
			exit(0);
		}

		//free memory buffer
		termBufferWrite();

		//update accumulator
		elapsedAccumulatorWrite += end_time-start_time;
	}
	//close file
	close(fd);

	//print write time
	cout << elapsedAccumulatorWrite.count() << ";";
}

void analysisRead(long int bs, long int num) {
	std::chrono::duration<double> elapsedAccumulatorRead;
	elapsedAccumulatorRead.zero();
	int readSuccessful = 0;
		
	int fd = open("file_prova.bin", O_RDONLY|O_DIRECT|O_SYNC, S_IRWXU);
	if(fd==-1) {
		perror("open file error");
		termBuffer();
		exit(0);
	}

	for(int i=num-1;i>=0;--i) {
		//initialize buffer
		initBufferRead(bs);

		auto start_time = std::chrono::system_clock::now();

		readSuccessful = read(fd, bufferRead, bs);

		auto end_time = std::chrono::system_clock::now();

		if (readSuccessful != bs) {
			perror("read error");
			termBuffer();
			exit(0);
		}

		termBufferRead();		
		
		elapsedAccumulatorRead += end_time-start_time;
	}
	
	close(fd);
	cout << elapsedAccumulatorRead.count() << ";" << endl;
}

long int fileSize() {
  streampos begin, end;
  ifstream fd ("file_prova.bin", ios::binary);
  begin = fd.tellg();
  fd.seekg (0, ios::end);
  end = fd.tellg();
  fd.close();
  return end-begin;
}

void checkFileSize(long int fs) {
	if(fileSize()<fs) {
		cout << endl <<"File size mismatch" << endl;
		cout << fileSize() << " " << fs << endl;
		exit(0);
	}
}
