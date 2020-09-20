#include <stdio.h>
#include <stdlib.h>

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
      f = fopen(argv[i], "r");
      if (!f) {
        perror(argv[i]);
        exit(1);
      }

      while ((c = fgetc(f)) != EOF) {
        switch (c) {
        case '\t':
          if (fputs("\\t", stdout) == EOF)
            exit(1);
          break;
        case '\n':
          if (fputs("$\n", stdout) == EOF)
            exit(1);
          break;
        default:
          if (putchar(c) == EOF)
            exit(1);
        }
      }
      fclose(f);
    }
  }
  exit(0);
}
