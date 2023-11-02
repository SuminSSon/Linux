#include <stdio.h>
#include <string.h>
#include "record.h"

main(int argc, char *argv[])
{
	FILE	*src, *dst;
	Record	rec;

	if (argc != 3)  {
		fprintf(stderr, "Usage: %s source dest\n", argv[0]);
		exit(1);
	}

	if ((src = fopen(argv[1], "rt")) == NULL)  { // argv[1] 파일을 오픈하여text로 읽고 read하여 src에 저장
		perror("fopen");
		exit(1);
	}
	if ((dst = fopen(argv[2], "wb")) == NULL)  { // argv[2]파일을 오픈하여 binary로 write하고 dst에 저장
		perror("fopen");
		exit(1);
	}

	while (fgets(rec.stud, SMAX, src))  { // src를 SMAX만큼 read하여  rec.stud에 저장
		*strchr(rec.stud, '\n') = '\0'; // strchr을 통해 rec.stud에 \n을 찾아서 \0으로 바꿈
		fgets(rec.num, NMAX, src); // src를 NMAX만큼 read하여 rec.num에 저장
		*strchr(rec.num, '\n') = '\0';
		fgets(rec.dept, DMAX, src); // src를 DMAX만큼 read하여 rec.dept에 저장
		*strchr(rec.dept, '\n') = '\0';

		fwrite(&rec, sizeof(rec), 1, dst); // dst에 rec를 rec size만큼 1  write 
	}

	fclose(src);
	fclose(dst);
}
