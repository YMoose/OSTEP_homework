#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

#include "ch5_3.h"

/* IPC_METHOD_PIPE */
static inline int *
prepare_for_pipe ()
{
  int *pipe_fd = malloc (sizeof (int) << 1);
  int flags;
  if (pipe (pipe_fd) < 0)
    {
      return NULL;
    }
  flags = fcntl(pipe_fd[0], F_GETFL, 0);
  flags |= O_NONBLOCK;
  fcntl (pipe_fd[0], F_SETFL, flags);
  return pipe_fd;
}

static inline void
wait_implement_by_pipe (void *pipe_fd)
{
  char single_c[1];
  int x = 1;
  
  close (((int *)pipe_fd)[1]);
  while (x)
    {
      x = read (((int *)pipe_fd)[0], single_c, 1);
    //   if (x == -1)
    //     perror ("read error");
    }
  close(((int *)pipe_fd)[0]);
}

static inline void
child_end_implement_by_pipe (void *pipe_fd)
{
  close (((int *)pipe_fd)[1]);
}

/* IPC_METHOD_FIFO */
static inline int *
prepare_for_fifo ()
{
  int *pipe_fd = malloc (sizeof (int) << 1);
  int flags;
  if (pipe (pipe_fd) < 0)
    {
      return NULL;
    }
  flags = fcntl(pipe_fd[0], F_GETFL, 0);
  flags |= O_NONBLOCK;
  fcntl (pipe_fd[0], F_SETFL, flags);
  return pipe_fd;
}

static inline void
wait_implement_by_fifo (void *pipe_fd)
{
  char single_c[1];
  int x = 1;
  
  close (((int *)pipe_fd)[1]);
  while (x)
    {
      x = read (((int *)pipe_fd)[0], single_c, 1);
    //   if (x == -1)
    //     perror ("read error");
    }
  close(((int *)pipe_fd)[0]);
}

static inline void
child_end_implement_by_fifo (void *pipe_fd)
{
  close (((int *)pipe_fd)[1]);
}

const wait_method_t method_list[IPC_METHOD_MAX] = {
    [IPC_METHOD_PIPE] = {
        .prepare_for_wait_func = prepare_for_pipe,
        .wait_child_func = wait_implement_by_pipe,
        .child_end_func = child_end_implement_by_pipe,
    },
    [IPC_METHOD_FIFO] = {
        .prepare_for_wait_func = prepare_for_fifo,
        .wait_child_func = wait_implement_by_fifo,
        .child_end_func = child_end_implement_by_fifo,
    },


};

int
main (int argc, char *argv[])
{
  int x = 100;
  int rc = 0;
  IPC_METHOD_T method = IPC_METHOD_PIPE;
  void *wait_ctx = prepare_for_wait (method);
  if (rc = fork ())
    {
      printf ("in parent process\n");
      wait_child_process (method, wait_ctx);
      printf ("goodbye\n");
      free (wait_ctx);
    }
  else
    {
      printf ("in child process\n");
      printf ("hello\n");
      child_end (method, wait_ctx);
      free (wait_ctx);
    }
  return 0;
}