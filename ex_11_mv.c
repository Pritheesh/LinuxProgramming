#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#define size 1024
#define cint sizeof(char)

int main(int argc, char const *argv[]){
	if(argc < 3){
		perror("Please provide Source file and destination file names as arguments.");
		exit(0);
	}
	int sfd = open(argv[1], O_RDONLY);
	if(sfd < 0){
		perror("Invalid Source file path");
		exit(0);
	}

	int dfd = open(argv[2], O_CREAT|O_EXCL|O_WRONLY, 0666);
	if(dfd < 0){
		perror("Error creating file");
		exit(0);
	}

	int len, total = 0;
	char buff[size];
	while((len = read(sfd, buff, size * cint))){
		write(dfd, buff, len * cint );
	}
	unlink(argv[1]);

	return 0;
}