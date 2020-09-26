#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <error.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <regex.h>
#include <errno.h>

regex_t preg;
char* pattern = "^(.*/)?";

void do_mkdir(char* path, mode_t mode);
void do_mkdir_p(char* path, mode_t mode);

int main(int argc, char* argv[]) {
  if (argc < 2) {
    fprintf(stderr, "%s: no arguments\n", argv[0]);
  }
  int opt = getopt(argc, argv, "p");
  int p_flag = 0;
  
  if (opt == 'p') {
    int rc;
    if ( 0 != (rc = regcomp(&preg, pattern, REG_EXTENDED | REG_NEWLINE))) {
      printf("regcomp() failed, returning nonzero (%d)¥n", rc);
      exit(EXIT_FAILURE); 
    }
    p_flag = 1;
  }
  for (int i = optind; i < argc; i++) {
    if (p_flag > 0) {
      printf("running: mkdir -p %s\n",argv[i]);
      int j;
      for(j = 0;; j++) {
        if (argv[i][j] == '\0')
          break;
      }
      if ((argv[i][j - 1]) == '/') {
        argv[i][j - 1] = '\0';
      }
      do_mkdir_p(argv[i], 0777);
    }
    else {
      do_mkdir(argv[i], 0777);
    }
  }
}

void do_mkdir(char* path, mode_t mode) {
  if (mkdir(path, mode) == -1) {
    perror(path);
    exit(1);
  }
}

void do_mkdir_p(char* path, mode_t mode) {
  if (mkdir(path, mode) == -1) {
    if (errno == ENOENT) {
      regmatch_t pmatch[1];
      char *buf = strdup(path);
      if (!buf) {
        printf("Couldn't allocate memory.\n");
        exit(1);
      }
      if ( 0 == regexec(&preg, buf, 1, pmatch, 0)) {
        int len = pmatch->rm_eo - pmatch->rm_so - 1;
        if (len < 1) {
          printf("wrong directory name\n");
          exit(1);
        }
        char* str = strndup(buf, len);
        do_mkdir_p(str, mode);
        free(str);
      }
      else {
        printf("error nari\n");
        exit(1);
      }
      do_mkdir(path, mode);
      free(buf);
    }
    else {
      perror(path);
      exit(1);
    }
  }
  printf("%s created\n", path);
}

