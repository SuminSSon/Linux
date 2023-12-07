#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s filename\n", argv[0]);
        return 1;
    }

    FILE *src;

    if((src=fopen(argv[1],"rt"))==NULL){
        perror("fopen");
        exit(1);
    }

    int word_count = 0;
    int in_word = 0;
    int ch;

    while ((ch = fgetc(src)) != EOF) {
        if (isspace(ch) || ch == '\n' || ch == '\t') {
            in_word = 0;
        } else if (!in_word) {
            in_word = 1;
            word_count++;
        }
    }

    fclose(src);

    printf("%d\n", word_count);

    return 0;
}

