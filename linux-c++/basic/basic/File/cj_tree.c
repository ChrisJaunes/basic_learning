/*
* a simple implement about tree
* todo : decorator pattern used
* check return value when we enter one directory, it will ub if we don't enter one directory and execute chdir("..")
* version 1.0 (2021/02/07)
* @author chrisjaunes
*/
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>

static char* myitoa(int value, char* string, int radix) {
	int rt = 0;
	if (string == NULL) return NULL;
	if (radix <= 0 || radix > 30) return NULL;
	rt = snprintf(string, radix, "%d", value);
	if (rt > radix) return NULL;
	string[rt] = '/0';
	return string;
}
static const char const* get_ctime(const time_t* ti) {
	static char d_ct[100];
	char* s_ct = ctime(ti);
	strcpy(d_ct, s_ct);
	d_ct[strlen(d_ct) - 1] = '\0';
	return d_ct;
}
static void tree_print(int8_t dep, struct stat *st, const char * name) {
	while (dep-- > 0) printf("|  ");
	printf("|--");
	printf("%x | ", st->st_mode);
	printf("%d | ", st->st_uid);
	printf("%d | ", st->st_gid);
	printf("%10d | ", st->st_size);
	printf("%s | ", get_ctime((const time_t*)&st->st_mtime));
	printf("%s | ", get_ctime((const time_t*)&st->st_atime));
	printf("%s | ", get_ctime((const time_t*)&st->st_ctime));
	printf("%s\n", name);
}
static void deal_dir(const int8_t dep, const int8_t mx_dep) {
	if (dep >= mx_dep) return;
	DIR* dir = opendir(".");
	struct dirent *ent;
	while ((ent = readdir(dir)) != NULL) {
		if (strcmp(ent->d_name, ".") == 0 || strcmp(ent->d_name, "..") == 0) continue;
		int fd = open(ent->d_name, O_RDONLY);
		struct stat fdstat;
		fstat(fd, &fdstat);
		tree_print(dep, &fdstat, ent->d_name);
		if (strncmp(ent->d_name, "linux-4.9.229.tar.xz", 20) == 0) {
			int x = 0;
			x += 0;
		}
		if (S_ISDIR(fdstat.st_mode)) {
			int ret = chdir(ent->d_name);
			if (ret < 0) {
				printf("[ERROR] don't enter directory");
			}
			else {
				deal_dir(dep + 1, mx_dep);
				chdir("..");
			}
		}
		close(fd);
	}
	closedir(dir);
}

void cj_tree(const char *path, const int8_t mx_dep) {
	chdir(path);
	printf("[cj_tree] %s\n", get_current_dir_name());
	deal_dir(0, mx_dep);
}