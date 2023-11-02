#include <stdio.h>
#include <unistd.h>
#include "record.h"

/*
 * rp의 stud, num, dept를 출력 
 */

void
print_record(Record *rp)
{
	puts(rp->stud);
	puts(rp->num);
	puts(rp->dept);
}

main(int argc, char *argv[])
{
	FILE	*fp;
	Record	rec;

	if (argc != 2)  {
		fprintf(stderr, "Usage: %s file\n", argv[0]);
		exit(1);
	}

	// argv[1]은 fopen으로 binary를 read모드로 열어 write도 가능하게 만들어>서 반환한 포인터를 fp에 저장 
	if ((fp = fopen(argv[1], "r+b")) == NULL)  {
		perror("fopen"); // fopen 시 NULL을 반환하면 에러메시지 출력
		exit(1);
	}

	printf("-----Ordered Record List-----\n");


	// fp에 있는 내용을 rec사이즈만큼 한 개를 읽어서 rec 객체에 저장한 후 rec 객체를 출력한다.
	while (fread(&rec, sizeof(rec), 1, fp))  {
		print_record(&rec);
	}
	rewind(fp); // fp의 위치를 처음으로 초기화한다.
	getchar();

	printf("-----Shuffled Record List-----\n");

	fseek(fp, sizeof(rec)*2L, SEEK_SET); // 파일 내 포인터 위치를 rec의 size * 2L만큼 이동
	fread(&rec, sizeof(rec), 1, fp); // record 객체 출력
	print_record(&rec);

	fseek(fp, sizeof(rec)*5L, SEEK_SET);
	fread(&rec, sizeof(rec), 1, fp);
	print_record(&rec);

	fseek(fp, sizeof(rec)*1L, SEEK_SET);
	fread(&rec, sizeof(rec), 1, fp);
	print_record(&rec);

	fseek(fp, sizeof(rec)*3L, SEEK_SET);
	fread(&rec, sizeof(rec), 1, fp);
	print_record(&rec);

	fseek(fp, sizeof(rec)*0L, SEEK_SET);
	fread(&rec, sizeof(rec), 1, fp);
	print_record(&rec);

	fseek(fp, sizeof(rec)*4L, SEEK_SET);
	fread(&rec, sizeof(rec), 1, fp);
	print_record(&rec);
	getchar();

	printf("-----Updated Record List-----\n");

	fseek(fp, sizeof(rec)*2L, SEEK_SET);
	fread(&rec, sizeof(rec), 1, fp);
	strcpy(rec.dept, "Movie"); // fp로 rec 객체의 dept의 값을 Movie로 수정한다.  
	fseek(fp, sizeof(rec)*2L, SEEK_SET);
	fwrite(&rec, sizeof(rec), 1, fp); // 다시 원래 포인터로 돌아와서 값을 수정

	fseek(fp, sizeof(rec)*5L, SEEK_SET);
	fread(&rec, sizeof(rec), 1, fp);
	strcpy(rec.dept, "Baseball");
	fseek(fp, sizeof(rec)*5L, SEEK_SET);
	fwrite(&rec, sizeof(rec), 1, fp);

	rewind(fp);
	while (fread(&rec, sizeof(rec), 1, fp))  {
		print_record(&rec);
	}

	fclose(fp);
}
