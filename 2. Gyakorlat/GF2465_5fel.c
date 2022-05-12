#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>

int main(int argc, char** argv) {
    pid_t parent_pid;
    pid_t child_pid;
    int pid, status;

    parent_pid = getpid();
    printf("A szulo process ID: %d\n", parent_pid);

    if((pid = fork())==0) {
        child_pid = getpid();
        printf("A gyerek process ID: %d\n", child_pid);
        status = execlp(argv[1], argv[1], (char *)0);
		if (status == -1)
		{	perror("Hiba tortent a gyerek processz futtatasakor.\n");
			exit (1);
		}
    }
	printf("A szulo processz (%d) var a gyermek processz (%d) befejezesere.\n", parent_pid, child_pid);
	if (pid != wait(&status)) {
        perror(" Szulo - varakozasi hiba ");
    } else {
        printf("A gyerek processz statusza: %d\n", status);
    }

    printf("A gyerek processnek vége.\n");
    printf("A szulo process ID: %d\n", parent_pid);
    
    return 0;
}
