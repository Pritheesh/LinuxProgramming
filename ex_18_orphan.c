#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main(){
	pid_t p = fork();
	if(p == 0){
		sleep(5);
		printf("Child");
	}
	else
		printf("Parent");
	return 0;
}