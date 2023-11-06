#include <stdio.h>

main(int argc, char *argv[])
{
	int		i;

	if (argc == 1)  {
		fprintf(stderr, "Usage: %s filename\n", argv[0]);
		exit(1);
	}

	for (i = 1 ; i < argc ; i++)  { 
		if (remove(argv[i]) < 0)  { // argv[i] 파일을 삭제
			perror("remove");
			exit(1);
		}
	}
}