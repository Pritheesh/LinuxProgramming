#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>

int main(int argc, char const *argv[]){
	DIR *pdir;
	struct dirent * pdirent;
	struct stat mystat;
	if(argc == 1)
		pdir = opendir(".");
	else
		pdir = opendir(argv[1]);

    while((pdirent = readdir(pdir)) != NULL){
    	stat(pdirent->d_name, &stat);
        printf("%s %lu\n", pdirent->d_name, pdirent->d_ino);
    }

    closedir(pdir);
	return 0;
}