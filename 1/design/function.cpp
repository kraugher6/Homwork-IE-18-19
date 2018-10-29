#include "benchmark.hpp"

clock_t inizio, fine;
double cpu_using;
std::ofstream ofs("/proc/sys/vm/drop_caches");
void *buffer;

void initBuffer(long int fs) {
	posix_memalign(&buffer, 1024, fs);
	getrandom(buffer, fs, GRND_NONBLOCK);
}

void termBuffer() {
	free(buffer);
}

void analysisWrite(long int bs, long int num) {
	int fd = open("file_prova.bin", O_CREAT|O_TRUNC|O_WRONLY|O_DIRECT, S_IRWXU);
	sync();
	ofs << "3" << std::endl;
	inizio = clock();
	for(unsigned int i=num;i>0;--i)
		write(fd, buffer, bs);
	sync();
	ofs << "3" << std::endl;
	fine = clock();
	close(fd);

	cpu_using = ((double) (fine - inizio))/CLOCKS_PER_SEC;
	cout << cpu_using << ";";
}

void analysisRead(long int bs, long int num) {
	int fd = open("file_prova.bin", O_CREAT|O_TRUNC|O_WRONLY|O_DIRECT, S_IRWXU);
	sync();
	ofs << "3" << std::endl;
	auto start_time = std::chrono::system_clock::now();
	for(unsigned int i=num;i>0;--i)
		read(fd, buffer, bs);
	sync();
	ofs << "3" << std::endl;
	auto end_time = std::chrono::system_clock::now();
	close(fd);

	std::chrono::duration<double> dur = end_time-start_time;
	cout << dur.count() << ";" << endl;
}
