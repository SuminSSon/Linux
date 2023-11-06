#include <stdio.h>
#include <stdlib.h>
#define	MAX_CMD		256

int mysystem(char *cmd){
    int pid;
    int status;
    char *argv[] = {"sh","-c",cmd,NULL};
    if((pid=fork())<0){ // fork하여 child process 생성
        perror("fork");
        return -1;
    }
    else if (pid==0){ // child porcess가 execv함수 실행
        if(execv("/bin/sh",argv)<0){
            perror("execv");
            return -1;
        }
    }
    if (waitpid(pid,&status,0)<0){ // process가 끝나기를 기다림
        perror("waitpid");
        return -1;
    }
    return status;
}

main()
{
    int		status;
    char cmd[MAX_CMD];
    while (1)  {
        printf("CMD> ");
        fgets(cmd, MAX_CMD, stdin); // 수행할 명령어 cmd에 저장
        if (cmd[0] == 'q') // q이면 종료
            break;
        if((status=mysystem(cmd))<0){
            perror("mysystem");
            exit(1);
        }
        printf("status = %d\n",status);
    }
}
