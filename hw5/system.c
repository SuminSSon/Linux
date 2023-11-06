#include <stdio.h>
#include <stdlib.h>

main()
{
	int		status;

	// system은 입력받은 command의 문자열을 실제로 실행시켜줌
	// child process가 알아서 fork로 만들고 exec랑 waitpid도 함
	if ((status = system("date")) < 0)  {
		perror("system");
		exit(1);
	}
	printf("exit status = %d\n", status);

	if ((status = system("nosuchcommand")) < 0)  {
		perror("system");
		exit(1);
	}
	printf("exit status = %d\n", status);

	/* $ who; exit 44 */
	if ((status = system("who; exit 44")) < 0)  {
		perror("system");
		exit(1);
	}
	printf("exit status = %d\n", status);
}
