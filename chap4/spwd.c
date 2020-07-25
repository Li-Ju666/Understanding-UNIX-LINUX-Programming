/* spwd.c - a simplified program to show the absolute path */
/* of current directory */
#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <dirent.h>

ino_t get_inode(char* path)
{
    struct stat current; 
    if (stat(path, &current) == 0)
    {
        return current.st_ino;     
    }
}

char* get_name(ino_t inode)
{
    DIR* dirp = opendir("."); 
    struct dirent* rec; 
    while((rec = readdir(dirp)) != NULL)
    {
        if (inode == rec->d_ino)
        {
            return rec->d_name; 
        }
    }
}

void recur_show(int depth)
{
    ino_t cur_inode = get_inode("."); 
    if (cur_inode == get_inode(".."))
    {
        /* To make sure print "/" when run at root */
        if (depth == 0)
        {
            printf("/"); 
        }
        return; 
    }
    chdir("..");
    char* cur_name = get_name(cur_inode); 
    
    recur_show(depth+1); 
    printf("/%s", cur_name);  
    return; 
}

int main()
{
    recur_show(0);
    printf("\n");  
    return 0; 
}
