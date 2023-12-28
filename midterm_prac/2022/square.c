#include<stdio.h>

void
main(int argc, char *argv[]) {
	if (argc != 2) {
		fprintf(stderr, "Usage: %s num\n", argv[0]);
		exit(1);
	}

	int num = atoi(argv[1]);
	printf("%d\n", num*num);
}
