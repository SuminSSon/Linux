#include <stdio.h>
#include "synclib.h"

#define	NLOOPS	5


main()
{
	int		i;
	pid_t	pid;

	TELL_WAIT();
	if ((pid = fork()) < 0)  {
		perror("fork");
		exit(1);
	}
	else if (pid > 0)  { // Parent process
		for (i = 0 ; i < NLOOPS ; i++)  {
			TELL_CHILD(); // Pfd1에 p를 write
			printf("Parent: Tell to child\n");
			printf("Parent: Wait for child to tell\n"); 
			WAIT_CHILD(); // Pfd2에서 c가 write될 때까지 wait
	       	} 
	}
	else  { // Child process
		for (i = 0 ; i < NLOOPS ; i++)  {
			printf("Child: Wait for parent to tell\n");
			WAIT_PARENT(); // Pfd1에서 p가 wrtie될 때까지 wait
			TELL_PARENT(); // Pfd1에 c를 write
			printf("Child: Tell to parent\n");
		}
	}
}
