#include <stdio.h>
#include <ctype.h>

void
myupper(char *fname, char *result)
{
	FILE *src, *dst;
	int ch;

	if((src = fopen(fname, "rt")) == NULL) {
		perror("fopen");
		return;
	}

	
        if ((dst = fopen(result, "wt")) == NULL)  {
                perror("fopen");
                return;
        }

	int total_num = 0;
	int convert_num = 0;
	int blank_num = 0;	
	int number_num = 0;
	int special_num = 0;

	while ((ch = fgetc(src)) != EOF) {
		total_num++;
		if(islower(ch)) {
			ch = toupper(ch);
			convert_num++;
		}
		fputc(ch, dst); // dst에 ch를 write

		if(isspace(ch)) blank_num++;
		else if(isdigit(ch)) number_num++;
		else if(!isalnum(ch)) special_num++;
	}

	printf("Converted file: %s\n", result);
	printf("Total characters: %d\n", total_num);
	printf("Converted characters: %d\n", convert_num);
	printf("Blank characters: %d\n", blank_num);
	printf("Number characters: %d\n", number_num);
	printf("Special characters: %d\n", special_num);

	fclose(src);
	fclose(dst);

}

main(int argc, char *argv[])
{

	if (argc != 3) {
        	fprintf(stderr, "Usage: %s input_filename output_filename\n", argv[0]);
        	exit(1);
    	}

	myupper(argv[1], argv[2]);
}


