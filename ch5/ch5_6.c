#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>
/*
 * waitpid的参数pid具有以下几种可能
 * pid == -1 等待任一子进程
 * pid > 0   等待进程ID为pid的子进程
 * pid == 0  等待进程组ID相同的任一子进程
 * pid < -1  等待进程组ID为pid绝对值的任一子进程
 * waitpid的options参数可以是以下几个选项用 | 组合
 * WCONTINUED
 * WNOHANG 不阻塞
 * WUNTRACED
 */
int
main (int argc, char *argv[])
{
  int x = 100;
  int rc = 0;
  if (rc = fork ())
    {
      x = waitpid (rc, NULL, WNOHANG);
      printf ("x is %d in parent process\n", x);
    }
  else
    {
      printf ("x is %d in child process\n", x);
      printf ("changing x to 25\n");
      x = 25;
      printf ("x is %d in child process\n", x);
    }
  return 0;
}