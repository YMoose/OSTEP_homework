#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

int
main (int argc, char *argv[])
{
  int pipe_fd[2];
  int x = 100;
  int rc = 0;

  if (pipe (pipe_fd) < 0)
    {
      return NULL;
    }

  if (rc = fork ())
    {
      if (rc = fork ())
        {
          return 0;
        }
      else
        {
          printf ("this is child output\n");
          close (pipe_fd[0]);
          if (dup2 (pipe_fd[1], STDOUT_FILENO) != STDOUT_FILENO)
            {
              perror ("dup2 err");
              close (pipe_fd[1]);
            }
          printf ("123\n");
        }
    }
  else
    {
      sleep (1);
      printf ("this is child input\n");
      close (pipe_fd[1]);
      if (dup2 (pipe_fd[0], STDIN_FILENO) != STDIN_FILENO)
        {
          perror ("dup2 err");
          close (pipe_fd[0]);
        }
      int d;
      printf ("start scanf\n");
      scanf ("%d", &d);
      printf ("%d\n", d);
    }
  return 0;
}