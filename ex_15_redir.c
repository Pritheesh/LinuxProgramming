#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <dirent.h>
int main(int argc, char *argv[]){
	DIR *pdir;
	struct dirent * pdirent;
	pdir = opendir(".");
	FILE * fp = fopen(argv[2], "w");

    while((pdirent = readdir(pdir)) != NULL)
        fprintf(fp, "%s\n", pdirent->d_name);

    closedir(pdir);
	return 0;
}