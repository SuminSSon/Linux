#include <stdio.h>
#include <signal.h>
#include <pthread.h>

pthread_t	ThreadId[2];


// SIGINT가 오면 thread 다 종료
void
SigIntHandler(int signo)
{
	int		i;

	printf("Received a SIGINT signal by thread %d\n", pthread_self());
	printf("Terminate other threads: tid=%d, %d\n", ThreadId[0], ThreadId[1]);

	for (i = 0 ; i < 2 ; i++)  {
		/* Cancel execution of all threads */
		if (pthread_cancel(ThreadId[i]))  {
			perror("pthread_cancel");
			exit(1);
		}
	}
	for (i = 0 ; i < 2 ; i++)  {
		if (pthread_join(ThreadId[i], NULL))  {
			perror("pthread_join");
			exit(1);
		}
	}
	printf("Threads terminated: tid=%d, %d\n", ThreadId[0], ThreadId[1]);

	exit(0);
}

// thread를 다른사람이 종료할 수 있게 setcancelstate로 설정하고 setcanceltype을 통해 thread를 async로 해서 바로 종료하도록 설정
void
Thread1(void *dummy)
{
	printf("Thread %d created.....\n", pthread_self());

	if (pthread_setcancelstate(PTHREAD_CANCEL_ENABLE, NULL))  {
		perror("pthread_setcancelstate");
		pthread_exit(NULL);
	}
	if (pthread_setcanceltype(PTHREAD_CANCEL_ASYNCHRONOUS, NULL))  {
		perror("pthread_setcanceltype");
		pthread_exit(NULL);
	}

	while (1)
		;
}

// thread를 다른사람이 종료할 수 있게 setcancelstate로 설정하고 setcanceltype을 통해 thread를 async로 해서 바로 종료하도록 설정
void
Thread2(void *dummy)
{
	printf("Thread %d created.....\n", pthread_self());

	if (pthread_setcancelstate(PTHREAD_CANCEL_ENABLE, NULL))  {
		perror("pthread_setcancelstate");
		pthread_exit(NULL);
	}
	if (pthread_setcanceltype(PTHREAD_CANCEL_ASYNCHRONOUS, NULL))  {
		perror("pthread_setcanceltype");
		pthread_exit(NULL);
	}

	while (1)
		;
}


main()
{
	if (pthread_create(&ThreadId[0], NULL, (void *)Thread1, NULL) < 0)  {
		perror("pthread_create");
		exit(1);
	}
	if (pthread_create(&ThreadId[1], NULL, (void *)Thread2, NULL) < 0)  {
		perror("pthread_create");
		exit(1);
	}

	signal(SIGINT, SigIntHandler); // 종료

	printf("Press ^C to quit\n");

	for ( ; ; )
		pause();
}
