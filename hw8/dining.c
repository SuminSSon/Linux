#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <semaphore.h>
#include <pthread.h>
#include <sys/time.h>

#define	NUM_MEN		5
#define	NLOOPS		5

sem_t	ChopStick[NUM_MEN];

void
ThreadUsleep(int usecs) //usecs 동안 thread를 sleep
{
	pthread_cond_t		cond;
	pthread_mutex_t		mutex;
	struct timespec		ts;
	struct timeval		tv;

	if (pthread_cond_init(&cond, NULL) < 0)  {
		perror("pthread_cond_init");
		pthread_exit(NULL);
	}
	if (pthread_mutex_init(&mutex, NULL) < 0)  {
		perror("pthread_mutex_init");
		pthread_exit(NULL);
	}

	gettimeofday(&tv, NULL);
	ts.tv_sec = tv.tv_sec + usecs/1000000;
	ts.tv_nsec = (tv.tv_usec + (usecs%1000000)) * 1000;
	if (ts.tv_nsec >= 1000000000)  {
		ts.tv_nsec -= 1000000000;
		ts.tv_sec++;
	}

	if (pthread_mutex_lock(&mutex) < 0)  {
		perror("pthread_mutex_lock");
		pthread_exit(NULL);
	}
	if (pthread_cond_timedwait(&cond, &mutex, &ts) < 0)  {
		perror("pthread_cond_timedwait");
		pthread_exit(NULL);
	}

	if (pthread_cond_destroy(&cond) < 0)  {
		perror("pthread_cond_destroy");
		pthread_exit(NULL);
	}
	if (pthread_mutex_destroy(&mutex) < 0)  {
		perror("pthread_mutex_destroy");
		pthread_exit(NULL);
	}
}

void
Thinking(int id)
{
	printf("Philosopher%d: Thinking.....\n", id);
	ThreadUsleep((rand()%200)*10000);
	printf("Philosopher%d: Want to eat.....\n", id);
}

void
Eating(int id)
{
	printf("Philosopher%d: Eating.....\n", id);
	ThreadUsleep((rand()%100)*10000);
}

void
DiningPhilosopher(int *pId)
{
	int		i;
	int		id = *pId;

	for (i = 0 ; i < NLOOPS ; i++)  {

		Thinking(id);

		if (sem_wait(&ChopStick[id]) < 0)  { // ChopStick semaphore wait
			perror("sem_wait");
			pthread_exit(NULL);
		}
		if (sem_wait(&ChopStick[(id+1) % NUM_MEN]) <0)  { // 반대쪽 ChopStick semaphore wait
			perror("sem_wait");
			pthread_exit(NULL);
		}

		Eating(id);

		if (sem_post(&ChopStick[id]) < 0)  { // ChopStick semaphore signal
			perror("sem_post");
			pthread_exit(NULL);
		}
		if (sem_post(&ChopStick[(id+1) % NUM_MEN]) < 0)  { // 반대쪽 ChopStick semaphore signal
			perror("sem_post");
			pthread_exit(NULL);
		}
	}

	printf("Philosopher%d: thinking & eating %d times.....\n", id, i);

	pthread_exit(NULL);
}

main()
{
	pthread_t	tid[NUM_MEN];
	int			i, id[NUM_MEN];

	srand(0x8888);

	for (i = 0 ; i < NUM_MEN ; i++)  {
		if (sem_init(&ChopStick[i], 0, 1) < 0)  {
			perror("sem_init");
			exit(1);
		}
		id[i] = i;
	}

	for (i = 0 ; i < NUM_MEN ; i++)  {
		if (pthread_create(&tid[i], NULL, (void *)DiningPhilosopher, 
				(void *)&id[i]) < 0)  {
			perror("pthread_create");
			exit(1);
		}
	}

	for (i = 0 ; i < NUM_MEN ; i++)  {
		if (pthread_join(tid[i], NULL) < 0)  {
			perror("pthread_join");
			exit(1);
		}
	}

	for (i = 0 ; i < NUM_MEN ; i++)  {
		if (sem_destroy(&ChopStick[i]) < 0)  {
			perror("sem_destroy");
		}
	}
}
