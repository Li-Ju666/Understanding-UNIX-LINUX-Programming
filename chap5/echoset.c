/* echostate.c */
/* Purpose: to show if echo in tty driver for stdin is closed or not */
/* Mehod: read termios info and check state */
#include <stdio.h>
#include <termios.h>

int main(int argc, char** argv)
{
    struct termios info; 
    if (tcgetattr(0, &info) == -1)
    {
        perror("tcgetattr"); 
        return -1; 
    }

    if (argv[1][0] == 'y')
    {
        info.c_lflag |= ECHO; 
    }
    else if (argv[1][0])
    {
        info.c_lflag &= ~ECHO; 
    }

    if (tcsetattr(0, TCSANOW, &info) == -1)
    {
        perror("tcsetattr"); 
        return -1; 
    }
    return 0; 
}
