#include <stdio.h>
#include <signal.h>
#include <unistd.h>

int main()
{
    void wakeup(int); 
    printf("Gonna sleep for 1 second! \n"); 
    signal(SIGALRM, wakeup); 
    alarm(2); 
    pause(); 
    printf("Pause ended! \n"); 
    return 0; 
}

void wakeup(int sig)
{
    printf("Signal received from kernel! \n"); 
}
