#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>

int main(){

	// if(mkfifo("test.fifo", O_CREAT|O_EXCL|0666) < 0){
	// 	perror("");
	// 	exit(0);
	// }

	int fd = open("test.fifo", O_RDONLY);
	char msg[100];
	read(fd, msg, 100);
	printf("Message is %s\n", msg);
}