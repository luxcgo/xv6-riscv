#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int
main(int argc, char *argv[])
{
  if(argc < 2){
    fprintf(2, "Error: please specify the number of ticks.\n");
    exit(1);
  }

  int tick;
  tick = atoi(argv[1]);
  exit(sleep(tick));
}
