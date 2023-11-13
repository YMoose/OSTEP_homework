#include <stdio.h>

int 
main (int argc, char* argv[])
{
    int rc = fork();
    if (rc < 0)
    {
        perror("fork error");
    }

    if (rc == 0)
    {
        return 0;
    }
    else 
    {
        argv[0] = strdup("/bin/ls");
        execvp(argv[0], argv);
    }
    return 0;
}