#include <stdio.h>
#include <signal.h>


// SIGINT를 호출하면 출력 후 종려
void
SigIntHandler(int signo)
{
	printf("Received a SIGINT signal\n");
	printf("Terminate this process\n");

	exit(0);
}

main()
{
	/* SIGINT signal handler: SigIntHandler */
	signal(SIGINT, SigIntHandler); // ctrl + c 를 입력받으면 종료

	printf("Press ^C to quit\n");

	for ( ; ; )
		pause();
}
