#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int main() {
    // 현재 프로세스 ID (부모 프로세스)
    pid_t parent_pid = getpid();
    
    // fork를 호출하여 자식 프로세스를 생성
    for (int i = 0; i < 4; i++) {
        fork();
    }

    // 각 프로세스에서 현재 프로세스 ID 출력
    pid_t current_pid = getpid();
    printf("Process ID: %d\n", current_pid);

    // 부모 프로세스에서만 현재 실행 중인 자식 프로세스 수 출력
    if (parent_pid == current_pid) {
        printf("Number of processes: 16\n");
    }
    
    return 0;
}

