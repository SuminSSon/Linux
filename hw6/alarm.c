#include <stdio.h>
#include <signal.h>

static unsigned int	AlarmSecs;


// 재등록 함수
void
SigAlarmHandler(int signo) // SIGALRM이 오면 처리하기 위한 핸들러 함수
{
	if (signal(SIGALRM, SigAlarmHandler) == SIG_ERR)  {
		perror("signal");
		exit(1);
	}

	alarm(AlarmSecs); // 1초 뒤에 알람 발생

	/* Do something */
	printf("."); // .을 찍고
	fflush(stdout); // fflush를 통해 버퍼를 강제 출력

	return;
}


// SIGALRM이 오면 signal에 핸들러를 등록하고 alarm을 통해서 nsecs 이후에alarm 발생
int
SetPeriodicAlarm(unsigned int nsecs)
{
	if (signal(SIGALRM, SigAlarmHandler) == SIG_ERR)  {
		return -1;
	}

	AlarmSecs = nsecs;

	alarm(nsecs);

	return 0;
}

main()
{
	printf("Doing something every one seconds\n");

	SetPeriodicAlarm(1);

	for ( ; ; )
		pause();
}
