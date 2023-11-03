#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>

main()
{
	struct stat	statbuf;

	if (stat("bar", &statbuf) < 0)  { // bar의status를 statbuf에 저장
		perror("stat");
		exit(1);
	}

	if (chmod("bar", (statbuf.st_mode & ~S_IWGRP) | S_ISUID) < 0)  { // bar 파일의 group의 write권한을 끄고 uid bit를 킴. effective uid가 나중에 소유자 id로 access 가능
		perror("chmod");
		exit(1);
	}

	/* S_IRUSR, S_IWUSR, S_IRGRP, S_IROTH : ON */
	if (chmod("foo", S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH) < 0 )  { // foo 파일의 user의 Read와 write, group의 read, other의 read 권한을 킨다
		perror("chmod");
		exit(1);
	}
}
