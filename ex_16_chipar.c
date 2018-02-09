#include <stdio.h>
#include <unistd.h>

int main(){
	pid_t p = fork();
	if(p == 0)
		printf("Child");
	else
		printf("Parent\n");
	return 0;
}