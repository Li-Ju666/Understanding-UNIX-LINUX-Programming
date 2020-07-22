/* my_who02.c - a second version of my who program which can open, */ 
/*     read UTMP file and show results */
#include <stdio.h>
#include <utmp.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <time.h>
#define SHOWHOST 1
void show_info(struct utmp*); 
int main(){
    struct utmp cur_record; 
    int utmpfd = open(UTMP_FILE, O_RDONLY);
    int reclen = sizeof(cur_record); 
    
    if(utmpfd == -1){
	perror(UTMP_FILE); 
	exit(-1); 	
    }
    while(read(utmpfd, &cur_record, reclen) == reclen)
	show_info(&cur_record); 
    close(utmpfd); 
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
