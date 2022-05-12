#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
 
int main()
{
    int pipe1[2];
    pid_t p;
 
    if (pipe(pipe1) == -1) {
        fprintf(stderr, "Pipe1 hiba");
        return 1;
    }
 
    p = fork();
 
    if (p < 0) {
        fprintf(stderr, "fork hiba");
        return 1;
    }
 
    // Parent process
    else if (p > 0) {
        char str[100];
 
        printf("Szulo processz vár\n");

        wait(NULL);

        printf("Szulo process olvas.\n");

        read(pipe1[0], str, 100);
        printf("Pipelinerol olvasva: %s\n", str);
        close(pipe1[0]);
    }
    else { 
 
        printf("Gyerek processz.\n");
        char output_string[100];
        strcpy(output_string, "Szabo Levente GF2465");
        write(pipe1[1], output_string, strlen(output_string) + 1);
        close(pipe1[1]);
 
        exit(0);
    }
}
