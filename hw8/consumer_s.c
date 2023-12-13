#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include "semlib.h"
#include "prodcons.h"

main()
{
	BoundedBufferType	*pBuf;
	int					shmid, i, data;
	int					emptySemid, fullSemid, mutexSemid;

	if ((shmid = shmget(SHM_KEY, SHM_SIZE, SHM_MODE)) < 0)  {
		perror("shmget");
		exit(1);
	}
	if ((pBuf = (BoundedBufferType *)shmat(shmid, 0, 0)) == (void *) -1)  {
		perror("shmat");
		exit(1);
	}

	if ((emptySemid = semInit(EMPTY_SEM_KEY)) < 0)  { // empty semaphore 생성
		fprintf(stderr, "semInit failure\n");
		exit(1);
	}
	if ((fullSemid = semInit(FULL_SEM_KEY)) < 0)  { // full semaphore 생성
		fprintf(stderr, "semInit failure\n");
		exit(1);
	}
	if ((mutexSemid = semInit(MUTEX_SEM_KEY)) < 0)  {
		fprintf(stderr, "semInit failure\n");
		exit(1);
	}

	if (semInitValue(emptySemid, MAX_BUF) < 0)  { // empty semaphore의 개수를 MAX_BUF로 초기화
		fprintf(stderr, "semInitValue failure\n");
		exit(1);
	}
	if (semInitValue(fullSemid, 0)  < 0)  { // full semaphore의 개수를 0으로 초기화
		fprintf(stderr, "semInitValue failure\n");
		exit(1);
	}
	if (semInitValue(mutexSemid,1) < 0)  { // mutex semaphore의 개수를 1로 초기화
		fprintf(stderr, "semInitValue failure\n");
		exit(1);
	}

	srand(0x9999);
	for (i = 0 ; i < NLOOPS ; i++)  {
		if (semWait(fullSemid) < 0)  { // full semaphore wait
			fprintf(stderr, "semWait failure\n");
			exit(1);
		}
		if (semWait(mutexSemid) < 0)  { // mutex semaphore wait
			fprintf(stderr, "semWait failure\n");
			exit(1);
		}
		printf("Consumer: Consuming an item.....\n");
		data = pBuf->buf[pBuf->out].data;
		pBuf->out = (pBuf->out + 1) % MAX_BUF;
		pBuf->counter--;

		if (semPost(mutexSemid) < 0)  { // mutex semaphore signal
			fprintf(stderr, "semPost failure\n");
			exit(1);
		}
		if (semPost(emptySemid) < 0)  { // empty semaphore signal
			fprintf(stderr, "semPost failure\n");
			exit(1);
		}

		usleep((rand()%100)*10000); // random time sleep
	}

	printf("Consumer: Consumed %d items.....\n", i);
	printf("Consumer: %d items in buffer.....\n", pBuf->counter);
}
