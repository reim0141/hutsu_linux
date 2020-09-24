#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <regex.h>
#include <getopt.h>

struct option longopts[] = {
  {"invert-match", no_argument, NULL, 'v'},
  {"ignore-case", no_argument, NULL, 'i'},
  {"help", no_argument, NULL, 'h'},
  {0, 0, 0, 0}
};

int opt_invert;
int opt_ignorecase; 

void do_grep(regex_t* pat, FILE* f);

int main(int argc, char* argv[]) {
  regex_t pat;
  int err;
  int i;
  int opt;
  
  if (argc < 2){
    exit(1);
  }
  while ((opt = getopt_long(argc, argv, "iv", longopts, NULL)) != -1) {
    switch (opt) {
    case 'i':
      opt_ignorecase = 1;
      break;
    case 'v':
      opt_invert = 1;
      break;
    case 'h':
      fprintf(stdout, "Usage: %s [OPTION]... PATTERNS [FILE]...\n", argv[0]);
      exit(0);
    case '?':
      fprintf(stderr, "Usage: %s [OPTION]... PATTERNS [FILE]...\n", argv[0]);
      exit(1);
    }
  }
  if (opt_ignorecase) {
    err = regcomp(&pat, argv[optind++], REG_EXTENDED | REG_NOSUB | REG_NEWLINE | REG_ICASE);
  }
  else {
    err = regcomp(&pat, argv[optind++], REG_EXTENDED | REG_NOSUB | REG_NEWLINE);
  }

  if (err != 0) {
    char buf[1024];

    regerror(err, &pat, buf, sizeof(buf));
    puts(buf);
    exit(1);
  }
  if (argc == 2) {
    do_grep(&pat, stdin);
  }
  else {
    for (int i = optind; i < argc; i++) {
      FILE *f;

      f = fopen(argv[i], "r");
      if (!f) {
        perror(argv[i]);
        exit(1);
      }
      do_grep(&pat, f);
      fclose(f);
    }
  }
  regfree(&pat);
  exit(0);
}

void do_grep(regex_t* pat, FILE* f) {
  char buf[4096];
  if (opt_invert) {
    while (fgets(buf, sizeof(buf), f)) {
      if (regexec(pat, buf, 0, NULL, 0) != 0) {
        fputs(buf, stdout);
      }
    }
  }   
  while (fgets(buf, sizeof(buf), f)) {
    if (regexec(pat, buf, 0, NULL, 0) == 0) {
      fputs(buf, stdout);
    }
  }
}
