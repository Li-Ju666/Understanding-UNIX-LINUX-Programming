/* my_more.c -- version 0.2 of more */
/* read and print 24 s then pause for following commands */
/* new feature: more command can be used for shell pipeline */

#include <stdio.h>
#include <stdlib.h>
#define PAGELEN 24
#define LINELEN 512

void do_more(FILE*); 
int see_more(FILE*); 

int main(int argc, char** argv){
    FILE* fp; 
    if(argc == 1){
	do_more(stdin); 
    }
    else{
	while(--argc){
	    if((fp = fopen(*(++argv), "r")) != NULL){
		do_more(fp); 
		fclose(fp); 
	    }
	    else
		exit(1); 
	    
	    return 0; 
	}
    }

}

void do_more(FILE* fp){
    /* read PAGELEN lines, then call see_more() for further instructions */
    char line[LINELEN]; 
    int line_num=0; 
    int reply;
    FILE* tty = fopen("/dev/tty", "r"); 
    if(tty == NULL) exit(1);  
    while(fgets(line, LINELEN, fp)){
	if(line_num == PAGELEN){
	    reply = see_more(tty); 
	    if(reply == 0){
		break; 
	    }
	    line_num -= reply; 
	}
	if(fputs(line, stdout) == EOF){
	    exit(1); 
	}
	line_num++;  
    }
}

int see_more(FILE* tty){
    /* print message, wait for response: */ 
    /* q means quit, space means print a page more and CR means print a line more */
    int c; 
    printf("\e[7mmore?\n\e[0m"); 
    while((c = getc(tty)) != EOF)
    {
	if(c == 'q') return 0; 
	if(c == ' ') return PAGELEN; 
	if(c == '\n') return 1; 
	else{
	    perror("Invalid input! \n"); 
	    return 0; 
	}
    }
}


