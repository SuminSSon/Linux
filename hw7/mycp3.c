#include <stdio.h>
#include <sys/types.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>

main(int argc, char *argv[])
{
	int			fdin, fdout;
	char		*src, *dst;
	struct stat	statbuf;

	if (argc != 3)  {
		fprintf(stderr, "Usage: %s source destination\n", argv[0]);
		exit(1);
	}

	if ((fdin = open(argv[1], O_RDONLY)) < 0)  { // argv[1]을 read only로 open
		perror("open");
		exit(1);
	}
	if ((fdout = open(argv[2], O_RDWR | O_CREAT | O_TRUNC, 0644)) < 0)  { // argv[2]를 write로 open
		perror("open");
		exit(1);
	}

	if (fstat(fdin, &statbuf) < 0)  { // fdin의 파일 정보를 statbuf에 저장
		perror("fstat");
		exit(1);
	}
	if (lseek(fdout, statbuf.st_size-1, SEEK_SET) < 0)  { // fdout의 처음에서 statbuf.st_size-1만큼 이동
		perror("lseek");
		exit(1);
	}
	write(fdout, "", 1); // 그 자리에 \0 입력

	if ((src = mmap(0, statbuf.st_size, PROT_READ, MAP_SHARED, fdin, 0)) 
		== (caddr_t) -1)  { // virtual addr에 내용 복사
		perror("mmap");
		exit(1);
	}
	if ((dst = mmap(0, statbuf.st_size, PROT_WRITE, MAP_SHARED, fdout, 0)) 
		== (caddr_t) -1)  { // 다른 proess와 share하여 fdout 사용
		perror("mmap");
		exit(1);
	}

	memcpy(dst, src, statbuf.st_size); // src에서 st_size만큼 read하여 dst에 write

	close(fdin);
	close(fdout);
}
