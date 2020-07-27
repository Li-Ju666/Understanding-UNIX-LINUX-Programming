/* get_response01.c - */ 
/* purpose: ask a question and wait for a y/n answer */
/* method: use getchar and ignore non y/n answers */
/* return: 0 for yes, 1 for no */
#include <stdio.h>

#define QUESTION "Do you want another transaction? "

int get_response(char* question)
{
    printf("%s(y/n)\n", question); 
    while (1)
    {
        switch (getchar())
        {
            case 'y': return 0; 
            case 'n': return 1; 
        }
    }
}



int main()
{
    return get_response(QUESTION); 
}

