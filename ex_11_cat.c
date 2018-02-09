#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#define size 1024
#define cint sizeof(char)

int main(int argc, char const *argv[]){
	if(argc < 2){
		perror("Please provide Source file as argument.");
		exit(0);
	}
	int sfd = open(argv[1], O_RDONLY);
	if(sfd < 0){
		perror("Invalid Source file path");
		exit(0);
	}

	int len;
	char buff[size];
	while((len = read(sfd, buff, size * cint)))
		write(1, buff, len * cint );
	

}