#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>
/*
 * 当你尝试向已关闭的文件描述符写入字符时，通常会导致一个错误。具体表现取决于你是如何尝试写入的。
 *
 * 使用write系统调用：如果你使用write系统调用向已关闭的文件描述符写入字符，该系统调用将返回-1，
 * 并设置全局变量errno为EBADF（表示无效的文件描述符）。
 * 这样你就可以通过检查errno来了解发生了什么错误。
 *
 * 使用标准输出函数：如果你使用像printf这样的标准输出函数向已关闭的文件描述符写入字符，程序可能会产生未定义的行为。
 * 这是因为标准输出函数内部并不一定会检查文件描述符的有效性，而是假定文件描述符是有效的。
 * 因此，这样的操作可能导致程序崩溃或其他意外行为。
 *
 * 综上所述，向已关闭的文件描述符写入字符通常会导致错误发生，并可能产生不确定的行为。
 * 在编程时，建议在写入前先检查文件描述符的状态，避免向已关闭的文件描述符进行写操作。
 */
int
main (int argc, char *argv[])
{
  int x = 100;
  int rc = 0;
  if (rc = fork ())
    {
      printf ("x is %d in parent process\n", x);
      printf ("changing x to 50\n");
      x = 50;
      printf ("x is %d in parent process\n", x);
    }
  else
    {
      close (STDOUT_FILENO);
      printf ("x is %d in child process\n", x);
      printf ("changing x to 25\n");
      x = 25;
      printf ("x is %d in child process\n", x);
    }
  return 0;
}