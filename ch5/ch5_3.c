#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <stdio.h>

int 
wait_child_process()
{
    
}

int
main (int argc, char *argv[])
{
    int x = 100;
    int rc = 0;
    if (rc = fork())
    {
        printf("in parent process\n");
        wait_child_process();
        printf("goodbye\n");
    }
    else
    {
        printf("in child process\n");
        printf("hello\n");
    }
    return 0;
}