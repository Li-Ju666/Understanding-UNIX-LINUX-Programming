/* ticker_demo.c: */
/* demonstrate the use of interval timer to generate regular */
/* signals, which are in turn caught and used to count down */
#include <stdio.h>
#include <sys/time.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
int main()
{
    void countdown(int); 
    int set_sticker(int); 

    signal(SIGALRM, countdown); 
    if (set_sticker(500) == -1)
    {
        perror("set_ticker"); 
    }
    else
    {
        while (1)
        {
            pause(); 
        }
    }
}

void countdown(int signal)
{
    static int num = 10; 
    printf("%d..", num--); 
    fflush(stdout); 
    if (num < 0)
    {
        printf("Done! \n"); 
        exit(0); 
    }
}

int set_sticker(int n_msec)
{
    struct itimerval new_timeset; 
    long n_sec, n_usec; 

    n_sec = n_msec/1000; 
    n_usec = (n_msec % 1000)*1000L; 

    new_timeset.it_interval.tv_sec = n_sec; 
    new_timeset.it_interval.tv_usec = n_usec; 

    new_timeset.it_value.tv_sec = n_sec; 
    new_timeset.it_value.tv_usec = n_usec; 

    return setitimer(ITIMER_REAL, &new_timeset, NULL); 
}
