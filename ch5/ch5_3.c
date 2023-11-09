#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <stdio.h>

typedef enum{
    IPC_METHOD_MSG_PIPE,
    IPC_METHOD_MSG_FIFO,
    IPC_METHOD_MSG_SOCKET,
    IPC_METHOD_MSG_SYS_V_MQ,
    IPC_METHOD_MSG_POSIX_MQ,
    IPC_METHOD_MSG_SIGNAL,
    IPC_METHOD_SHM_SYS_V,
    IPC_METHOD_SHM_POSIX,
    IPC_METHOD_SHM_MMAP,
} IPC_METHOD_T;

int 
wait_child_process(IPC_METHOD_T ipc_method)
{
    switch(ipc_method)
    {
        
    }
    
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