#include <stdio.h>
#include <signal.h>

void
SigAlarmHandler(int signo) // SIGALRM이 오면 return을 해서 pause 처리
{
	/* nothing to do, just return to wake up the pause */
	return;
}

unsigned int
mysleep(unsigned int nsecs)
{
	/* SIGALRM signal handler: SigAlarmHandler */
	if (signal(SIGALRM, SigAlarmHandler) == SIG_ERR)  { // SIGALRM이 오면 핸들러를 등록
		return nsecs;
	}

	alarm(nsecs); // nsecs 이후에 알람시그널 발생

	pause();

	return alarm(0); // 이전 남은 알림 시간 반환
}

main()
{
	printf("Wait for 5 seconds...\n");

	mysleep(5);
}
