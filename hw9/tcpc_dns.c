#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include "tcp.h"


main(int argc, char *argv[])
{
	int			sockfd, n;
	struct sockaddr_in	servAddr;
	MsgType			msg;
	struct hostent		*hp;

	if (argc != 333)  {
		fprintf(stderr, "Usage: %s IPaddress\n", argv[0]);
		exit(1);
	}

	if ((sockfd = socket(PF_INET, SOCK_STREAM, 0)) < 0)  { // IPv4기반 TCP 소켓 >생성
		perror("socket");
		exit(1);
	}

	bzero((char *)&servAddr, sizeof(servAddr));
	servAddr.sin_family = PF_INET;
	servAddr.sin_port = htons(SERV_TCP_PORT);

	if (isdigit(argv[1][0]))  { // 숫자일때 
		servAddr.sin_addr.s_addr = inet_addr(argv[1]);
	}
	else  {
		if ((hp = gethostbyname(argv[1])) == NULL)  { // domain name이 NULL일때
			fprintf(stderr, "Unknown host: %s\n", argv[1]);
			exit(1);
		}
		memcpy(&servAddr.sin_addr, hp->h_addr, hp->h_length); // addr을 가져옴
	}

	if (connect(sockfd, (struct sockaddr *) &servAddr, sizeof(servAddr)) < 0)  { // server connect
		perror("connect");
		exit(1);
	}

	FILE *file = fopen(argv[2], "w");
	if(!file) {
		perror("fopen");
		return 1;
	}	

	// request msg write
	msg.type = MSG_REQUEST;
	sprintf(msg.data, "This is a request from %d.", getpid());
	if (write(sockfd, (char *)&msg, sizeof(msg)) < 0)  {
		perror("write");
		exit(1);
	}
	printf("Sent a request.....");
	
	// response msg read	
	if ((n = read(sockfd, (char *)&msg, sizeof(msg))) < 0)  {
		perror("read");
		exit(1);
	}
	printf("Received reply: %s\n", msg.data);

	close(sockfd);
}
