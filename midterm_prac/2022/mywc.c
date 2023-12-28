#include <stdio.h>
#include <unistd.h>
#include <unistd.h>

void
main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s filename\n", argv[0]);
        exit(1);
    }

    pid_t pid;
    char *filename = argv[1];
    char *v[]={"wc","-w",argv[1],NULL};

    if ((pid = fork()) < 0)  {
        perror("fork");
        exit(1);
    } else if (pid == 0) {
    	if(execvp("wc",v)<0){
		perror("execvp");
		exit(1);
	}
    }

    if (waitpid(pid, NULL, 0) < 0)  {
        perror("waitpid");
        exit(1);
    }
}

