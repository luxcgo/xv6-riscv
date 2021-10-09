#include "kernel/types.h"
#include "user/user.h"

int
main()
{
  int fds[2];
  char buf[128];
  pipe(fds);
  if (!fork()) {
    read(fds[0], buf, sizeof(buf));
    close(fds[0]);
    printf("%d: received %s\n", getpid(), buf);
    write(fds[1], "pong", sizeof(buf));
    close(fds[1]);
    exit(0);
  } else {
    write(fds[1], "ping", sizeof(buf));
    close(fds[1]);
    wait(0);
    read(fds[0], buf, sizeof(buf));
    close(fds[0]);
    printf("%d: received %s\n", getpid(), buf);
    exit(0);
  }
}