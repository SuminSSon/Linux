#include <stdio.h>
#include <signal.h>
#include <pwd.h>


void
MyAlarmHandler(int signo)
{
	struct passwd	*rootptr;

	signal(SIGALRM, MyAlarmHandler);
	alarm(1); // 알람 시그널 발생 예약

	printf("in signal handler\n");

	if ((rootptr = getpwnam("root")) == NULL)  { // getpwnam을 통해 root 사용자의 정보를받아옴
		perror("getpwnam");
		exit(1);
	}

	return;
}

// getpwnam은 nonreent
main()
{
	struct passwd	*ptr;

	signal(SIGALRM, MyAlarmHandler);
	alarm(1);

	for ( ; ; )  {
		if ((ptr = getpwnam("cjs")) == NULL)  {
			perror("getpwnam");
			exit(1);
		}

		if (strcmp(ptr->pw_name, "cjs") != 0)  { // 위 함수에서 cjs에 대한 정보를 불러왔지만 alarm SIG가 실행되면서 cjs 정보와 다르게 된다 
			printf("return value corrupted!, pw_name = %s\n", ptr->pw_name);
			exit(0);
		}
	}
}
