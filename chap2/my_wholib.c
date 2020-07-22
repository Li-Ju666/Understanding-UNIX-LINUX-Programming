/* my_wholib.c - functions to buffer reads from utmp file */

/* functions are: */ 
/*     int utmp_open(file_name)    - open file */
/* 	return -1 on error */
/*     
 *     struct utmp* utmp_next()		    - return pointer to next utmp record */
/* 	return NULL on eof */
/*     
 *     int utmp_close()	    - close file */

/*     reads NRECS per read and then push them out of buffer one by one */
#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <utmp.h>

#define NRECS 16
#define NULLUT ((struct utmp*)NULL)
#define UTSIZE (sizeof(struct utmp))

int utmp_reload(); 

static char utmpbuf[NRECS*UTSIZE]; 
static int num_recs; 
static int cur_rec; 
static int fd_utmp = -1; 

int utmp_open(char* file){
    fd_utmp = open(file, O_RDONLY); 
    cur_rec = num_recs = 0; 
    return fd_utmp;  
}

struct utmp* utmp_next(){
    struct utmp* recp; 
    if(fd_utmp == -1){
	return NULLUT; 
    }
    if(cur_rec == num_recs && utmp_reload() == 0){
	return NULLUT; 
    }
    
    recp = (struct utmp*)&utmpbuf[cur_rec*UTSIZE]; 
    cur_rec ++; 
    return recp; 
}

int utmp_reload(){
    int read_size; 
    read_size = read(fd_utmp, utmpbuf, NRECS*UTSIZE); 
    num_recs = read_size/UTSIZE; 
    cur_rec = 0; 
    return num_recs; 
}

void utmp_close(){
    if(fd_utmp != -1){
	close(fd_utmp); 
    }
}
