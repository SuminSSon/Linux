#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

// SUMVALUE 구조체 정의
typedef struct SumValue{
    int start;
    int sum;
} SUMVALUE, *SUM;

void *
addSum(void* arg)
{

    SUMVALUE *func_add = (SUM)arg; // 파라메타로 들어온 arg 형변환하여 func_add에 저장
    int idx = func_add->start; // start를 idx에 저장

    for(int i=idx;i<(idx+50);i++){ // idx부터 idx+50까지
        func_add->sum+=i;
    }
    pthread_exit(NULL); // thread 종료
}

int main()
{
    pthread_t   tid1, tid2;

    //  첫 번째 thread에 전달할 구조체 생성
    SUM arg1 = (SUM) malloc(sizeof(SUMVALUE));
    arg1->start=1;
    arg1->sum=0;

    // 두 번째 thread에 전달할 구조체 생성
    SUM arg2 = (SUM) malloc(sizeof(SUMVALUE));
    arg2->start=51;
    arg2->sum=0;

    if (pthread_create(&tid1, NULL, (void *)addSum, (void *)arg1) < 0)  { // 첫 번째 thread 생성
        perror("pthread_create");
        exit(1);
    }

    if (pthread_create(&tid2, NULL, (void *)addSum, (void *)arg2) < 0)  { // 두 번째 thread 생성
        perror("pthread_create");
        exit(1);
    }

    printf("Threads created: tid=%d, %d\n", tid1, tid2);

    if (pthread_join(tid1, NULL) < 0)  {
        perror("pthread_join");
        exit(1);
    }
    if (pthread_join(tid2, NULL) < 0)  {
        perror("pthread_join");
        exit(1);
    }

    int result = arg1->sum+arg2->sum;
    printf("Threads terminated: tid=%d, %d\ntotal sum = %d\n", tid1, tid2,result);

}
