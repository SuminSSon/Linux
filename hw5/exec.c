#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

main()
{
	pid_t	pid;
	char	*argv[] = { "mycp", "exec.c", "exec2.c", NULL };

	// execl
	if ((pid = fork()) < 0)  {
		perror("fork");
		exit(1);
	}
	else if (pid == 0)  {
		// mycp exec.c exec2.c
		if (execl("/home/cjs/lsp/file-io/mycp","mycp","exec.c","exec2.c",NULL)<0)  { // 해당 path에 있는 list로 입력을 받은 파일을 실행시킴.
			perror("execl");
			exit(1);
		}
	}
	if (waitpid(pid, NULL, 0) < 0)  { // child process가 끝나기를 기다림
		perror("waitpid");
		exit(1);
	}

	// execv
	if ((pid = fork()) < 0)  {
		perror("fork");
		exit(1);
	}
	else if (pid == 0)  {
		// mycp exec.c exec2.c
		if (execv("/home/cjs/lsp/file-io/mycp",argv)<0)  { // 해당 path에 있는 vector에 들어있는 파일을 실행
			perror("execv");
			exit(1);
		}
	}
	if (waitpid(pid, NULL, 0) < 0)  {
		perror("waitpid");
		exit(1);
	}

	// execlp
	if ((pid = fork()) < 0)  {
		perror("fork");
		exit(1);
	}
	else if (pid == 0)  {
		// execute 'env' from PATH
		if (execlp("env","env",NULL)<0)  { // 해당 filename을 실행.  인수 중복:  arg[0]은 프로그램 전체 이름, arg[1]은 프로그램 이름을 다시 지정
			perror("execlp");
			exit(1);
		}
	}
	if (waitpid(pid, NULL, 0) < 0)  {
		perror("waitpid");
		exit(1);
	}
}
