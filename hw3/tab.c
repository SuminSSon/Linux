#include <stdio.h>

enum { FALSE, TRUE };

void
conv(char *fname)
{
	FILE	*src, *dst;
	char	fdest[40];
	int		ch, first;

	if ((src = fopen(fname, "rt")) == NULL)  {
		perror("fopen");
		return;
	}

	strcpy(fdest, fname); // fname(file name)을 fdest에 저장
	strcat(fdest, ".t"); // fdest 뒤에 .t를 붙임
	if ((dst = fopen(fdest, "wt")) == NULL)  {
		perror("fopen");
		return;
	}

	first = TRUE;
	while ((ch = fgetc(src)) != EOF)  {
		if (first && ch == '\t')  { // 첫 번재 문자이고 \t라면 4개의 공백을 삽입
			fputc(' ', dst);
			fputc(' ', dst);
			fputc(' ', dst);
			fputc(' ', dst);
		}
		else  { // 아니면 dst에 ch 삽입
			fputc(ch, dst);
			if (first)
				first = FALSE;
			if (ch == '\n')
				first = TRUE;
		}
	}

	fclose(src);
	fclose(dst);
}

main(int argc, char *argv[])
{
	while (--argc)  { // argv 수만큼 conv 실행
		conv(argv[argc]);
	}
}
