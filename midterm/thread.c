#include<stdio.h>
#include <stdlib.h>
#include <pthread.h>

typedef struct TValue {
	int x1;
	int x2;

	int y1;
	int y2;

	int result;
} TVALUE, *T;

void *
multiSum(void* arg) {
	TVALUE *func_add = (T)arg;
	int idx_x1 = func_add->x1;
	int idx_x2 = func_add->x2;

	int idx_y1 = func_add->y1;
	int idx_y2 = func_add->y2;
	
	func_add->result = (idx_x1 * idx_y1) + (idx_x2 * idx_y2);

	pthread_exit(NULL);

}

void
main(){
	pthread_t   tid1, tid2, tid3, tid4;

	srand(10);
	int x11 = rand() % 10;
        int x12 = rand() % 10;
        int x21 = rand() % 10;
	int x22 = rand() % 10;

	int y11 = rand() % 10;
	int y12 = rand() % 10;
	int y21 = rand() % 10;
	int y22 = rand() % 10;

	T arg1 = (T) malloc(sizeof(TVALUE));
	arg1->x1 = x11;
	arg1->x2 = x12;
	arg1->y1 = y11;
	arg1->y2 = y21;
	arg1->result = 0;

	T arg2 = (T) malloc(sizeof(TVALUE));
        arg2->x1 = x11;
        arg2->x2 = x12;
        arg2->y1 = y12;
        arg2->y2 = y22;
        arg2->result = 0;

	T arg3 = (T) malloc(sizeof(TVALUE));
        arg3->x1 = x21;
        arg3->x2 = x22;
        arg3->y1 = y11;
        arg3->y2 = y21;
        arg3->result = 0;

	T arg4 = (T) malloc(sizeof(TVALUE));
        arg4->x1 = x21;
        arg4->x2 = x22;
        arg4->y1 = y12;
        arg4->y2 = y22;
        arg4->result = 0;


	if (pthread_create(&tid1, NULL, (void *)multiSum, (void *)arg1) < 0)  {
        perror("pthread_create");
        exit(1);
    	}

	if (pthread_create(&tid2, NULL, (void *)multiSum, (void *)arg2) < 0)  {
        perror("pthread_create");
        exit(1);
        }

	if (pthread_create(&tid3, NULL, (void *)multiSum, (void *)arg3) < 0)  {
        perror("pthread_create");
        exit(1);
        }

	if (pthread_create(&tid4, NULL, (void *)multiSum, (void *)arg4) < 0)  {
        perror("pthread_create");
        exit(1);
        }


	if (pthread_join(tid1, NULL) < 0)  {
        perror("pthread_join");
        exit(1);
    	}
    	if (pthread_join(tid2, NULL) < 0)  {
        perror("pthread_join");
        exit(1);
   	}
	if (pthread_join(tid3, NULL) < 0)  {
        perror("pthread_join");
        exit(1);
        }
        if (pthread_join(tid4, NULL) < 0)  {
        perror("pthread_join");
        exit(1);
        }
	



	printf("(%d %d %d %d) X (%d %d %d %d) = (%d %d %d %d)", x11, x12, x21, x22, y11, y12, y21, y22, arg1->result, arg2->result, arg3->result, arg4->result);
}
