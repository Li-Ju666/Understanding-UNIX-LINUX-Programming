/* echostate.c */
/* Purpose: to show if echo in tty driver for stdin is closed or not */
/* Mehod: read termios info and check state */
#include <stdio.h>
#include <termios.h>

int main()
{
    struct termios info; 
    if (tcgetattr(0, &info) == -1)
    {
        perror("tcgetattr"); 
        return -1; 
    }
    if (info.c_lflag & ECHO)
    {
        printf("Echo is on! \n"); 
    }
    else
    {
        printf("Echo is off! \n"); 
    }
}
