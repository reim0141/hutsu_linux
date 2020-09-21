#include <stdio.h>
#include <stdlib.h>

#define MAX_LINE_LENGTH 1024
#define N_LINES 10

int main(int argc, char* argv[]) {
  char *buf[N_LINES];
  for (int i = 0; i < N_LINES; i++)
    buf[i] = (char *)calloc(MAX_LINE_LENGTH, sizeof(char));

  FILE *f;

  f = fopen(argv[1], "r");
  if (!f) 
    exit(1);
  
  int cur = 0;
  int n_read_lines = 0;
  while (fgets(buf[cur], MAX_LINE_LENGTH, f)) {
    cur = ++cur % N_LINES;
    n_read_lines++;
  }
  fclose(f);
  if (n_read_lines < N_LINES) {
    cur = 0;
  }
  
  for (int i = 0; i < N_LINES && n_read_lines; i++, n_read_lines--) {
    printf("%s", buf[cur]);
    cur = ++cur % N_LINES;
  }

}
