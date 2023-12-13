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

	if (semInitValue(emptySemid, 0) < 0)  { //empty 값을 0으로 초기화
		fprintf(stderr, "semInitValue failure\n");
		exit(1);
	}
	if (semInitValue(fullSemid, 0) < 0)  { //full 값을  0으로 초기화
		fprintf(stderr, "semInitValue failure\n");
		exit(1);
	}

	if (semWait(fullSemid) < 0)  {
        fprintf(stderr, "semWait failure\n");
        exit(1);
	}

	printf("Received request: %s.....", data);
	sprintf(data, "This is a reply from %d.", getpid());
	
	if (semPost(emptySemid) < 0)  {
        fprintf(stderr, "semPost failure\n");
        exit(1);
	}

	printf("Replied.\n");

	sleep(1);

	if (shmctl(shmid, IPC_RMID, 0) < 0)  {
		perror("shmctl");
		exit(1);
	}
}
