#include <stdio.h>
#include <stdlib.h>

void
myexit1()
{
	printf("first exit handler\n");
}

void
myexit2()
{
	printf("second exit handler\n");
}

// atexit는 main함수가 끝나고 실행됨.
// stack형태로 관리하기 때문에 myexit1이 먼저 출력됨
main()
{
	/* Add myexit2 to exit functions */
	if (atexit(myexit2))  { // atexit함수를 통해 exit handler 실행
		perror("atexit");
		exit(1);
	}

	if (atexit(myexit1) != 0)  {
		perror("atexit");
		exit(1);
	}

	if (atexit(myexit1) != 0)  {
		perror("atexit");
		exit(1);
	}

	printf("main is done\n");
}
