#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>

void display_file_type(mode_t st_mode){
	if(S_ISREG(st_mode))
		printf("-");
	else if(S_ISDIR(st_mode))
		printf("d");
	else if(S_ISFIFO(st_mode))
		printf("p");
	else if(S_ISCHR(st_mode))
		printf("c");
	else if(S_ISBLK(st_mode))
		printf("b");
	else if(S_ISSOCK(st_mode))
		printf("s");
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

void display_rest(struct stat mystat){
	printf(" %lu", mystat.st_nlink);
	struct group *grp = getgrgid(mystat.st_gid);
	struct passwd *usr = getpwuid(mystat.st_uid);
	printf(" %s %s", usr->pw_name, grp->gr_name);
	printf(" %ld", mystat.st_size);
	// char *str = (char *)malloc(50 * sizeof(char));
	// str = ctime(&mystat.st_mtime);
	// printf(" %s", str);
	printf(" %ld", mystat.st_mtime);

}

int main(int argc, char * argv[]){
	if(argc != 2){
		perror("");
		exit(0);
	}
	int fd;
	if((fd = open(argv[1], O_RDONLY)) < 0){
		perror("In open");
		exit(0);
	}

	struct stat mystat;
	if(stat(argv[1], &mystat) < 0){
		perror("In fstat");
		exit(1);
	}
	display_file_type(mystat.st_mode);
	display_access_perm(mystat.st_mode);
	display_rest(mystat);
	printf(" %s", argv[1]);
}