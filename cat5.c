#include <stdio.h>
#include <stdlib.h>

void die(char *s) {
  perror(s);
  exit(1);
}

int main(int argc, char* argv[]) {
  if (argc == 1) {
    int c;
    while ((c = getchar()) != -1) {
      if (putchar(c) == EOF)
        exit(1);
    }
  }
  
  if (argc > 1) {
    for (int i = 1; i < argc; i++) {
      FILE *f;
      int c;
      unsigned char buf[4096] = {};
      f = fopen(argv[i], "r");
      if (!f) {
        die(argv[i]);
      }

      for (;;) {
        ssize_t nread = fread(buf, 1, sizeof(buf), f);
        if (ferror(f) != 0)
          die(argv[i]);
        ssize_t nwrite = fwrite(buf, 1, nread, stdout);
        if (nwrite < nread)
          die(argv[i]);
        if (nread < sizeof(buf))
          break;
      }
      fclose(f);
    }
  }
  exit(0);
}
