#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <dirent.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <time.h>

void display_file_type(mode_t st_mode){
	if(S_ISREG(st_mode))
		printf("Regular File");
	else if(S_ISDIR(st_mode))
		printf("Directory");
	else if(S_ISFIFO(st_mode))
		printf("Fifo File");
	else if(S_ISCHR(st_mode))
		printf("Character special File");
	else if(S_ISBLK(st_mode))
		printf("Block File");
	else if(S_ISSOCK(st_mode))
		printf("Socket File");
}

void display_access_perm(mode_t st_mode){
	int i, j;
	char per[] = "rwxrwxrwx";
	char amode[10];
	for(i = 0, j = 1<<8; i < 9; i++, j >>= 1)
		amode[i] = (j & st_mode)?per[i]:'-';

	if(st_mode & S_ISUID)
		amode[2] = (amode[2] == 'x')?'S':'s';
	if(st_mode & S_ISGID)
		amode[5] = (amode[5] == 'x')?'G':'g';
	if(st_mode & S_ISVTX)
		amode[8] = (amode[8] == 'x')?'T':'t';

	amode[9] = 0;
	printf("%s", amode);
}

void display_file(struct stat mystat){
	printf("File Type: ");
	display_file_type(mystat.st_mode);
	printf("\nNumber of links: %lu\nPermissions: ", mystat.st_nlink);
	display_access_perm(mystat.st_mode);
	char * str = (char *)malloc(sizeof(char) * 50);
	str = ctime(&mystat.st_atime);
	printf("\nLast access time: %s\n", str);
}

void display_dir(const char * dirname){
	DIR * dir;
	struct dirent * mydirent;
	dir = opendir(dirname);
	while((mydirent = readdir(dir)) != NULL){
		printf("File Name: %s\n", mydirent->d_name);
		struct stat mystat;
		if(stat(mydirent->d_name, &mystat) < 0){
			perror("");
			exit(0);
		}
		display_file(mystat);
	}
}

int main(int argc, char const *argv[]){
	if(argc < 2){
		perror("");
		exit(0);
	}

	struct stat mystat;
	if(stat(argv[1], &mystat) < 0){
		perror("");
		exit(0);
	}

	if(S_ISDIR(mystat.st_mode))
		display_dir(argv[1]);
	else{
		printf("File Name: %s\n", argv[1]);
		display_file(mystat);
	}
}