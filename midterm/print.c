#include<stdio.h>

void
main(int argc, char* argv[]) {
	
	if (argc != 3) {
		fprintf(stderr, "Usage: %s print\n", argv[0]);
                exit(1);
	}

	int size = atoi(argv[2]);
	for(int i=0; i<size; i++) {
		printf("%c", argv[1][i]);
	}

	printf("\n");
}
