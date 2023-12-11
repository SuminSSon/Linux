#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

#define	MAX_BUF	128

main()
{
	int		n, fd[2];
	pid_t	pid;
	char	buf[MAX_BUF];

	if (pipe(fd) < 0)  { // pipe로 2개의 파일 디스크립터를 생성하고 하나의 pipe를 process들이 공유
		perror("pipe");
		exit(1);
	}

	if ((pid = fork()) < 0)  {
		perror("fork");
		exit(1);
	}
	else if (pid == 0)  { // Child process
		close(fd[1]); // pipe 쓰기모드 닫기
		printf("Child : Wait for parent to send data\n");
		if ((n = read(fd[0], buf, MAX_BUF)) < 0)  { // MAX_BUF만큼 buf에fd[0]을 읽음
			perror("read");
			exit(1);
		}
		printf("Child : Received data from parent: ");
		fflush(stdout); // 버퍼 내에 데이터 바로 출력
		write(STDOUT_FILENO, buf, n); // buf 내용을 화면에 출력
	}
	else  {
		close(fd[0]); // pipe 읽기모드 닫기
		strcpy(buf, "Hello, World!\n");
		printf("Parent: Send data to child\n");
		write(fd[1], buf, strlen(buf)+1); // pipe에 buf를 write
	}

	exit(0);
}
