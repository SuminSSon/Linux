#include <stdio.h>
#include <unistd.h>

#define	MAX_BUF	1024

long
filesize(FILE *fp)
{
	long	cur, size;

	cur = ftell(fp); // stream의 현재 위치 저장
	fseek(fp, 0L, SEEK_END); // SEEK_END로 fp의 위치를 옮긴다.
	size = ftell(fp); // 현위치가 맨 마지막이니 size에 저장
	fseek(fp, cur, SEEK_SET); // size를 구한 후 다시 원래 위치로 fp를 올김
	return(size);
}

main(int argc, char *argv[])
{
	FILE	*src, *dst1, *dst2;
	char	buf[MAX_BUF];
	int		count, size;

	if (argc != 4)  {
		fprintf(stderr, "Usage: %s source dest1 dest2\n", argv[0]); // stderr에 출력
		exit(1);
	}

	if ((src = fopen(argv[1], "rb")) == NULL)  {
		perror("fopen");
		exit(1);
	}
	if ((dst1 = fopen(argv[2], "wb")) == NULL)  {
		perror("fopen");
		exit(1);
	}
	if ((dst2 = fopen(argv[3], "wb")) == NULL)  {
		perror("fopen");
		exit(1);
	}

	size = filesize(src) / 2; // src의 filesize를 절반으로 나누어서 size에 저장

	while (size > 0)  {
		count = (size > MAX_BUF) ?  MAX_BUF : size; // size와 MAX_BUF 중 작은 것을 count에저장 
		fread(buf, 1, count, src); // src에서 count만큼 읽어서 buf에 저장 
		fwrite(buf, 1, count, dst1); // bufㄹ를 count만큼 write
		size -= count;
	}

	while ((count = fread(buf, 1, MAX_BUF, src)) > 0)  {
		fwrite(buf, 1, count, dst2); // 나머지 절반을 dst2에 write함
	}

	fclose(src);
	fclose(dst1);
	fclose(dst2);
}
