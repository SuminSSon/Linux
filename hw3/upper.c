#include <stdio.h>

void
myupper(char *fname)
{
	FILE *src, *dst;
	char fdest[40];
	int ch;

	if((src = fopen(fname, "rt")) == NULL) { // fname을 text로 read하여 반환받은 포인터를 src에 저장
		perror("fopen");
		return;
	}

	strcpy(fdest, fname); // fname을 fdest로 복사
	strcat(fdest, ".t");
        if ((dst = fopen(fdest, "wt")) == NULL)  { // fdest를 text로 write하여 반환받은 포인터를 dst에 저장
                perror("fopen");
                return;
        }
	
	while ((ch = fgetc(src)) != EOF) {
		if(ch >= 97 && ch <= 122) { // 소문자이면
			ch -= 32; // 대문자로 바꿔줌
		}
		fputc(ch, dst); // dst에 ch를 write
	}

	fclose(src);
	fclose(dst);

}

main(int argc, char *argv[])
{
        while (--argc)  {
                myupper(argv[argc]);
        }
}

