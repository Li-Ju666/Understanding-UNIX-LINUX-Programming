#include <stdio.h>
#include <ncurses.h>
#include <unistd.h>

int main()
{
    initscr(); 
    clear(); 
    for(int i=0; i<LINES; i++)
    {
        move(i, 2*i); 
        if (i%2 == 1) standout(); 
        addstr("Hello world!"); 
        if (i%2 == 1) standend(); 
        usleep(50*1000); 
        refresh();  
    }
    endwin(); 
}
