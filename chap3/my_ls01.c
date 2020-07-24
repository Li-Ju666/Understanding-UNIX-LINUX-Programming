/* my_ls01.c - function to list all files in given directory */
#include <stdio.h>
#include <dirent.h>

void do_ls(char* dir_name){
    DIR* cur_dir = opendir(dir_name); 
    if(cur_dir == NULL){
	    perror("Error: "); 
	    return; 
    }
    struct dirent* entity; 
    while((entity = readdir(cur_dir)) != NULL){
	    printf("%s\n", entity->d_name); 	
    } 
}

int main(int argc, char** argv){
    if(argc < 2){
	    printf("Usage: my_ls directory_to_be_explored \n"); 
	    return 0;  
    }
    
    do_ls(argv[1]);
    return 0;  
}
