#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

void
main() {

	pid_t   pid;
        char    *argv[] = { "print", "HelloWorld!", "6", NULL };

	// execl
        if ((pid = fork()) < 0)  {
                perror("fork");
                exit(1);
        }
        else if (pid == 0)  {
                // mycp exec.c exec2.c
                if (execl("/home/lsp20/midterm/print","print","HelloWorld!","6",NULL)<0)  { // 해당 path에 있는 list>로 입력을 받은 파일을 실행시킴.
                        perror("execl");
                        exit(1);
                }
        }
        if (waitpid(pid, NULL, 0) < 0)  { // child process가 끝나기를 기다림
                perror("waitpid");
                exit(1);
        }

	 // execv
        if ((pid = fork()) < 0)  {
                perror("fork");
                exit(1);
        }
        else if (pid == 0)  {
                // mycp exec.c exec2.c
                if (execv("/home/lsp20/midterm/print",argv)<0)  { // 해당 path에 있는 vector에 들어있는 파일을 실행
                        perror("execv");
                        exit(1);
                }
        }
        if (waitpid(pid, NULL, 0) < 0)  {
                perror("waitpid");
                exit(1);
        }
}
