#include <stdio.h>

main(int argc, char *argv[])
{
	FILE	*src, *dst;
	int		ch;

	if (argc != 3)  {
		fprintf(stderr, "Usage: %s source destination\n", argv[0]);
		exit(1);
	}

	if ((src = fopen(argv[1], "rt")) == NULL)  {
		perror("fopen");
		exit(1);
	}

	if ((dst = fopen(argv[2], "wt")) == NULL)  {
		perror("fopen");
		exit(1);
	}

	while ((ch = fgetc(src)) != EOF)  { // src에 한 글자씩 ch에 저장
		fputc(ch, dst); // dst에 ch  저장
	}

	fclose(src);
	fclose(dst);
}
