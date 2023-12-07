#include<stdio.h>
#include<unistd.h>

void main(int argc, char *argv[]) {
	
	if (argc < 2) {
		fprintf(stderr, "Usage: %s filename\n", argv[0]);
                exit(1);
	}

	for(int i=1; i<argc; i++) {
		if(remove(argv[i]) != 0) {
			perror("Error deleting file");
			exit(1);
		}
	}
}
