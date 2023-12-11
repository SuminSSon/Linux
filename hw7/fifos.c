#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <signal.h>
#include <errno.h>
#include "fifo.h"


void
SigIntHandler(int signo) // SIGINT 감지 시 SERV_FIFO 삭제
{
	if (remove(SERV_FIFO) < 0)  {
		perror("remove");
		exit(1);
	}

	exit(0);
}


main()
{
	int			fd, cfd, n;
	MsgType		msg;

	if (signal(SIGINT, SigIntHandler) == SIG_ERR)  { // SigIntHandler 호출
		perror("signal");
		exit(1);
	}

	if (mkfifo(SERV_FIFO, 0600) < 0)  { // SERV_FIFO의 권한을 0600으로 생성
		if (errno != EEXIST)  {
			perror("mkfifo");
			exit(1);
		}
	}

	if ((fd = open(SERV_FIFO, O_RDWR)) < 0)  { // 생성한 SERV_FIFO open
		perror("open");
		exit(1);
	}

	while (1)  {
		if ((n = read(fd, (char *)&msg, sizeof(msg))) < 0)  {
			if (errno == EINTR)  { // read가 중단된 경우
				continue;
			}
			else  {
				perror("read");
				exit(1);
			}
		}
		printf("Received request: %s.....", msg.data);

		if ((cfd = open(msg.returnFifo, O_WRONLY))<0)  {
			perror("open");
			exit(1);
		}
		sprintf(msg.data, "This is a reply from %d.", getpid());
		write(cfd, (char *)&msg, sizeof(msg));
		close(cfd);
		printf("Replied.\n");
	}
}
