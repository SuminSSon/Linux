#include<stdio.h>
#include<string.h>

void
main(int argc, char *argv[])
{
	FILE *src;
	int ch;
	int count=0;

	if (argc !=3) {
		fprintf(stderr, "Usage: %s pattern\n", argv[0]);
		exit(1);
	}

	char *filename = argv[1];
	char *pattern = argv[2];
	
	if ((src = fopen(filename, "rb")) == NULL) {
		perror("fopen");
		exit(1);
	}

	int len = strlen(pattern);
	char buffer[len];
	int currentPosition;

	while (fread(buffer, 1, len, src) == len) {
	        if (memcmp(buffer, pattern, len) == 0) {
	            count++;
        	}

		currentPosition = ftell(src);
		fseek(src, currentPosition - len + 1,SEEK_SET);
    	}
	
	fclose(src);
	printf("%d\n", count);
}
