/*
* Designed a exp about dir api of POSIX
* use #define  _GNU_SOURCE if need include get_current_dir_name;
* dot and dotdot have same d_ino, why?;
* https://stackoverflow.com/questions/66084223/dot-and-dotdot-have-same-d-ino-but-different-stat-st-ino-why
* .. is a symbolic link to a parent directory. You may see this: d_type is DT_LINK.
  d_ino value for a symbolic link is unspecified in POSIX standard for the function readdir. 
  It means, this may have any value, probably d_ino has an unchanged value assigned for a previous direntry.
  st_ino returns a real inode number of a symbolic link.
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
	chdir("file_exp3");
	while ((ent = readdir(dir)) != NULL) {
		struct stat ent_stat;
		int fd = open(ent->d_name, O_RDWR);
		stat(ent->d_name, &ent_stat);
		printf("[open_dir] ent->d_ino : %llu, ent_stat.st_ino : %llu, fd : %d\n", ent->d_ino, ent_stat.st_ino, fd);
		printf("[open_dir] -- %s\n", ent->d_name);
		close(fd);
	}
	closedir(dir);
}
void File_exp3() {
	create_dir();
	open_dir();
}