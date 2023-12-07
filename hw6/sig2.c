#include <stdio.h>
#include <signal.h>

void
SigUsrHandler(int signo)
{
	if (signo == SIGUSR1)  { // SIGUSR1이 오면
		printf("Received a SIGUSR1 signal\n");
	}
	else if (signo == SIGUSR2)  { // SIGUSR2가 오면
		printf("Received a SIGUSR2 signal\n");
	}
	else  {
		printf("Received unknown signal\n");
		printf("Terminate this process\n");
		exit(0);
	}
}

main()
{
	// SIGUSR1이나 SIGUSR2를 받으면 SigUsrHandler 호출

	/* SIGUSR1 signal handler: SigUsrHandler */
	if (signal(SIGUSR1, SigUsrHandler) == SIG_ERR)  {
		perror("signal");
		exit(1);
	}

	if (signal(SIGUSR2, SigUsrHandler) == SIG_ERR)  {
		perror("signal");
		exit(1);
	}

	for ( ; ; )
		pause();
}
