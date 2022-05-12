#include<stdio.h>
#include<signal.h>
#include <stdlib.h>
  
int sigint_counter = 0;
void handle_signals(int sig) {
    if (sig == 3) {
        printf("Quit signal caught.\n");
        exit(0);
    } else if (sig == 2) {
        if (sigint_counter == 0) {
            printf("First SIGINT.\n");
            sigint_counter++;
            signal(SIGINT, SIG_DFL);
        }
    }
}

int main()
{
    signal(SIGINT, handle_signals);
    signal(SIGQUIT, handle_signals);
    
    while (1) ;
    return 0;
}
