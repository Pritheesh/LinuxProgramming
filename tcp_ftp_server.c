#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <string.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#define saddr sizeof(struct sockaddr_in)

typedef struct{
	int type; //put = 1 get = 0
	char filename[25];
	char data[4096];
}req;

int main(){
	int lsockfd, newsockfd;
	struct sockaddr_in serv_addr, cli_addr;
	socklen_t socklen = saddr;
	lsockfd = socket(AF_INET, SOCK_STREAM, 0);
	memset(&serv_addr, 0, saddr);
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(1101);
	serv_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
	bind(lsockfd, (struct sockaddr *) &serv_addr, saddr);
	listen(lsockfd, 10);
	memset(&cli_addr, 0, socklen);
	newsockfd = accept(lsockfd, (struct sockaddr *)&cli_addr, &socklen);
	req newreq;
	memset(&newreq, 0, sizeof(req));
	int size = read(newsockfd, &newreq, sizeof(newreq));

	if(newreq.type == 1){
		int fd = open(newreq.filename, O_WRONLY|O_CREAT, 0666);
		int written = write(fd, newreq.data, strlen(newreq.data));
		if(written < 0){
			perror("Error writing");
			exit(1);
		}
		memset(&newreq, 0, sizeof(req));
		strcpy(newreq.data, "Download complete");
		write(newsockfd, &newreq, sizeof(newreq));
	}

	else{
		int fd = open(newreq.filename, O_RDONLY);
		if(fd < 0){
			perror("Could not open file");
			exit(0);
		}
		int uploaded = read(fd, newreq.data, 4096);
		write(newsockfd, &newreq, sizeof(req));
		printf("%d bytes uploaded\n", uploaded);
	}

}