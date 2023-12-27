#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <signal.h>
#include "udp.h"


int	Sockfd;

void
CloseServer() // SIGINT 발생시 socket을 종료
{
	close(Sockfd);
	printf("\nUDP Server exit.....\n");

	exit(0);
}


main(int argc, char *argv[])
{
	int			cliAddrLen, n;
	struct sockaddr_in	cliAddr, servAddr;
	MsgType			msg;

	signal(SIGINT, CloseServer); // SIGINT 발생시 CloseServer 호출

	if ((Sockfd = socket(PF_INET, SOCK_DGRAM, 0)) < 0)  { // IPv4기반 UDP 소켓 생성
		perror("socket");
		exit(1);
	}

	bzero((char *)&servAddr, sizeof(servAddr));
	servAddr.sin_family = PF_INET;
	servAddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servAddr.sin_port = htons(SERV_UDP_PORT);

	if (bind(Sockfd, (struct sockaddr *) &servAddr, sizeof(servAddr)) < 0)  { // Sockfd에 bind
		perror("bind");
		exit(1);
	}

	printf("UDP Server started.....\n");

	cliAddrLen = sizeof(cliAddr);
	while (1)  {
		// msg read
		if ((n = recvfrom(Sockfd, (char *)&msg, sizeof(msg), 
					0, (struct sockaddr *)&cliAddr, &cliAddrLen)) < 0)  { // data가 도착할 대까지 block
			perror("recvfrom");
			exit(1);
		}
		printf("Received request: %s.....", msg.data);

		// reply msg write
		msg.type = MSG_REPLY;
		sprintf(msg.data, "This is a reply from %d.", getpid());
		if (sendto(Sockfd, (char *)&msg, sizeof(msg),
					0, (struct sockaddr *)&cliAddr, cliAddrLen) < 0)  {
			perror("sendto");
			exit(1);
		}
		printf("Replied.\n");
	}
}
