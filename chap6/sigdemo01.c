#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
int main()
{
    void f(int); 
    signal(SIGINT, f); 
    while (1)
    {
        printf("Hello! \n"); 
        sleep(1); 
    }
}

void f(int signal)
{
    printf("OUUUUUCH! \n"); 
    exit(-1); 
}
