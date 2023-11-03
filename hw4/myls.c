#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>

main()
{
	DIR				*dp;
	struct dirent	*dep;

	if ((dp = opendir(".")) == NULL)  { // 현재 dir를 열고 DIR 포인터 dp에 저장
		perror("opendir");
		exit(0);
	}

	while (dep = readdir(dp))  { // dp의 dirent struct를 반환받아 dep에 저장
		printf("%s\n", dep->d_name);
	}
	
	closedir(dp);
}
