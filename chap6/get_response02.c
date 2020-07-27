/* get_response02.c - */ 
/* purpose: ask a question and wait for a y/n answer */
/* method: use getchar and ignore non y/n answers, with tty char-by-char mode */
/* return: 0 for yes, 1 for no */
#include <stdio.h>
#include <termios.h>
#include <unistd.h>

#define QUESTION "Do you want another transaction? "

void tty_save_config(int how)
{
    /* Backup and restore stdin configuration: */ 
    /*     how = 0: backup */
    /*     how = others: restore backups */
    static struct termios origin; 
    if (how == 0)
    {
        tcgetattr(0, &origin);
    }
    else
    {
        tcsetattr(0, TCSANOW, &origin);
    }
}

void tty_set_cbc()
{
    /* set stdin as char-by-char mode */
    struct termios config; 
    tcgetattr(0, &config); 
    /* Disable buffer input (line-by-line input) */
    config.c_lflag &= ~ICANON; 
    /* Maximum character: 1 */ 
    config.c_cc[VMIN] = 1; 
    tcsetattr(0, TCSANOW, &config);
}

int get_response(char* question)
{
    tty_save_config(0); 
    tty_set_cbc(); 
    printf("%s(y/n)", question); 
    while (1)
    {
        switch (getchar())
        {
            case 'Y': 
            case 'y': {tty_save_config(1); return 0; }
            case 'N': 
            case 'n': {tty_save_config(1); return 1; }
            default: printf("\nInvalid input! \n"); 
        }
    }
}

int main()
{
    return get_response(QUESTION);
}

