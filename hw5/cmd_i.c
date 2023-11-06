#include <stdio.h>

#define	MAX_CMD		256 

void
DoCmd(char *cmd) // cmd를 받으면 수행은 하지 않고 print해주는 함수
{
	printf("Doing %s", cmd);
	sleep(1);
	printf("Done\n");
}

main()
{
	char	cmd[MAX_CMD];

	while (1)  {
		printf("CMD> ");
		fgets(cmd, MAX_CMD, stdin); // 수행할 명령어 입력받기
		if (cmd[0] == 'q')
			break;

		DoCmd(cmd);
	}
}
