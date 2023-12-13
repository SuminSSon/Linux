#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/time.h>
#include "prodcons.h"

BoundedBufferType	Buf;

void
ThreadUsleep(int usecs) // usecs만큼 thread를 sleep
{
	pthread_cond_t		cond; // conditional signal 감지
	pthread_mutex_t		mutex;
	struct timespec		ts;
	struct timeval		tv;

	if (pthread_cond_init(&cond, NULL) < 0)  { // 조건변수 cond 초기화, attr이 NULL이면 기본 조건 사용
		perror("pthread_cond_init");
		pthread_exit(NULL);
	}
	if (pthread_mutex_init(&mutex, NULL) < 0)  { // mutex 초기화, NULL이면 default 'fast' 사용
		perror("pthread_mutex_init");
		pthread_exit(NULL);
	}

	gettimeofday(&tv, NULL); // 1970-01-01 00::00:00 +0000 (UTC)이후 현재까지 경과된 초와 micro초를 get
	// 단위 맞춰주기
	ts.tv_sec = tv.tv_sec + usecs/1000000;
	ts.tv_nsec = (tv.tv_usec + (usecs%1000000)) * 1000;
	if (ts.tv_nsec >= 1000000000)  {
		ts.tv_nsec -= 1000000000;
		ts.tv_sec++;
	}

	if (pthread_mutex_lock(&mutex) < 0)  { // mutex lock
		perror("pthread_mutex_lock");
		pthread_exit(NULL);
	}
	if (pthread_cond_timedwait(&cond, &mutex, &ts) < 0)  { // cond가 true가 될때까지 wait
		perror("pthread_cond_timedwait");
		pthread_exit(NULL);
	}

	if (pthread_cond_destroy(&cond) < 0)  { // cond 삭제
		perror("pthread_cond_destroy");
		pthread_exit(NULL);
	}
	if (pthread_mutex_destroy(&mutex) < 0)  { // mutex 삭제
		perror("pthread_mutex_destroy");
		pthread_exit(NULL);
	}
}

void
Producer(void *dummy)
{
	int		i, data;

	printf("Producer: Start.....\n");

	for (i = 0 ; i < NLOOPS ; i++)  {
		if (Buf.counter == MAX_BUF)  { // MAX_BUF 크기를 넘는 data가 들어왔을 때
			printf("Producer: Buffer full. Waiting.....\n");
			while (Buf.counter == MAX_BUF) // MAX_BUF보다 작아질 때까지 wait
				;
		}

		printf("Producer: Producing an item.....\n");
		data = (rand()%100)*10000;
		Buf.buf[Buf.in].data = data;
		Buf.in = (Buf.in + 1) % MAX_BUF;
		Buf.counter++;

		ThreadUsleep(data); // data micro second만큼 Thread sleep
	}

	printf("Producer: Produced %d items.....\n", i);
	printf("Producer: %d items in buffer.....\n", Buf.counter);
	
	pthread_exit(NULL);
}

void
Consumer(void *dummy)
{
	int		i, data;

	printf("Consumer: Start.....\n");

	for (i = 0 ; i < NLOOPS ; i++)  {
		if (Buf.counter == 0)  { // buf에 data가 없을 때
			printf("Consumer: Buffer empty. Waiting.....\n");
			while (Buf.counter == 0)
				;
		}

		printf("Consumer: Consuming an item.....\n");
		data = Buf.buf[Buf.out].data; // read
		Buf.out = (Buf.out + 1) % MAX_BUF;
		Buf.counter--;

		ThreadUsleep((rand()%100)*10000);
	}

	printf("Consumer: Consumed %d items.....\n", i);
	printf("Consumer: %d items in buffer.....\n", Buf.counter);

	pthread_exit(NULL);
}

main()
{
	pthread_t	tid1, tid2;

	srand(0x8888);

	if (pthread_create(&tid1, NULL, (void *)Producer, (void *)NULL) < 0)  {
		perror("pthread_create");
		exit(1);
	}

	if (pthread_create(&tid2, NULL, (void *)Consumer, (void *)NULL) < 0)  {
		perror("pthread_create");
		exit(1);
	}

	if (pthread_join(tid1, NULL) < 0)  { // tid1의 종료되기를 기다림
		perror("pthread_join");
		exit(1);
	}
	if (pthread_join(tid2, NULL) < 0)  { // tid2의 종료되기를 기다림
		perror("pthread_join");
		exit(1);
	}

	printf("Main    : %d items in buffer.....\n", Buf.counter);
}
