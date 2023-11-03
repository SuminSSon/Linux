#include <stdio.h>
#include <unistd.h>

// child process가 실행되기 때문에 현재 프로세스에서는 바뀌지 않음
main(int argc, char *argv[])
{
	if (argc != 2)  {
		fprintf(stderr, "Usage: %s dirname\n", argv[0]);
		exit(1);
	}

	if (chdir(argv[1]) < 0)  { // argv[1]의 dir로 dir의 위치를 옮긴다.
		perror("chdir");
		exit(1);
	}
}
