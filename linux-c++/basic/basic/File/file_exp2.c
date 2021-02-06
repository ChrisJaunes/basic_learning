/*
* Designed a exp about file api of ANSI C
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
	FILE *fd = fopen("File_exp2", "w+");
	if (fd < 0) {
		printf("[create_file Error] don't create file, code : %d\n", fd);
		return;
	}
	getStat(fileno(fd));
	char buf[16];
	memset(buf, 'A', sizeof(buf));
	fwrite(buf, sizeof(buf), 1, fd);
	fclose(fd);
}
static void open_file_only_read() {
	FILE *fd = fopen("File_exp2", "r");
	char buf[16];
	memset(buf, 0, sizeof buf);
	ssize_t sz = fread(buf, (sizeof buf) - 1, 1, fd);
	printf("[open_file_only_read] read %d: %s\n", (int)sz, buf);

	memset(buf, 'B', 8);
	fseek(fd, 0, SEEK_SET);
	sz = fwrite(buf, 8, 1, fd);
	printf("[open_file_only_read] read %d\n", (int)sz);

	memset(buf, 0, sizeof buf);
	fseek(fd, 0, SEEK_SET);
	sz = fread(buf, (sizeof buf) - 1, 1, fd);
	printf("[open_file_only_read] read %d: %s\n", (int)sz, buf);

	fclose(fd);
}
static void open_file_only_write() {
	FILE *fd = fopen("File_exp2", "w");
	struct stat fd_stat;
	fstat(fileno(fd), &fd_stat);
	printf("[open_file_only_write] size : %d\n", fd_stat.st_size);
	fwrite("AAAAAAAAAAAAAAAA", 16, 1, fd);
	fclose(fd);
}
static void open_file_read_write() {
	FILE *fd = fopen("File_exp2", "r+");
	char buf[16];
	memset(buf, 0, sizeof buf);
	ssize_t sz = fread(buf, (sizeof buf) - 1, 1, fd);
	printf("[open_file_read_write] read %d: %s\n", (int)sz, buf);

	//lseek(fd, 0, SEEK_SET);
	memset(buf, 'D', 1);
	sz = fwrite(buf, 1, 1, fd);
	printf("[open_file_read_write] read %d: %s\n", (int)sz, buf);

	close(fd);
}
void File_exp2() {
	create_file();
	open_file_only_read();
	open_file_only_write();
	open_file_read_write();
}