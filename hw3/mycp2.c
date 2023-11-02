#include <stdio.h>

#define	MAX_BUF	1024

main(int argc, char *argv[])
{
	FILE	*src, *dst;
	char	buf[MAX_BUF];
	int		count;

	if (argc != 3)  {
		fprintf(stderr, "Usage: %s source destination\n", argv[0]);
		exit(1);
	}

	if ((src = fopen(argv[1], "rb")) == NULL)  { // argv[1]을 fopen으로open하고   binary로 read해서 반환되는 pointer를 src에 저장
		perror("fopen");
		exit(1);
	}

	if ((dst = fopen(argv[2], "wb")) == NULL)  { // argv[2]을 fopen으로open하고 binary로 write해서 반환되는 pointer를 dst로 저장
		perror("fopen");
		exit(1);
	}

	while ((count = fread(buf, 1, MAX_BUF, src)) > 0)  { // src를 MAX_BUF만큼 read 하여 buf에 저장
		fwrite(buf, 1, count, dst); // dst에 count만큼 buf을 wrtie함.
	}

	fclose(src);
	fclose(dst);
}
