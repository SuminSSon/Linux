#include <stdio.h>

#define	MAX_BUF	256

main(int argc, char *argv[])
{
	FILE	*fp;
	char	buf[MAX_BUF];
	int		line;

	if (argc != 2)  {
		printf("Usage: %s filename\n", argv[0]);
		exit(1);
	}

	if ((fp = fopen(argv[1], "rt")) == NULL)  { // argv[1]을 text로 read
		perror("fopen");
		exit(1);
	}

	line = 1;
	while (fgets(buf, MAX_BUF, fp))  { // fp를 MAX_BUF만큼 buf에 저장
		printf("%4d: %s", line++, buf);
	}

	fclose(fp);
}
