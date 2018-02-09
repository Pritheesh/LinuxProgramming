#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include <stdlib.h>

int main(){
	int id = shmget(1235, sizeof(char) * 27, IPC_CREAT|0666);
	if(id < 0){
		perror("");
		exit(0);
	}

	char * msg = shmat(id, NULL, 0);
	while(*msg){
		putchar(*msg++);														
	}
	msg[0] = '*';
	printf("\n");
}