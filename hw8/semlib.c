#include <stdio.h>
#include "semlib.h"
 
 
int
semInit(key_t key)
{
    int     semid;

    if ((semid = semget(key, 1, 0600 | IPC_CREAT)) < 0)  { // 입력받은 key로 semaphore의 id값을 가져옴. 없을경우 생성
		perror("semget");
        return -1;
    }

    return semid;
}
 
int
semInitValue(int semid, int value)
{
    union semun {
	int     val;
    } semun;

    semun.val = value;
    if (semctl(semid, 0, SETVAL, semun) < 0)  { // 입력받은 semid로 식별하여 semaphore의 value 값을 설정
		perror("semctl");
        return -1;
    }
 
    return semid;
}
 
int
semWait(int semid)
{
    struct sembuf   semcmd;
 
    semcmd.sem_num = 0; // semaphore를 하나만 만들기 때문에 0으로 설정
    semcmd.sem_op = -1; // wait이므로 -1
    semcmd.sem_flg = SEM_UNDO; // 자원을 반납하지 않고 종료되는 상황을 방지
    if (semop(semid, &semcmd, 1) < 0)  {
		perror("semop");
        return -1;
    }
 
    return 0;
}
 
int
semTryWait(int semid)
{
    struct sembuf   semcmd;
 
    semcmd.sem_num = 0;
    semcmd.sem_op = -1;
    semcmd.sem_flg = IPC_NOWAIT | SEM_UNDO; // 자원이 없으면 IPC_NOWAIT은 기다리지 않고 종료
    if (semop(semid, &semcmd, 1) < 0)  {
		perror("semop");
        return -1;
    }
 
    return 0;
}

int
semPost(int semid)
{
    struct sembuf   semcmd;
 
    semcmd.sem_num = 0;
    semcmd.sem_op = 1;
    semcmd.sem_flg = SEM_UNDO;
    if (semop(semid, &semcmd, 1) < 0)  {
		perror("semop");
        return -1;
    }
 
    return 0;
}

int
semGetValue(int semid)
{
    union semun {
            int     val;
    } dummy;
 
    return semctl(semid, 0, GETVAL, dummy);
}
 
int
semDestroy(int semid)
{
    union semun {
            int     val;
    } dummy;
 
    if (semctl(semid, 0, IPC_RMID, dummy) < 0)  {
		perror("semctl");
        return -1;
    }
    close(semid);
 
    return 0;
}
