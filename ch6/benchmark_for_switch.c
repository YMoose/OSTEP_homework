#define _GNU_SOURCE /* cannot user CPU_SET API without it */
#include <sched.h>
#include <stdio.h>
#include <sys/time.h>
#include <time.h>
#include <unistd.h>

/* copy from vpp */
/* Return CPU time stamp as 64bit number. */
#if defined(__x86_64__) || defined(i386)
static inline unsigned long long
clib_cpu_time_now (void)
{
  unsigned int a, d;
  asm volatile ("rdtsc" : "=a"(a), "=d"(d));
  return (unsigned long long)a
         + ((unsigned long long)d << (unsigned long long)32);
}
#elif defined(__riscv)

static inline unsigned long long
clib_cpu_time_now (void)
{
  unsigned long long result;
  asm volatile ("rdcycle %0\n" : "=r"(result));
  return result;
}
#endif

/* lmbench solution */
int
switch_bench_prepare (int *pipe_fd0, int *pipe_fd1)
{
  pipe (pipe_fd0);
  pipe (pipe_fd1);
  int ret = 0;
  if (ret = fork ())
    {
      close (pipe_fd0[0]);
      close (pipe_fd1[1]);
    }
  else
    {
      close (pipe_fd0[1]);
      close (pipe_fd1[0]);
    }

  return ret;
}

static inline void
switch_bench (int read_fd, int write_fd)
{
  int i = 0;
  char buf[1] = { "t" };
  write (write_fd, buf, 1);
  for (; i < 200000; i++)
    {
      read (read_fd, buf, 1);
      write (write_fd, buf, 1);
    }
  return;
}

int
main (int argc, char *argv[])
{
  int pipe_fd0[2];
  int pipe_fd1[2];
  struct timeval start_tv, end_tv;
  struct timespec start_ts, end_ts;
  unsigned long long start_cycle, end_cycle;

  cpu_set_t cpuset;
  CPU_ZERO (&cpuset);   // 清空CPU集合
  CPU_SET (0, &cpuset); // 将CPU 0添加到集合中

  if (sched_setaffinity (0, sizeof (cpu_set_t), &cpuset) == -1)
    {
      perror ("sched_setaffinity");
      return 1;
    }

  if (!switch_bench_prepare (pipe_fd0, pipe_fd1))
    {
      /* child process */
      switch_bench (pipe_fd0[0], pipe_fd1[0]);
      return 0;
    }

  gettimeofday (&start_tv, NULL);
  clock_gettime (CLOCK_REALTIME, &start_ts);
  start_cycle = clib_cpu_time_now ();

  /* parent process */
  switch_bench (pipe_fd0[1], pipe_fd1[0]);

  end_cycle = clib_cpu_time_now ();
  clock_gettime (CLOCK_REALTIME, &end_ts);
  gettimeofday (&end_tv, NULL);

  end_tv.tv_sec = start_tv.tv_usec < end_tv.tv_usec
                      ? end_tv.tv_sec - start_tv.tv_sec
                      : end_tv.tv_sec - start_tv.tv_sec - 1;
  end_tv.tv_usec = end_tv.tv_usec - start_tv.tv_usec;
  printf ("interval is %llu second %llu usecond\n", end_tv.tv_sec,
          end_tv.tv_usec);

  end_ts.tv_sec = start_ts.tv_nsec < end_ts.tv_nsec
                      ? end_ts.tv_sec - start_ts.tv_sec
                      : end_ts.tv_sec - start_ts.tv_sec - 1;
  end_ts.tv_nsec = end_ts.tv_nsec - start_ts.tv_nsec;
  printf ("interval is %llu second %llu nanosecond\n", end_ts.tv_sec,
          end_ts.tv_nsec);

  printf ("interval is %llu cycles\n", end_cycle - start_cycle);
  return 0;
}