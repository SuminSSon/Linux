#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/un.h>
#include <signal.h>
#include <sys/time.h>
#include <unistd.h>
#include "select.h"
#include <pthread.h>


int	TcpSockfd;
int	UdpSockfd;
int	UcoSockfd;
int	UclSockfd;

void
CloseServer() // SIGINT 발생시 socket을 종료
{
	close(TcpSockfd);
	close(UdpSockfd);
	close(UcoSockfd);
	close(UclSockfd);
	if (remove(UNIX_STR_PATH) < 0)  {
		perror("remove");
	}
	if (remove(UNIX_DG_PATH) < 0)  {
		perror("remove");
	}

	printf("\nServer daemon exit.....\n");

	exit(0);
}

void
MakeTcpSocket() // IPv4기반 TCP socket 생성
{
	struct sockaddr_in	servAddr;

	if ((TcpSockfd = socket(PF_INET, SOCK_STREAM, 0)) < 0)  {
		perror("socket");
		exit(1);
	}

	bzero((char *)&servAddr, sizeof(servAddr));
	servAddr.sin_family = PF_INET;
	servAddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servAddr.sin_port = htons(SERV_TCP_PORT);

	if (bind(TcpSockfd, (struct sockaddr *) &servAddr, sizeof(servAddr)) < 0)  {
		perror("bind");
		exit(1);
	}

	listen(TcpSockfd, 5);
}

void
MakeUdpSocket() // IPv4기반 UDP socket 생성
{
	struct sockaddr_in	servAddr;

	if ((UdpSockfd = socket(PF_INET, SOCK_DGRAM, 0)) < 0)  {
		perror("socket");
		exit(1);
	}

	bzero((char *)&servAddr, sizeof(servAddr));
	servAddr.sin_family = PF_INET;
	servAddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servAddr.sin_port = htons(SERV_UDP_PORT);

	if (bind(UdpSockfd, (struct sockaddr *) &servAddr, sizeof(servAddr)) < 0)  {
		perror("bind");
		exit(1);
	}

}

void
MakeUcoSocket() 
{
	struct sockaddr_un	servAddr;
	int					servAddrLen;

	if ((UcoSockfd = socket(PF_UNIX, SOCK_STREAM, 0)) < 0)  {
		perror("socket");
		exit(1);
	}

	bzero((char *)&servAddr, sizeof(servAddr));
	servAddr.sun_family = PF_UNIX;
	strcpy(servAddr.sun_path, UNIX_STR_PATH);
	servAddrLen = strlen(servAddr.sun_path) + sizeof(servAddr.sun_family);

	if (bind(UcoSockfd, (struct sockaddr *) &servAddr, servAddrLen) < 0)  {
		perror("bind");
		exit(1);
	}

	listen(UcoSockfd, 5);

}

void
MakeUclSocket()
{
	struct sockaddr_un	servAddr;
	int					servAddrLen;

	if ((UclSockfd = socket(PF_UNIX, SOCK_DGRAM, 0)) < 0)  {
		perror("socket");
		exit(1);
	}

	bzero((char *)&servAddr, sizeof(servAddr));
	servAddr.sun_family = PF_UNIX;
	strcpy(servAddr.sun_path, UNIX_DG_PATH);
	servAddrLen = strlen(servAddr.sun_path) + sizeof(servAddr.sun_family);

	if (bind(UclSockfd, (struct sockaddr *) &servAddr, servAddrLen) < 0)  {
		perror("bind");
		exit(1);
	}

}

void
ProcessTcpRequest() 
{
	int			newSockfd, cliAddrLen, n;
	struct sockaddr_in	cliAddr;
	MsgType			msg;

	cliAddrLen = sizeof(cliAddr);
	newSockfd = accept(TcpSockfd, (struct sockaddr *) &cliAddr, &cliAddrLen); // client accept
	if (newSockfd < 0)  {
		perror("accept");
		exit(1);
	}
		
	// msg read
	if ((n = read(newSockfd, (char *)&msg, sizeof(msg))) < 0)  {
		perror("read");
		exit(1);
	}
	printf("Received TCP request: %s.....", msg.data);

	// reply msg write
	msg.type = MSG_REPLY;
	sprintf(msg.data, "This is a reply from %d.", getpid());
	if (write(newSockfd, (char *)&msg, sizeof(msg)) < 0)  {
		perror("write");
		exit(1);
	}
	printf("Replied.\n");

	close(newSockfd);
}

void
ProcessUdpRequest()
{
	int			cliAddrLen, n;
	struct sockaddr_in	cliAddr;
	MsgType			msg;

	// msg read
	cliAddrLen = sizeof(cliAddr);
	if ((n = recvfrom(UdpSockfd, (char *)&msg, sizeof(msg), 
				0, (struct sockaddr *)&cliAddr, &cliAddrLen)) < 0)  {
		perror("recvfrom");
		exit(1);
	}
	printf("Received UDP request: %s.....", msg.data);

	// reply msg write
	msg.type = MSG_REPLY;
	sprintf(msg.data, "This is a reply from %d.", getpid());
	if (sendto(UdpSockfd, (char *)&msg, sizeof(msg),
				0, (struct sockaddr *)&cliAddr, cliAddrLen) < 0)  {
		perror("sendto");
		exit(1);
	}
	printf("Replied.\n");
}

void
ProcessUcoRequest()
{
	int					newSockfd, cliAddrLen, n;
	struct sockaddr_un	cliAddr;
	MsgType				msg;

	cliAddrLen = sizeof(cliAddr);
	newSockfd = accept(UcoSockfd, (struct sockaddr *) &cliAddr, &cliAddrLen);
	if (newSockfd < 0)  {
		perror("accept");
		exit(1);
	}
		
	if ((n = read(newSockfd, (char *)&msg, sizeof(msg))) < 0)  {
		perror("read");
		exit(1);
	}
	printf("Received UNIX-domain CO request: %s.....", msg.data);

	msg.type = MSG_REPLY;
	sprintf(msg.data, "This is a reply from %d.", getpid());
	if (write(newSockfd, (char *)&msg, sizeof(msg)) < 0)  {
		perror("write");
		exit(1);
	}
	printf("Replied.\n");

	close(newSockfd);
}

void
ProcessUclRequest()
{
	int					cliAddrLen, n;
	struct sockaddr_un	cliAddr;
	MsgType				msg;

	cliAddrLen = sizeof(cliAddr);
	if ((n = recvfrom(UclSockfd, (char *)&msg, sizeof(msg), 
				0, (struct sockaddr *)&cliAddr, &cliAddrLen)) < 0)  {
		perror("recvfrom");
		exit(1);
	}
	printf("Received UNIX-domain CL request: %s.....", msg.data);

	msg.type = MSG_REPLY;
	sprintf(msg.data, "This is a reply from %d.", getpid());
	if (sendto(UclSockfd, (char *)&msg, sizeof(msg),
				0, (struct sockaddr *)&cliAddr, cliAddrLen) < 0)  {
		perror("sendto");
		exit(1);
	}
	printf("Replied.\n");
}

main(int argc, char *argv[])
{
	fd_set	fdvar;
	int		count;
	pthread_t tid1,tid2,tid3,tid4,tid5,tid6,tid7,tid8;

	signal(SIGINT, CloseServer);

	if (pthread_create(&tid1,NULL,(void *)MakeTcpSocket,(void *)NULL)<0){
		perror("pthread_create");
		exit(1);
	}
	if (pthread_create(&tid2,NULL,(void *)MakeUdpSocket,(void *)NULL)<0){
        perror("pthread_create");
        exit(1);
    	}
	if (pthread_create(&tid3,NULL,(void *)MakeUcoSocket,(void *)NULL)<0){
        perror("pthread_create");
        exit(1);
    	}
	if (pthread_create(&tid4,NULL,(void *)MakeUclSocket,(void *)NULL)<0){
        perror("pthread_create");
        exit(1);
    	}

	printf("Server daemon started.....\n");

	while (1) {
        fd_set fdvar;
        int count;

	FD_ZERO(&fdvar);
	FD_SET(TcpSockfd, &fdvar);
	FD_SET(UdpSockfd, &fdvar);
	FD_SET(UcoSockfd, &fdvar);
	FD_SET(UclSockfd, &fdvar);

        if ((count = select(10, &fdvar, NULL, NULL, NULL)) < 0) {
            perror("select");
            exit(1);
        }

        while (count--) {
        	if (FD_ISSET(TcpSockfd, &fdvar)) {
			if (pthread_create(&tid5, NULL, ProcessTcpRequest, NULL) < 0) {
                    		perror("pthread_create");
                    		exit(1);
                	}
                	if (pthread_join(tid5, NULL) < 0) {
                    	perror("pthread_join");
                    	exit(1);
                	}
            	} else if (FD_ISSET(UdpSockfd, &fdvar)) {
                	if (pthread_create(&tid6, NULL, ProcessUdpRequest, NULL) < 0) {
                    	perror("pthread_create");
                    	exit(1);
                	}
                	if (pthread_join(tid6, NULL) < 0) {
                    	perror("pthread_join");
                    	exit(1);
                	}
            	} else if (FD_ISSET(UcoSockfd, &fdvar)) {
                	if (pthread_create(&tid7, NULL, ProcessUcoRequest, NULL) < 0) {
                    	perror("pthread_create");
                    	exit(1);
               		}
                	if (pthread_join(tid7, NULL) < 0) {
                    	perror("pthread_join");
                    	exit(1);
                	}
            	} else if (FD_ISSET(UclSockfd, &fdvar)) {
                	if (pthread_create(&tid8, NULL, ProcessUclRequest, NULL) < 0) {
                    	perror("pthread_create");
                    	exit(1);
                	}
                	if (pthread_join(tid8, NULL) < 0) {
                    	perror("pthread_join");
                    	exit(1);
                	}
		}
		}
   	}

	// Join threads
	if (pthread_join(tid1, NULL) < 0) {
		perror("pthread_join");
		exit(1);
	}

	if (pthread_join(tid2, NULL) < 0) {
		perror("pthread_join");
		exit(1);
	}

	if (pthread_join(tid3, NULL) < 0) {
		perror("pthread_join");
		exit(1);
	}


	if (pthread_join(tid4, NULL) < 0) {
		perror("pthread_join");
		exit(1);
	}

	return 0;
}
