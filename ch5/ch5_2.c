#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <stdio.h>

int
main (int argc, char *argv[])
{
    int fd = open("test.txt", O_WRONLY | O_CREAT, 0644);
    if (fd == -1)
        return 0;
    int rc = 0;
    if (rc = fork())
    {
        printf("fd is %d in parent process\n", fd);
        write(fd, "it is parent\n", 13);
    }
    else
    {
        printf("fd is %d in child process\n", fd);
        write(fd, "it is child\n", 12);
    }
    return 0;
}