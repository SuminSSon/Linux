#INCLUDE <STDIO.H>

VOID
MYUPPER(CHAR *FNAME)
{
	FILE *SRC, *DST;
	CHAR FDEST[40];
	INT CH;

	IF((SRC = FOPEN(FNAME, "RT")) == NULL) { // FNAME을 TEXT로 READ하여 반환받은 포인터를 SRC에 저장
		PERROR("FOPEN");
		RETURN;
	}

	STRCPY(FDEST, FNAME); // FNAME을 FDEST로 복사
	STRCAT(FDEST, ".T");
        IF ((DST = FOPEN(FDEST, "WT")) == NULL)  { // FDEST를 TEXT로 WRITE하여 반환받은 포인터를 DST에 저장
                PERROR("FOPEN");
                RETURN;
        }
	
	WHILE ((CH = FGETC(SRC)) != EOF) {
		IF(CH >= 97 && CH <= 122) { // 소문자이면
			CH -= 32; // 대문자로 바꿔줌
		}
		FPUTC(CH, DST); // DST에 CH를 WRITE
	}

	FCLOSE(SRC);
	FCLOSE(DST);

}

MAIN(INT ARGC, CHAR *ARGV[])
{
        WHILE (--ARGC)  {
                MYUPPER(ARGV[ARGC]);
        }
}

