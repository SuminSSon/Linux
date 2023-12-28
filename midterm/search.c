#include <stdio.h>

int binarySearch(int arr[], int size, int target) {
    int left = 0;
    int right = size - 1;

    while (left <= right) {
        int mid = left + (right - left) / 2;

        if (arr[mid] == target) {
            return mid;  // 원하는 숫자를 찾았을 때 해당 위치를 반환
        }

        if (arr[mid] < target) {
            left = mid + 1;  // 숫자가 오른쪽 절반에 있음
        } else {
            right = mid - 1;  // 숫자가 왼쪽 절반에 있음
        }
    }

    return -1;  // 숫자를 찾지 못했을 때 -1 반환
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s filename target\n", argv[0]);
        return 1;
    }

    FILE *file = fopen(argv[1], "r");
    if (!file) {
        perror("fopen");
        return 1;
    }

    int target = atoi(argv[2]);
    int numbers[100];  // 파일에서 읽어올 숫자 배열, 크기 조정 필요

    int size = 0;
    int number;

    // 파일에서 숫자 읽어오기
    while (fscanf(file, "%d", &number) == 1) {
        numbers[size] = number;
        size++;
    }

    fclose(file);

    // 배열에서 이진 검색 수행
    int result = binarySearch(numbers, size, target);

    if (result != -1) {
        printf("%d\n", numbers[result]);
    } else {
        printf("None\n");
    }

    return 0;
}

