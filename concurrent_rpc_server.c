#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <string.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#define saddr sizeof(struct sockaddr_in)

typedef struct{
	char pname[15];
	int a, b;
	int res;
}req;

void add(req *newreq){
	newreq->res = newreq->a + newreq->b;
}

void sub(req *newreq){
	newreq->res = newreq->a - newreq->b;
}
void mul(req *newreq){
	newreq->res = newreq->a * newreq->b;
}

void divi(req *newreq){
	newreq->res = newreq->a / newreq->b;
}

void child(int * fd){
	int sock = *fd;
	req newreq;
	read(sock, &newreq, sizeof(req));
	char * procs[] = { "add", "mul", "sub", "div"};
	int res;
	if(!strcmp(procs[0], newreq.pname))
		add(&newreq);
	else if(!strcmp(procs[1], newreq.pname))
		mul(&newreq);
	else if(!strcmp(procs[2], newreq.pname))
		sub(&newreq);
	else if (!strcmp(procs[3], newreq.pname))
		divi(&newreq);
	write(sock, &newreq, sizeof(req));
	close(sock);
	free(fd);
	exit(0);
}


int main(){
	int lsockfd, * newsockfd;
	struct sockaddr_in serv_addr, cli_addr;
	socklen_t socklen = saddr;
	lsockfd = socket(AF_INET, SOCK_STREAM, 0);
	memset(&serv_addr, 0, saddr);
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(1101);
	serv_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
	bind(lsockfd, (struct sockaddr *) &serv_addr, saddr);
	listen(lsockfd, 10);
	while(1){
		socklen = saddr;
		memset(&cli_addr, 0, saddr);
		newsockfd = (int *)malloc(sizeof(int));
		*newsockfd = accept(lsockfd, (struct sockaddr *)&cli_addr, &socklen);
		pid_t p = fork();
		if(p == 0){
			child(newsockfd);
			close(lsockfd);
			exit(0);
		}
	}
}