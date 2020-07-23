/* logout.c - to log out from a Unix/Linux system: modify utmp file records */
#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <utmp.h>
#include <string.h>
#include <time.h>
int my_logout(char* user){
    int fd; 
    struct utmp rec; 
    int len = sizeof(struct utmp); 
    
    if((fd = open(UTMP_FILE, O_RDWR)) == -1){
	return -1; 
    }
    
    while(len == read(fd, &rec, len)){
	if(strncmp(rec.ut_line, user, sizeof(rec.ut_line)) == 0){
	    rec.ut_type = DEAD_PROCESS; 
	    if(time((time_t*)&(rec.ut_time))){
		if(lseek(fd, -len, SEEK_CUR) != -1){
		    if(write(fd, &rec, len) == len){
			printf("Logged out! \n"); 
		    }
		}
	    }
	    break; 
	}
    }
    if(close(fd) == -1){
	return -1; 
    }
    return 0; 
}


int main(int argc, char** argv){
    int i=0; 
    if(argc == 2){
	i = my_logout(argv[1]); 
    }
    return i; 
}


