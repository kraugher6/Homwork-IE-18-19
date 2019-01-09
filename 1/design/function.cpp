#include "benchmark.hpp"

std::ofstream ofs("/proc/sys/vm/drop_caches");
void *buffer;

void initBuffer(long int fs) {
	posix_memalign(&buffer, sizeof(void *), fs);
	getrandom(buffer, fs, GRND_NONBLOCK);
}

void termBuffer() {
	free(buffer);
}

void analysisWrite(long int bs, long int num) {
	int fd = open("file_prova.bin", O_CREAT|O_TRUNC|O_WRONLY|O_DIRECT, S_IRWXU);
	sync();
	ofs << "3" << std::endl;
	auto start_time = std::chrono::system_clock::now();
	for(unsigned int i=num;i>0;--i)
		write(fd, buffer, bs);
	sync();
	ofs << "3" << std::endl;
	auto end_time = std::chrono::system_clock::now();
	close(fd);

	std::chrono::duration<double> dur = end_time-start_time;
	cout << dur.count() << ";";
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
