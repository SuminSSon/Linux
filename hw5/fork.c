#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int		Var = 6;
char	Buf[] = "a write to stdout\n";

main()
{
	int		var;
	pid_t	pid;

	var = 88;
	write(STDOUT_FILENO, Buf, sizeof(Buf)-1);
	printf("Before fork\n");

	if ((pid = fork()) < 0)  { // fork()시 오류 나면 peoor실행하고 exit
		perror("fork");
		exit(1);
	}
	else if (pid == 0)  { // pid가 0이면 자식 process 실행
		/* child */
		Var++;
		var++;
	}
	else  { // pid가 0이상이면 parent process 실행
		/* parent */
		sleep(2);
	}

	// fork는 메모리도 복사됨. child process의 Var, var값이 바뀌어도 parent process에 영향이 가지 않음
	printf("pid = %d, Var = %d, var = %d\n", getpid(), Var, var);
}
