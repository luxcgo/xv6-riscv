#include "kernel/types.h"
#include "user/user.h"

int prime_filter(int in, int prime) 
{
  int num;
  int fds[2];
  pipe(fds);
  if (fork() == 0) {
    while (read(in, &num, sizeof(int)) > 0) {
      if (num%prime != 0)
        write(fds[1], &num, sizeof(int));
    }
    close(in);
    close(fds[1]);
    exit(0);
  } 
  close(in);
  close(fds[1]);
  return fds[0];
}

int
main(int argc, char *argv[])
{
  int num, fd;
  int fds[2];
  pipe(fds);
  if (fork() == 0) {
    for (int i = 2; i <= 35; i++) {
      write(fds[1], &i, sizeof(int));
    }
    close(fds[1]);
  } else {
    close(fds[1]);
    fd = fds[0];
    while (read(fd, &num, sizeof(int)) > 0) {
      printf("prime %d\n", num);
      fd = prime_filter(fd, num);
    }
    close(fd);
  }
  exit(0);
}