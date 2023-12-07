#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    if (argc != 4) {
        fprintf(stderr, "Usage: %s num1 op num2\n", argv[0]);
        return 1; 
    }

    int num1 = atoi(argv[1]);
    char op = argv[2][0];
    int num2 = atoi(argv[3]);
    int result;

    switch (op) {
        case '+':
            result = num1 + num2;
            break;
        case '-':
            result = num1 - num2;
            break;
        case 'x':
            result = num1 * num2;
            break;
        case '/':
            if (num2 != 0) {
                result = num1 / num2;
            } else {
                fprintf(stderr, "Division by zero is not allowed.\n");
                exit(1); 
            }
            break;
        default:
            fprintf(stderr, "Invalid operator: %c\n", op);
            return 1;
    }

    printf("%d\n", result);
    return 0;
}

