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
      u_int8_t buf[4096];
      int fd = open(argv[i], O_RDONLY);
      ssize_t nread;
      if (fd < 0) {
        die(argv[i]);
      }
      int count = 0;
      while ((nread = read(fd, buf, sizeof(buf))) > 0) {
        for (int j = 0; j < nread; j++) {
          if (buf[j] == '\n') {
            count += 1;
          } 
        }
      }
      char str[10] = {};
      //itoa(count, str, 10);
      sprintf(str, "%d", count);
      for (int i = 0; i < 10; i++) {
        printf("%d:%d\n",i,str[i]);
      }
      printf("\n");
      printf("%s\n",str);
      write(1, str, sizeof(str));
      char enter[1] = {'\n'};
      write(1, enter, 1);
    }
  }
}


