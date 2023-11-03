#include <stdio.h>
#include <unistd.h>

main(int argc, char *argv[])
{
	if (argc != 3)  {
		fprintf(stderr, "Usage: %s source destinaion\n", argv[0]);
		exit(1);
	}

	if (symlink(argv[1], argv[2]) < 0)  { // argv[1]을 sympolic link를 생성하여 argv[2]를 만든다.
		perror("link");
		exit(1);
	}
}
