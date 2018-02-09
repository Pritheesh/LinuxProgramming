#include <sys/msg.h>
#include <stdio.h>
#include <sys/ipc.h>
#include <stdlib.h>

typedef struct{
	long mtype;
	int num;
}msgbuf;

int main(){
	int msgid = msgget(1234, IPC_CREAT|0666);
	if(msgid < 0){
		perror("");
		exit(0);
	}
	msgbuf msg;
	int count = 0;
	while(count < 3){
		msgrcv(msgid, &msg, sizeof(int), -4, 0);
		printf("Msg of type %ld is %d\n", msg.mtype, msg.num);
		++count;
	}

}