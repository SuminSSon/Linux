#include <stdio.h>
#include <signal.h>
#include <pthread.h>

// SIGCHILD 호출시 출력
void
SigCHLDHandler(int signo)
{
    printf("Received a SIGCHLD \n");
}

main()
{
	pid_t	pid;
	signal(SIGCHLD,SigCHLDHandler); // SIGCHILD 등록
	if ((pid = fork()) < 0)  {
		perror("fork");
		exit(1);
	}
	else if (pid == 0)  {
		printf("I'm a child\n");
	}
	else  {
		while(1)
			;
	}

}
