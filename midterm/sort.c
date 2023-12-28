#include <stdio.h>
#include <stdlib.h>

int compare(const void *a, const void *b) {
    return (*(int *)a - *(int *)b);
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s input_file output_file\n", argv[0]);
        return 1;
    }

    const char *input_filename = argv[1];
    const char *output_filename = argv[2];

    // Open the input file for reading
    FILE *input_file = fopen(input_filename, "r");
    if (!input_file) {
        perror("fopen");
        return 1;
    }

    // Open the output file for writing
    FILE *output_file = fopen(output_filename, "w");
    if (!output_file) {
        perror("fopen");
        fclose(input_file); // Close the input file
        return 1;
    }

    int num_values = 0;
    int max_values = 1000; // You can adjust the maximum number of values as needed
    int *values = (int *)malloc(max_values * sizeof(int));

    if (!values) {
        perror("malloc");
        fclose(input_file);
        fclose(output_file);
        return 1;
    }

    int value;
    while (fscanf(input_file, "%d", &value) == 1) {
        if (num_values >= max_values) {
            // If the array is full, resize it
            max_values *= 2;
            values = (int *)realloc(values, max_values * sizeof(int));
            if (!values) {
                perror("realloc");
                fclose(input_file);
                fclose(output_file);
                free(values);
                return 1;
            }
        }
        values[num_values++] = value;
    }

    // Sort the array of values
    qsort(values, num_values, sizeof(int), compare);

    // Write the sorted values to the output file
    for (int i = 0; i < num_values; i++) {
        fprintf(output_file, "%d ", values[i]);
    }

    // Clean up and close the files
    fclose(input_file);
    fclose(output_file);
    free(values);

    return 0;
}

