#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>
#include <sys/stat.h>

#define	MAX_PATH	256

void
JustDoIt(char *path)
{
	DIR				*dp;
	struct dirent	*dep;
	struct stat		statbuf;
	char			fullpath[MAX_PATH];

	if ((dp = opendir(path)) == NULL)  { // parameter로 받은 path의 dir을 열어 반환받은 pointer dp에 저장
		perror("opendir");
		exit(0);
	}

	printf("\n%s:\n", path); 
	while (dep = readdir(dp))  {
		if (strcmp(".", dep->d_name) == 0 || strcmp("..", dep->d_name) == 0) // 현재 dir 또는 부모 dir인 경우에는 continue
			continue;
		printf("%s\n", dep->d_name); // 아니면 d_name 출력
	}

	rewind(dp); // pointer 위치를 처음으로 초기화
	while (dep = readdir(dp))  { 
		if (strcmp(".", dep->d_name) == 0 || strcmp("..", dep->d_name) == 0)
			continue;
		strcpy(fullpath, path); 
		strcat(fullpath, "/");
		strcat(fullpath, dep->d_name);
		if (lstat(fullpath, &statbuf < 0))  { // path/d_name으로 만든 fullpath의 status를 statbuf에 저장
			perror("lstat");
			exit(1);
		}
		if (S_ISDIR(statbuf.st_mode))  { // stabuf의 st_mode가 dir이면 재귀
			JustDoIt(fullpath);
		}
	}
	
	closedir(dp);
}

main()
{
	JustDoIt(".");
}
