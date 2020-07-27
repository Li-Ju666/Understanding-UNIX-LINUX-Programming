/* get_response03.c - */ 
/* purpose: ask a question and wait for a y/n answer */
/* method: use getchar and ignore non y/n answers, with tty char-by-char mode */
/* return: 0 for yes, 1 for no */
/* better: close echo and invalid input information */

#include <stdio.h>
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <signal.h>

#define QUESTION "Do you want another transaction? "
#define MAX_TRIES 3
#define SLEEP_TIME 2

void tty_save_config(int how)
{
    /* Backup and restore stdin configuration: */ 
    /*     how = 0: backup */
    /*     how = others: restore backups */
    static struct termios ori_mode; 
    static int ori_flag; 
    if (how == 0)
    {
        tcgetattr(0, &ori_mode);
        ori_flag = fcntl(0, F_GETFL); 
    }
    else
    {
        tcsetattr(0, TCSANOW, &ori_mode);
        fcntl(0, F_SETFL, ori_flag); 
    }
}

void tty_set_nodelay()
{
    int config = fcntl(0, F_GETFL); 
    config |= O_NDELAY; 
    fcntl(0, F_SETFL, config); 
}

void tty_set_cbc_noecho()
{
    /* set stdin as char-by-char mode */
    struct termios config; 
    tcgetattr(0, &config); 
    /* Disable buffer input (line-by-line input) and echo*/
    config.c_lflag &= ~(ICANON | ECHO); 
    /* Maximum character: 1 */ 
    config.c_cc[VMIN] = 1; 
    tcsetattr(0, TCSANOW, &config);
}

void handler(int signal)
{
    printf("Handled by handler! \n"); 
    tty_save_config(1); 
    exit(-1); 
}
int get_response(char* question, int max_tries)
{
    tty_save_config(0); 
    tty_set_cbc_noecho(); 
    tty_set_nodelay(); 
    signal(SIGINT, handler); 
    signal(SIGQUIT, SIG_IGN); 
    printf("%s(y/n)", question); 
    /* fflush(stdout); */  
    while (max_tries > 0)
    {
        switch (getchar())
        {
            case 'Y': 
            case 'y': {tty_save_config(1); return 0; }
            case 'N': 
            case 'n': {tty_save_config(1); return 1; }
            default: {max_tries--; sleep(SLEEP_TIME); }
        }
    }
    putchar('\a');
    tty_save_config(1);  
    return 2; 
}

int main()
{
    printf("%d\n", get_response(QUESTION, MAX_TRIES)); 
}

