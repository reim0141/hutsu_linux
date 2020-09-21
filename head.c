#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>

#define DEFAULT_N_LINES 10

struct option longopts[] = {
  {"lines", required_argument, NULL, 'n'},
  {"help", no_argument, NULL, 'h'},
  {0, 0, 0, 0}
};

void die(const char *s) {
  perror(s);
  exit(1);
}

void do_head(FILE *f, int nlines) {
  int c;
  while((nlines != 0) && ((c = fgetc(f)) != EOF)) {
    if (c == '\n') {
      nlines -= 1;
    }
    if (putchar(c) == EOF)
      exit(1);
  }
}

int main(int argc, char* argv[]) {
  int opt;
  int nlines = DEFAULT_N_LINES;
  while ((opt = getopt_long(argc, argv, "n:", longopts, NULL)) != -1) {
    switch (opt) {
    case 'n':
      nlines = atoi(optarg);
      break;
    case 'h':
      fprintf(stdout, "Usage: %s [-n LINES] [FILE ...]\n", argv[0]);
      exit(0);
    case '?':
      fprintf(stderr, "Usage: %s [-n LINES] [FILE ...]\n", argv[0]);
      exit(1);
    }
  }
  if (optind == argc){
    do_head(stdin, nlines);
  }
  else {
    for (int i = optind; i < argc; i++) {
      FILE* f = fopen(argv[i], "r");
      if (!f) {
        die(argv[i]);
      }
      do_head(f, nlines);
      fclose(f);
    }
  }
}
