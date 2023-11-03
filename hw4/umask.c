#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>

main()
{
	umask(0); // 
	if (creat("bar", S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | 
				S_IROTH | S_IWOTH) < 0)  { // bar파일에 user의 rw, group의 rw, other의 rw 권한 부여
		perror("creat");
		exit(1);
	}

	/* Set file mode creation mask: S_IRGRP, S_IWGRP, S_IROTH, S_IWOTH */
	umask(S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH);
	if (creat("foo", S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | 
				S_IROTH | S_IWOTH) < 0)  { // foo파일에 user의 rw권한만 있음.
		perror("creat");
		exit(1);
	}
}
