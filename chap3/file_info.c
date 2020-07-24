#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <time.h>
#include <stdlib.h>
#include <pwd.h>
#include <grp.h>
int stat(const char *pathname, struct stat *statbuf);

char* mode_to_letter(int mode)
{
    char* result = malloc(11); 
    strcpy(result, "----------");
    
    if (S_ISDIR(mode))  result[0] = 'd'; 
    if (S_ISCHR(mode))  result[0] = 'c'; 
    if (S_ISBLK(mode))  result[0] = 'b'; 

    if (mode & S_IRUSR) result[1] = 'r'; 
    if (mode & S_IWUSR) result[2] = 'w'; 
    if (mode & S_IXUSR) result[3] = 'x'; 

    if (mode & S_IRGRP) result[4] = 'r'; 
    if (mode & S_IWGRP) result[5] = 'w'; 
    if (mode & S_IXGRP) result[6] = 'x'; 

    if (mode & S_IROTH) result[7] = 'r'; 
    if (mode & S_IWOTH) result[8] = 'w'; 
    if (mode & S_IXOTH) result[9] = 'x'; 

    return result; 

}

char* uid_to_name(uid_t uid)
{
    return getpwuid(uid)->pw_name; 
}

char* gid_to_name(gid_t gid)
{
    return getgrgid(gid)->gr_name;  
}

void show_stat_info(const char* fname, struct stat* rec){
    printf("%s ", mode_to_letter(rec->st_mode)); 
    printf("%4ld ", rec->st_nlink); 
    printf("%-8s ", uid_to_name(rec->st_uid)); 
    printf("%-8s ", gid_to_name(rec->st_gid)); 
    printf("%8ld ", rec->st_size);
    printf("%.12s ", 4+ctime(&(rec->st_mtime))); 
    printf("%s\n", fname); 
}

/* int main(int argc, char** argv){ */
/*     struct stat rec; */ 
/*     if(argc > 1){ */
/* 	    if(stat(argv[1], &rec) != -1){ */
/* 	        show_stat_info(argv[1], &rec); */ 
/* 	    } */
/* 	    return 0; */  
/*     } */
/*     else{ */
/* 	    perror(argv[1]); */
/* 	    return -1; */ 
/*     } */
/* } */
