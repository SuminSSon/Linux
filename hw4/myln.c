#include <stdio.h>
#include <unistd.h>

main(int argc, char *argv[])
{
	if (argc != 3)  {
		fprintf(stderr, "Usage: %s source destinaion\n", argv[0]);
		exit(1);
	}

	if (link(argv[1], argv[2]) < 0)  { // argv[1]의 파일을 hard link하여 새로운 파일을 만든다.
		perror("link");
		exit(1);
	}
}
