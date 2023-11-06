#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

main()
{
	int		pid;

	if ((pid = fork()) < 0 )  {
		perror("fork");
		exit(1);
	}
	else if (pid == 0)  { // pid가 0이면 child process 실행
		/* child */
		printf("I am %d. My parent is %d.\n", getpid(), getppid()); // getppid는 parent process id
	}
	else  { // pid가 0이상이면 parent process 실행
		/* parent */
		printf("I am %d. My child is %d.\n", getpid(), pid); // getpid는 현재 프로세스 id, pid는 자식 id
	}
}
