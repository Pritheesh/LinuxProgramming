#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <fcntl.h>	
#define saddr sizeof(struct sockaddr_in)

typedef struct{
	int type; //put = 1 get = 0
	char filename[25];
	char data[4096];
}req;

int main(int argc, char * argv[]){
	int lsockfd;
	struct sockaddr_in serv_addr;
	lsockfd = socket(AF_INET, SOCK_STREAM, 0);
	memset(&serv_addr, 0, saddr);
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(1101);
	serv_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
	connect(lsockfd, (struct sockaddr *) &serv_addr, saddr);
	req newreq;

	memset(&newreq, 0, sizeof(req));
	newreq.type = atoi(argv[1]);
	strcpy(newreq.filename, argv[2]);

	if(newreq.type == 0){
		write(lsockfd, &newreq, sizeof(req));
		read(lsockfd, &newreq, sizeof(req));
		int fd = open(newreq.filename, O_WRONLY|O_CREAT, 0666);
		int written = write(fd, newreq.data, strlen(newreq.data));
		printf("%d bytes downloaded\n", written);
	}

	else{
		int fd = open(newreq.filename, O_RDONLY);
		read(fd, newreq.data, 4096);
		write(lsockfd, &newreq, sizeof(req));
		read(lsockfd, &newreq, sizeof(req));
		printf("%s\n", newreq.data);
	}
}