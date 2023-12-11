#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

#define MAX_BUF 128

main()
{
	int	n, fd[2], fd2[2];
	pid_t	pid;
	char	buf[MAX_BUF];

	if(pipe(fd) < 0){ // pipe로 2개의 파일 디스크립터를 생성하고 하나의 pipe를 process들이 공유
		perror("pipe");
		exit(1);
	}

	if(pipe(fd2) <0){
		perror("pipe");
		exit(1);
	}

	if((pid = fork()) < 0)
	{
		perror("fork");
		exit(1);
	}

	else if (pid == 0) // Child process
	{
		printf("Child : Wait for parent to send data\n");
		if((n = read(fd[0], buf, MAX_BUF)) < 0){ // MAX_BUF만큼 buf에 fd[0]을 read
			perror("read");
			exit(1);
		}
		printf("Child : Received data from parent: ");
		fflush(stdout); // 버퍼 내에 데이터 바로 출력
		write(STDOUT_FILENO, buf, n); // buf를 화면에 출력

		printf("Child: Send data to parent\n");
		strcpy(buf, "Child to Parent\n");
		write(fd2[1], buf, strlen(buf)+1); // pipe에 write

	}
	else{
		strcpy(buf, "Parent to Child\n");
		printf("Parent: Send data to child\n"); 
		write(fd[1], buf, strlen(buf)+1); // pipe에 write

		printf("Parent : Wait for child to send data\n");
		if((n = read(fd2[0], buf, MAX_BUF)) < 0){ // MAX_BUF만큼 buf에 fd2[0]을 read
			perror("read");
			exit(1);
		}
		printf("Parent : Received data from child: ");
		fflush(stdout); // 버퍼 내에 데이터 바로 출력
		write(STDOUT_FILENO, buf, n); // buf를 화면에 출력
	}

	exit(0);
}

