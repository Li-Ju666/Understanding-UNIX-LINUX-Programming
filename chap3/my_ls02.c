/* my_ls02.c - function to list all files in given directory with details*/
#include <stdio.h>
#include <dirent.h>
#include <sys/stat.h>
#include <string.h>

void show_stat_info(const char* fname, struct stat* rec); 

void do_ls(char* dir_name){
    DIR* cur_dir = opendir(dir_name); 
    if(cur_dir == NULL){
	    perror("Error: "); 
	    return; 
    }
    struct dirent* entity; 
    /* to store file path */
    char filepath[1000]; 
    /* to store file stats */ 
    struct stat rec; 
    
    while((entity = readdir(cur_dir)) != NULL){
        /* empty file path */
        filepath[0] = '\0';  
        strcat(filepath, dir_name); 
        strcat(filepath, "/"); 
        strcat(filepath, entity->d_name); 
        if(stat(filepath, &rec) != -1){
	        show_stat_info(entity->d_name, &rec); 
	    }
    } 
}

int main(int argc, char** argv){
    if(argc < 2){
	    do_ls(".");  
        return 0;  
    }
    
    do_ls(argv[1]);
    return 0;  
}
