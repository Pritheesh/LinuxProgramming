#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>

int main(int argc, char * argv[]){
	int pd[2];
	pipe(pd);
	pid_t pid = fork();

	if(pid == 0){
		close(pd[0]);
		dup2(pd[1], 1);
		close(pd[1]);
		//execlp(argv[1], argv[1], NULL);
		system(argv[1]);
		exit(0);
	}
	else{
		wait();
		close(pd[1]);
		dup2(pd[0], 0);
		close(pd[0]);
		//execlp(argv[2], argv[2], NULL);
		system(argv[2]);
	}
	return 0;
}