#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <error.h>
#include <errno.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char* argv[]) {
   u_int8_t buf[4096];
   ssize_t nread;
   int fd = STDIN_FILENO;
   if (argc == 1) {      
      while ((nread = read(fd, buf, sizeof(buf))) > 0)
         write(1, buf, nread);
   }
   if (argc > 1){
      for (int i = 1; i < argc; i++) {
         fd = open(argv[i], O_RDONLY);
         if (fd < 0) {
            fprintf(stderr, "cannot open %s: %s\n", argv[1], strerror(errno));
         }
         while ((nread = read(fd, buf, sizeof(buf))) > 0) {
            write(1, buf, nread);
         }
      }
   }
      return 0;
}
