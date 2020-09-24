#include <stdio.h>
#include <stdlib.h>
#include <error.h>
#include <sys/stat.h>

void do_mkdir(char* path, mode_t mode);

int main(int argc, char* argv[]) {
  if (argc < 2) {
    fprintf(stderr, "%s: no arguments\n", argv[0]);
  }

  for (int i = 1; i < argc; i++) {
    do_mkdir(argv[i], 0777);
  }

}

void do_mkdir(char* path, mode_t mode) {
  if (mkdir(path, mode) == -1) {
    perror(path);
    exit(1);
  }
}

