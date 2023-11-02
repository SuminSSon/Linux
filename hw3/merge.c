#include <stdio.h>

#define	MAX_BUF	1024

main(int argc, char *argv[])
{
	FILE	*src1, *src2, *dst;
	char	buf[MAX_BUF];
	int		count;

	if (argc != 4)  {
		fprintf(stderr, "Usage: %s source1 source2 dest\n", argv[0]);
		exit(1);
	}

	if ((src1 = fopen(argv[1], "rb")) == NULL)  { // argv[1]을 binary로 read하여 반환받은 포인터를 src1에 저장
		perror("fopen");
		exit(1);
	}
	if ((src2 = fopen(argv[2], "rb")) == NULL)  { // argv[2]를 binary로 read하여 반환받은 포인터를 rc2에 저장
		perror("fopen");
		exit(1);
	}
	if ((dst = fopen(argv[3], "wb")) == NULL)   { // argv[3]을 binary로 write하여 반환받은 포인터를 dst에 저장
		perror("fopen");
		exit(1);
	}

	while ((count = fread(buf, 1, MAX_BUF, src1)) > 0)  { // src1을 MAX_BUF만큼1번 read하고 buf에 저장. 반환된 read한 수를 count에 저장.
		fwrite(buf, 1, count, dst); // buf 데이터 중 count만큼 dst에write
	}

	// 위와 동일하게 수행. 
	while ((count = fread(buf, 1, MAX_BUF, src2)) > 0)  {
		fwrite(buf, 1, count, dst);
	}

	fclose(src1);
	fclose(src2);
	fclose(dst);
}
