#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

void die(const char *s) {
  perror(s);
  exit(1);
}

int main(int argc, char* argv[]) {
  if (argc == 1) {
    fprintf(stderr, "%s: file name not given\n",argv[0]);
    exit(1);
  }
  if (argc > 1) {
    for (int i = 1; i < argc; i++) {
      FILE* f = fopen(argv[i], "r");
      ssize_t nread;
      char buf[4096] = {};
      if (!f) {
        die(argv[i]);
      }
      int count = 0;
      int c;
      while ((c = fgetc(f)) != EOF) {
        if (c == '\n') {
          count += 1;
        }
      }
      printf("%d\n", count);
      fclose(f);
    }
  }
}
