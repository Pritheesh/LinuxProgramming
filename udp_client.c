#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <string.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <unistd.h>
#define saddr sizeof(struct sockaddr_in)

typedef struct{
	char pname[15];
	int a, b;
	int res;
}req;

int main(int argc, char * argv[]){
	socklen_t socklen = saddr;
	int lsockfd;
	struct sockaddr_in serv_addr;
	lsockfd = socket(AF_INET, SOCK_DGRAM, 0);
	memset(&serv_addr, 0, saddr);
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(1234);
	serv_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
	//connect(lsockfd, (struct sockaddr *) &serv_addr, saddr);
	req newreq;
	memset(&newreq, 0, sizeof(req));
	strcpy(newreq.pname, argv[1]);
	newreq.a = atoi(argv[2]);
	newreq.b = atoi(argv[3]);
	sendto(lsockfd, &newreq, sizeof(req), 0, (struct sockaddr *)&serv_addr, socklen);
	recvfrom(lsockfd, &newreq, sizeof(req), 0, (struct sockaddr *)&serv_addr, &socklen);
	printf("Result is %d", newreq.res);
}
