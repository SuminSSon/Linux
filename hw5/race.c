#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

void
CharAtaTime(char *str)
{
	char	*ptr;
	int		c, i;

	setbuf(stdout, NULL);
	for (ptr = str ; c = *ptr++ ; )  { // char 하나씩 출력
		for(i = 0 ; i < 999999 ; i++) 
			;
		putc(c, stdout);
	}
}

main()
{
	pid_t	pid;

	if ((pid = fork()) < 0)  {
		perror("fork");
		exit(1);
	}
	else if (pid == 0)  { // child process
		CharAtaTime("output from child\n");
	} 
	else  { // aprent process
		CharAtaTime("output from parent\n");
	}
}
