#include <stdio.h>
#include <unistd.h>

#define	MAX_BUF	256

main(int argc, char *argv[])
{
	char	buf[MAX_BUF];

	if (getcwd(buf, MAX_BUF) < 0)  { // 현재 dir를 알아내서 MAX_BUF만큼 buf에 저장
		perror("getcwd");
		exit(1);
	}

	printf("%s\n", buf);
}
