#include <stdio.h>
#include <signal.h>
#include <unistd.h>

#define INPUTLEN 100

int main()
{
    struct sigaction new_handler; 
    sigset_t intset;  
    void inthandler(int); 
    char x[INPUTLEN]; 

    new_handler.sa_handler = inthandler; 
    new_handler.sa_flags = SA_RESETHAND; 
    
    sigemptyset(&intset); 
    sigaddset(&intset, SIGQUIT); 
    new_handler.sa_mask = intset; 

    if (sigaction(SIGINT, &new_handler, NULL) == -1)
    {
        perror("sigaction"); 
    }
    else
    {
        while (1)
        {
            fgets(x, INPUTLEN, stdin); 
            printf("input: %s", x); 
        }
    }
}

void inthandler(int signal)
{
    printf("Interuput handler is called...\n"); 
    sleep(3); 
    printf("Interupt handler finished! \n"); 
}
