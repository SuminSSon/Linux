#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include "fifo.h"


main()
{
	char		fname[MAX_FIFO_NAME];
	int			fd, sfd, n;
	MsgType		msg;

	sprintf(fname, ".fifo%d", getpid()); // .fifo + pid로 fifo  생성
	if (mkfifo(fname, 0600) < 0)  {
		perror("mkfifo");
		exit(1);
	}

	if ((fd = open(fname, O_RDWR)) < 0)  { // 생성한 fifo 열기
		perror("open");
		exit(1);
	}
	if ((sfd = open(SERV_FIFO, O_RDWR)) < 0)  { // SERV_FIFO 열기
		perror("open");
		exit(1);
	}

	strcpy(msg.returnFifo, fname);
	sprintf(msg.data, "This is a request from %d.", getpid());
	write(sfd, (char*)&msg, sizeof(msg)); //server fifo에 write
	printf("Sent a request.....");

	if ((n = read(fd, (char*)&msg, sizeof(msg)))<0)  { // 생성한 fifo에서 msg 읽기
		perror("read");
		exit(1);
	}

	printf("Received reply: %s\n", msg.data);

	close(fd);
	close(sfd);

	/* Remove temporary FIFO */
	if (remove(fname) < 0)  {
		perror("remove");
		exit(1);
	}
}
