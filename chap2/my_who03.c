/* my_who03.c - The third version of my who program */
/*     feature: buffer read is used - to make less system calls */
#include <stdio.h>
#include <utmp.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <time.h>
#define SHOWHOST 1
void show_info(struct utmp*); 
int utmp_open(char*); 
struct utmp* utmp_next(); 
void utmp_close(); 

int main(){
    int utmpfd = utmp_open(UTMP_FILE);
    
    struct utmp* record = utmp_next();     

    while(record != NULL){
	show_info(record);
	record = utmp_next(); 	
    }
    utmp_close(); 
    return 0; 
}

void show_info(struct utmp* record){
    if(record->ut_type != USER_PROCESS){
	return; 
    }
    printf("%-8.8s  ", record->ut_name); 
    printf("%-8.8s  ", record->ut_line); 
    printf("%12.12s  ", ctime((time_t*)&(record->ut_time))+4); 
#if SHOWHOST
    printf("%s", record->ut_host); 
#endif
    printf("\n"); 
}
