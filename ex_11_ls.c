#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <dirent.h>
#include <sys/types.h>

int main(int argc, char const *argv[]){
	DIR *pdir;
	struct dirent * pdirent;
	if(argc == 1)
		pdir = opendir(".");
	else
		pdir = opendir(argv[1]);

    while((pdirent = readdir(pdir)) != NULL)
        printf("%s\n", pdirent->d_name);

    closedir(pdir);
	return 0;
}