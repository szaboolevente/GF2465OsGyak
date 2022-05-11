#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>

int main() {
    pid_t parent_pid;
    pid_t child_pid;
    int pid, status;

    parent_pid = getpid();
    printf("A szülő process ID: %d\n", parent_pid);

    if((pid = fork())==0) {
        child_pid = getpid();
        printf("A gyerek process ID: %d\n", child_pid);
        status = execl("./child", "./child", (char *)0);
		if (status == -1)
		{	perror("Hiba történt a gyerek futtatáskor.\n");
			exit (1);
		}        
    }
	printf("A szülő (%d) vár a gyermek (%d) befejeződésére.\n", parent_pid, child_pid);
	if (pid != wait(&status)) {
        perror(" Szülő - várakozási hiba ");
    }

    printf("A gyerek processnek vége.\n");
    printf("A szülő process ID: %d\n", parent_pid);
    
    return 0;
}
