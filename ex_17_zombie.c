#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main(){
	pid_t p = fork();
	if(p == 0){
		printf("Child");
		exit(0);
	}
	else{
		sleep(5);
		printf("Parent");
	}
	return 0;
}