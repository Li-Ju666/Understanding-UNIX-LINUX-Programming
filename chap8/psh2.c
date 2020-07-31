#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>

#define MAXARGS 20
#define ARGLEN 100


int main()
{
    void execute(char**); 
    char* arglist[MAXARGS+1]; 
    int numargs; 
    char argbuf[ARGLEN]; 
    char* makestring(); 
    numargs = 0;

    while (numargs < MAXARGS)
    {
        printf("Arg[%d]: ", numargs); 
        if (fgets(argbuf, ARGLEN, stdin) && *argbuf != '\n')
            arglist[numargs++] = makestring(argbuf); 
        else
        {
            if (numargs > 0)
            {
                arglist[numargs] = NULL; 
                execute(arglist); 
                numargs = 0; 
            }
        }
    }
    return 0; 
}

void execute(char** arglist)
{
    int child_id = 0; 
    child_id = fork(); 
    if (child_id)
    {
        signal(SIGINT, SIG_IGN); 
        int status; 
        wait(&status); 
        printf("return value: %d, core dump bit: %d, signal value: %d\n", 
                status>>8, status & 0x0080, status & 0x007F); 
        signal(SIGINT, SIG_DFL);  
    }
    else if (child_id == -1)
    {
        perror("fork"); 
    }
    else 
    {
        execvp(arglist[0], arglist); 
    }
}

char* makestring(char* buff)
{
    char* cp; 
    buff[strlen(buff)-1] = '\0'; 
    cp = malloc(strlen(buff)+1); 
    if (cp == NULL)
    {
        fprintf(stderr, "No memory\n"); 
        exit(1); 
    }
    strcpy(cp, buff); 
    return cp; 
}
