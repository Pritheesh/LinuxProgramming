#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>

int main(){

	if(mkfifo("test.fifo", O_CREAT|0666) < 0){
		perror("");
		exit(0);
	}

	int fd = open("test.fifo", O_WRONLY);
	char msg1[] = "hello";
	write(fd, msg1, strlen(msg1));
}