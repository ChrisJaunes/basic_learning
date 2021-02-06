/*
* Designed a exp about file api of POSIX
* @author ChrisJuanes
*/
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
static void getStat(const int fd) {
	struct stat fd_stat;
	fstat(fd, &fd_stat);
	printf("[getStat] Name : %d\n", fd_stat.st_uid);
	printf("[getStat] Mode : %b\n", fd_stat.st_mode);
}
static void create_file() {
	int fd = creat("File_exp1", S_IRWXU);
	if (fd < 0) {
		printf("[create_file Error] don't create file, code : %d\n", fd);
		return;
	}
	getStat(fd);
	char buf[16];
	memset(buf, 'A', sizeof(buf));
	write(fd, buf, sizeof(buf));
	close(fd);
}
static void open_file_only_read() {
	int fd = open("File_exp1", O_RDONLY); 
	char buf[16];
	memset(buf, 0, sizeof buf);
	ssize_t sz = read(fd, buf, (sizeof buf) - 1);
	printf("[open_file_only_read] read %d: %s\n", (int)sz, buf);

	memset(buf, 'B', 8);
	//lseek(fd, 0, SEEK_SET);
	sz = write(fd, buf, 8);
	printf("[open_file_only_read] read %d\n", (int)sz);

	memset(buf, 0, sizeof buf);
	lseek(fd, 0, SEEK_SET);
	sz = read(fd, buf, (sizeof buf) - 1);
	printf("[open_file_only_read] read %d: %s\n", (int)sz, buf);

	close(fd);
}
static void open_file_only_write() {
	int fd = open("File_exp1", O_WRONLY);
	char buf[16];
	memset(buf, 0, sizeof buf);
	ssize_t sz = read(fd, buf, (sizeof buf) - 1);
	printf("[open_file_only_write] read %d: %s\n", (int)sz, buf);

	memset(buf, 'C', 3);
	//lseek(fd, 0, SEEK_SET);
	sz = write(fd, buf, 3);
	//sz = write(fd, buf, (sizeof buf) - 1);
	printf("[open_file_only_write] read %d: %s\n", (int)sz, buf);

	close(fd);
}
static void open_file_read_write() {
	int fd = open("File_exp1", O_RDWR);
	char buf[16];
	memset(buf, 0, sizeof buf);
	ssize_t sz = read(fd, buf, (sizeof buf) - 1);
	printf("[open_file_read_write] read %d: %s\n", (int)sz, buf);

	//lseek(fd, 0, SEEK_SET);
	memset(buf, 'D', 1);
	sz = write(fd, buf, 1);
	printf("[open_file_read_write] read %d: %s\n", (int)sz, buf);

	close(fd);
}
void File_exp1() {
	create_file();
	open_file_only_read();
	open_file_only_write();
	open_file_read_write();
}