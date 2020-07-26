/* write0.c */

/* purpose: send message to another termimal */
/* method: open another terminal file and copy from stdin */
/*     to the terminal file */
/* usage: write0 ttyname */
#include <stdio.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char** argv)
{
    int fd; 
    char buf[BUFSIZ]; 
    if (argc != 2)
    {
        fprintf(stderr, "usage: write0 ttyname\n"); 
        return -1; 
    }

    fd = open(argv[1], O_WRONLY); 
    if (fd == -1)
    {
        perror(argv[1]); 
        return -1; 
    }

    while (fgets(buf, BUFSIZ, stdin) != NULL)
    {
        if (write(fd, buf, strlen(buf)) == -1)
        {
            break; 
        }
    }
    close(fd); 
}
