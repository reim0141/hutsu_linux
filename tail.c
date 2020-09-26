#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#define MAX_LINE_LENGTH 1024
#define N_LINES 10

struct option longopts[] = {
  {"lines", required_argument, NULL, 'n'},
  {"help", no_argument, NULL, 'h'},
  {0, 0, 0, 0}
};

int main(int argc, char* argv[]) {
  if (argc < 2) {
    exit(1);
  }
  int nlines = N_LINES;
  int opt;
  while ((opt = getopt_long(argc, argv, "n:", longopts, NULL)) != -1) {
    switch (opt) {
    case 'n':
      nlines = atoi(optarg);
      break;
    case 'h':
      fprintf(stdout, "Usage: %s [OPTION]... [FILE]...\n", argv[0]);
      exit(0);
    case '?':
      fprintf(stderr, "Usage: %s [OPTION]... [FILE]...\n", argv[0]);
      exit(1);
    }
  }

  char **buf;
  buf = (char **)malloc(sizeof(char *) * nlines);
  for (int i = 0; i < nlines; i++)
    buf[i] = (char *)malloc(MAX_LINE_LENGTH * sizeof(char));
  int first = 1;
  //printf("allocated\n");
  //printf("optind: %d\n", optind);
  for (int i = optind; i < argc; i++)  {
    printf("%s%s\n",(first++ == 1) ? "" : "\n" , argv[i]);
    FILE *f;

    f = fopen(argv[i], "r");
    if (!f) 
      exit(1);
    
    int cur = 0;
    int n_read_lines = 0;
    while (fgets(buf[cur], MAX_LINE_LENGTH, f)) {
      cur = ++cur % nlines;
      n_read_lines++;
    }
    fclose(f);
    if (n_read_lines < nlines) {
      cur = 0;
    }
    
    for (int i = 0; i < nlines && n_read_lines; i++, n_read_lines--) {
      printf("%s", buf[cur]);
      cur = ++cur % nlines;
    }
  }
  for (int i = 0; i < nlines; i++)
    free(buf[i]);
  free(buf);
  exit(0);
}
