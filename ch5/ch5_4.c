#include <stdio.h>
#include <unistd.h>
/*
 * exec函数族的第二个参数的意义？
 * 为什么有这么多变体?
 *
 * 对函数参数的形式（list/vector）
 * 函数参数中是否有envp参数
 * 第一个参数是pathname还是filename
 */
int
main (int argc, char *argv[])
{
  int rc = fork ();
  if (rc < 0)
    {
      perror ("fork error");
    }

  if (rc == 0)
    {
      return 0;
    }
  else
    {
      char *my_argv[] = { "/usr/bin/echo", "\"$USER\"", NULL };
      char *env_init[] = { "USER=unknow", "PATH=/tmp", NULL };
      execv (my_argv[0], my_argv);
      //   execvp (my_argv[0], my_argv);
      //   execve (my_argv[0], my_argv, env_init);
      //   execl (my_argv[0], my_argv, 0);
      //   execlp (my_argv[0], my_argv, 0);
      //   execle (my_argv[0], my_argv[0], my_argv[1], 0, env_init);
    }
  return 0;
}