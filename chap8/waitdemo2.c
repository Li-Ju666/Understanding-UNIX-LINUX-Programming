#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>

int main()
{
    int child_action(int); 
    int parent_action(); 

    int child_id = 0; 
    child_id = fork();


    if (child_id)
    {
        int status = parent_action();      
        printf("High 8: %d\n", status>>8); 
        printf("Mid 7 value: %d\n", status & 0x0080); 
        printf("Lower 7: %d\n", status & 0x007F); 
        return 0; 
    }
    else
    {
        child_action(2);  
    }
}

int child_action(int sec)
{
    printf("From child process: my pid is %d. \n", getpid()); 
    sleep(sec); 
    exit(17); 
}

int parent_action()
{
    int status; 
    wait(&status);
    return status;  
}
