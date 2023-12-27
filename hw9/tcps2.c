#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <signal.h>
#include <unistd.h>
#include <sys/wait.h>
#include "tcp.h"

int Sockfd;

void CloseServer() // SIGINT 발생시 socket 종료
{
    close(Sockfd);
    printf("\nTCP Server exit.....\n");
    exit(0);
}

void HandleClient(int newSockfd) {
    MsgType msg;
    int n;

    if ((n = read(newSockfd, (char *)&msg, sizeof(msg))) < 0) {
        perror("read");
        exit(1);
    }
    printf("Received request: %s.....", msg.data);

    // Apply msg 작성
    msg.type = MSG_REPLY;
    sprintf(msg.data, "This is a reply from %d.", getpid());
    if (write(newSockfd, (char *)&msg, sizeof(msg)) < 0) {
        perror("write");
        exit(1);
    }
    printf("Replied.\n");

    usleep(10000);
    close(newSockfd);
}

int main(int argc, char *argv[]) {
    int newSockfd, cliAddrLen;
    struct sockaddr_in cliAddr, servAddr;

    signal(SIGINT, CloseServer);

    if ((Sockfd = socket(PF_INET, SOCK_STREAM, 0)) < 0) {
        perror("socket");
        exit(1);
    }

    bzero((char *)&servAddr, sizeof(servAddr));
    servAddr.sin_family = PF_INET;
    servAddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servAddr.sin_port = htons(SERV_TCP_PORT);

    if (bind(Sockfd, (struct sockaddr *)&servAddr, sizeof(servAddr)) < 0) {
        perror("bind");
        exit(1);
    }

    listen(Sockfd, 5);

    printf("TCP Server started.....\n");

    cliAddrLen = sizeof(cliAddr);
    while (1) {
        newSockfd = accept(Sockfd, (struct sockaddr *)&cliAddr, &cliAddrLen);
        if (newSockfd < 0) {
            perror("accept");
            exit(1);
        }

        pid_t child_pid = fork();
        if (child_pid == 0) { // Child process
            close(Sockfd);  // Child doesn't need the listener socket
            HandleClient(newSockfd);
            exit(0);
        } else if (child_pid < 0) {
            perror("fork");
            exit(1);
        } else { // Parent process
            close(newSockfd);  // Parent doesn't need the connected socket
        }
    }
}

