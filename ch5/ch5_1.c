#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <stdio.h>

int
main (int argc, char *argv[])
{
    int x = 100;
    int rc = 0;
    if (rc = fork())
    {
        printf("x is %d in parent process\n", x);
        printf("changing x to 50\n");
        x = 50;
        printf("x is %d in parent process\n", x);
    }
    else
    {
        printf("x is %d in child process\n", x);
        printf("changing x to 25\n");
        x = 25;
        printf("x is %d in child process\n", x);
    }
    return 0;
}