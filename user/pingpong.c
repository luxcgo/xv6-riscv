#include "kernel/types.h"
#include "user/user.h"

int
main()
{
  int n, pid, status;
  int fds[2];
  char buf[1];
  pipe(fds);
  pid = fork();
  if (pid == 0) {
    n = read(fds[0], buf, sizeof(buf));
    if (n > 0) {
        printf("%d: received ping\n", buf[0]);
        buf[0] = pid;
        write(fds[1], buf, 1);
        exit(0);
    }
    exit(1);
  } else {
    buf[0] = pid;
    write(fds[1], buf ,1);
    wait(&status);
    read(fds[0], buf, sizeof(buf));
    printf("%d: received pong\n", getpid());
    exit(0);
  }
}
