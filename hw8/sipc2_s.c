#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include "semlib2.h"
#include "shm.h"

main()
{
	int	shmid;
	char	*data;
	int     emptySemid, fullSemid;


	if ((shmid = shmget(SHM_KEY, SHM_SIZE, SHM_MODE)) < 0)  {
		perror("shmget");
		exit(1);
	}
	if ((data = shmat(shmid, 0, 0)) == (void *) -1)  {
		perror("shmat");
		exit(1);
	}

	if ((emptySemid = semInit(EMPTY_SEM_KEY) ) < 0)  { //환경변수 EMPTY_SEM_KEY로 semaphore 생성
		fprintf(stderr, "semInit failure\n");
		exit(1);
	}
	if ((fullSemid = semInit(FULL_SEM_KEY) ) < 0)  { //환경변수 FULL_SEM_KEY로 semaphore 생성
		fprintf(stderr, "semInit failure\n");
		exit(1);
	}

	sprintf(data, "This is a request from %d.", getpid());

	if (semPost(fullSemid) < 0)  {
        fprintf(stderr, "semPost failure\n");
        exit(1);
	}
	printf("Sent a request.....");

	if (semWait(emptySemid) < 0)  {
        fprintf(stderr, "semWait failure\n");
        exit(1);
	}

	printf("Received reply: %s\n", data);

	if (semDestroy(emptySemid) < 0)  { //empty semaphore 제거
		fprintf(stderr, "semDestroy failure\n");
	}
	if (semDestroy(fullSemid) < 0)  { //full semaphore 제거
		fprintf(stderr, "semDestroy failure\n");
	}

	
}
