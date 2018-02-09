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
	char c;
	for(c = 'a'; c <= 'z'; c++)
		*msg++ = c;
	*msg = 0;

	while(msg[0] != '*')
		sleep(1);

}