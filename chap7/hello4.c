#include <stdio.h>
#include <ncurses.h>
#include <unistd.h>

int main()
{
    initscr(); 
    clear();
    while (1)
    {for(int i=0; i<LINES; i++)
    {
        move(i, 2*i); 
        standout();  
        addstr("Hello world!");
        standend();  
        refresh();  
        usleep(50*1000);
        move(i, 2*i);  
        addstr("               "); 
    }}
    endwin(); 
}
