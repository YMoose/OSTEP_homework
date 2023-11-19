#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>
/*
 * wait 在父进程中返回的是终止子进程的pid
 * wait在子进程中使用直接返回
 * 因为fork时在内核会调用
 * add_wait_queue(&current->signal->wait_chldexit, &wo->child_wait)
 * 往内核进程数据结构task_struct加入子进程信息
 * wait调用的参数statloc如果不是一个空指针，wait调用会将终止进程的终止状态存入其内存，其由实现定义，每一位有不同含义
 * 可以在<sys/wait.h>中查看WIFXXX的宏
 */
int
main (int argc, char *argv[])
{
  int x = 100;
  int rc = 0;
  if (rc = fork ())
    {
      int statloc;
      x = wait (&statloc);
      printf ("wait ret %d in parent process\n", x);
      printf ("statloc is %d\n", statloc);
    }
  else
    {
      printf ("x is %d in child process\n", x);
      printf ("changing x to 25\n");
      x = 25;
      printf ("x is %d in child process\n", x);
      exit (1);
    }
  return 0;
}