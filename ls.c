#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <dirent.h>

void do_ls(DIR* d);

int main(int argc, char* argv[]) {

  if (argc < 2) {
    fprintf(stderr, "%s: no arguments\n", argv[0]);
    exit(1);
  }
  for (int i = 1; i < argc; i++) {
    DIR* d = opendir(argv[i]);
    if (!d) {
      perror(argv[i]);
      exit(1);
    }
    do_ls(d);
    closedir(d);
  }
}

void do_ls(DIR* d) {
  struct dirent *ent;
  while (ent = readdir(d)) {
    printf("%s\n", ent->d_name);
  }
}
