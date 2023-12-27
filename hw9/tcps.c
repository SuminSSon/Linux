#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <signal.h>
#include "tcp.h"


int	Sockfd;

void
CloseServer() // SIGINT 발생시 socket을 종료
{
	close(Sockfd); // socket close
	printf("\nTCP Server exit.....\n");

	exit(0);
}


main(int argc, char *argv[])
{
	int			newSockfd, cliAddrLen, n;
	struct sockaddr_in	cliAddr, servAddr;
	MsgType			msg;

	signal(SIGINT, CloseServer); // SIGINT 발생시 CloseServer 호출

	if ((Sockfd = socket(PF_INET, SOCK_STREAM, 0)) < 0)  { // IPv4기반 TCP 소켓 생성
		perror("socket");
		exit(1);
	}

	bzero((char *)&servAddr, sizeof(servAddr));
	servAddr.sin_family = PF_INET;
	servAddr.sin_addr.s_addr = htonl(INADDR_ANY); // server IP addr 설정. INADDR_ANY: 모든 인터페이스에서 연결 수락
	servAddr.sin_port = htons(SERV_TCP_PORT); // server port 설정

	if (bind(Sockfd, (struct sockaddr *) &servAddr, sizeof(servAddr)) < 0)  { // Sockfd에 bind
		perror("bind");
		exit(1);
	}

	listen(Sockfd, 5); // 대기열의 크기를 5로 설정

	printf("TCP Server started.....\n");

	cliAddrLen = sizeof(cliAddr); // client addr 크기
	while (1)  {
		// client 연결 수락. 새로운 소켓 생성
		newSockfd = accept(Sockfd, (struct sockaddr *) &cliAddr, &cliAddrLen);
		if (newSockfd < 0)  {
			perror("accept");
			exit(1);
		}
		
		if ((n = read(newSockfd, (char *)&msg, sizeof(msg))) < 0)  { // msg  read
			perror("read");
			exit(1);
		}
		printf("Received request: %s.....", msg.data);

		// apply msg 작성
		msg.type = MSG_REPLY; 
		sprintf(msg.data, "This is a reply from %d.", getpid());
		if (write(newSockfd, (char *)&msg, sizeof(msg)) < 0)  {
			perror("write");
			exit(1);
		}
		printf("Replied.\n");

		usleep(10000);
		close(newSockfd);
	}
}
