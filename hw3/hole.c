#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

main()
{
	int 	fd;
	char	ch = '\0';

	if ((fd = creat("file.hole", 0400)) < 0)  { //  file.hole을 생성할 때 소유자는 read-only 권한을 가진다.
		perror("creat");
		exit(1);
	}

	if (lseek(fd, 1023, SEEK_SET) < 0)  { // fd를 1023byte로 포인터가 이동
		perror("lseek");
		exit(1);
	}
	write(fd, &ch, 1); // fd에 NULL을 1번 write. 그 앞은 0으로 채워짐.

	close(fd);
}
