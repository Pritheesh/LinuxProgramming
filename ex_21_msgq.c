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
	msg.mtype = 1;
	msg.num = 5;
	msgsnd(msgid, &msg, sizeof(int), 0);
	msg.mtype = 2;
	msg.num = 10;
	msgsnd(msgid, &msg, sizeof(int), 0);
	msg.mtype = 3;
	msg.num = 15;
	msgsnd(msgid, &msg, sizeof(int), 0);
	

}