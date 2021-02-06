/*
* Designed a exp about dir api of POSIX
* use #define  _GNU_SOURCE if need include get_current_dir_name
* @author ChrisJuanes
*/
#define  _GNU_SOURCE
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <malloc.h>

static void getStat(const int fd) {
	struct stat fd_stat;
	fstat(fd, &fd_stat);
	printf("[getStat] Name : %d\n", fd_stat.st_uid);
	printf("[getStat] Mode : %x\n", fd_stat.st_mode);
}
static void create_dir() {
	int fd = mkdir("file_exp3", S_IRWXU | S_IRGRP | S_IXGRP | S_IRGRP);
	if (fd < 0) {
		printf("[create_dir Error] don't create file, code : %d\n", fd);
		chdir("file_exp3");
		return;
	}
	const char* path1 = get_current_dir_name();
	printf("[create_dir] current dir : %s\n", path1);
	chdir("file_exp3");
	const char* path2 = get_current_dir_name();
	printf("[create_dir] current dir : %s\n", path2);
	creat("A", S_IRWXU);
	creat("B", S_IRWXU);
	creat("C", S_IRWXU);
	close(fd);
}
static void open_dir() {
	printf("[create_dir] current dir : %s\n", (const char *)get_current_dir_name());
	chdir("..");
	printf("[create_dir] current dir : %s\n", (const char*)get_current_dir_name());

	struct DIR* dir = opendir("file_exp3");
	struct dirent* ent = (struct dirent *) malloc(sizeof(struct dirent));

	while ((ent = readdir(dir)) != NULL) {
		printf("[open_dir] -- %s\n", ent->d_name);
	}
	closedir(dir);
}
void File_exp3() {
	create_dir();
	open_dir();
}