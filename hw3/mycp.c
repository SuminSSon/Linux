#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

#define	MAX_BUF	1024

main(int argc, char *argv[])
{
	int 	fd1, fd2, count;
	char	buf[MAX_BUF];

	if (argc != 3)  {
		printf("Usage: %s source destination\n", argv[0]);
		exit(1);
	}

	if ((fd1 = open(argv[1], O_RDONLY)) < 0)  { // argv[1]을read로 open하여 fd1에 저장
		perror("open");
		exit(1);
	}

	if ((fd2 = open(argv[2], O_WRONLY | O_CREAT | O_TRUNC, 0644)) < 0)  { // argv[2]는 write, create, trunc 모드로 open하여 fd2에 저장하고 644 권한 지정.
		perror("open");
		exit(1);
	}

	// fd1 내용을 read하여 fd2에write
	while ((count = read(fd1, buf, MAX_BUF)) > 0)  {
		write(fd2, buf, count);
	}

	close(fd1);
	close(fd2);
}
