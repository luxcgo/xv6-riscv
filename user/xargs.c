#include "kernel/types.h"
#include "user/user.h"
#include "kernel/param.h"

int
main(int argc, char *argv[])
{
  if (argc < 2) {
    fprintf(2, "usage: xargs <command> [argv...]\n");
    exit(1);
  }
  if (argc + 1 > MAXARG) {
    fprintf(2, "Too many args\n");
    exit(1);
  }
  char *cmd[MAXARG], buf[512];
  char *p = buf;
  for (int i = 0; i < argc; i++) {
    cmd[i] = argv[i+1];
  }
  cmd[argc] = 0;
  int i = 0;
  while (read(0, &buf[i], 1) > 0) {
    if (buf[i] == '\n') {
      printf("hh\n");
      buf[i] = 0;
      cmd[argc - 1] = p;
      p = buf + i + 1;
      if (fork() == 0) {
        exit(exec(cmd[0], cmd));
      } else {
        wait(0);
      }
    }
    i++;
  }
  exit(0);
}