/* copy01.c - The first version of my copy program */
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

#define BUFFERSIZE 4096
#define COPYMODE 0644

int main(int argc, char** argv){
    if(argc != 3){
	printf("Usage: copy source-file destination-file\n"); 
	exit(-1); 
    }
    int in_fd, out_fd; 
    char buf[BUFFERSIZE]; 
    int n_char; 
    if((in_fd = open(argv[1], O_RDONLY)) == -1){
	printf("Failed to open file %s. \n", argv[1]); 
	exit(-1); 
    }
    if((out_fd = creat(argv[2], COPYMODE)) == -1){
	close(in_fd); 
	printf("Failed to create file %s. \n", argv[2]); 
	exit(-1); 
    }
    while((n_char = read(in_fd, buf, BUFFERSIZE)) > 0){
	printf("Now n_char is %d, BUFFERSIZE is %d. \n", n_char, BUFFERSIZE); 
	if(write(out_fd, buf, n_char) != n_char){
	    printf("Error: failed to write data for file %s. \n", argv[2]); 
	    exit(-1); 
	}
    }
    if(n_char < 0){
	printf("Error: failed to read data from file %s. \n", argv[1]); 
	exit(-1); 	
    }
    if(close(in_fd) == -1 || close(out_fd) == -1){
	printf("Failed to close files. \n"); 
	exit(-1); 
    }
}
