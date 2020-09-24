#include <stdio.h>
#include <stdlib.h>
#include <error.h>
#include <sys/stat.h>
#include <unistd.h>

void do_rmdir(char* path);

int main(int argc, char* argv[]) {
  if (argc < 2) {
    fprintf(stderr, "%s: no arguments\n", argv[0]);
  }

  for (int i = 1; i < argc; i++) {
    do_rmdir(argv[i]);
  }

}

void do_rmdir(char* path) {
  if (rmdir(path) == -1) {
    perror(path);
    exit(1);
  }
}

