#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>

main()
{
	pid_t	pid;
	int		status;

	if ((pid = fork()) < 0)  { // child process 실행
		perror("fork");
		exit(1);
	}
	else if (pid == 0)  {
		printf("I'm a child\n");
		sleep(2); // 2초뒤에 종료 
	}
	else  {
		wait(&status);	// child process가 끝날 때까지 기다림
		printf("A child killed with %d status\n", status);
	}
}
