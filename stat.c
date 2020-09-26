#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <time.h>

char* filetype(mode_t mode);

int main(int argc, char* argv[]) {
  if (argc < 2) {
    fprintf(stderr, "%s: no arguments\n", argv[1]);
    exit(1);
  }
  else {
    int first = 1;
    for (int i = 1; i < argc; i++) {
      printf("%s", (first++ == 1) ? "" : "\n");
      struct stat st[1];
      if (stat(argv[i], st) < 0) {
        perror(argv[i]);
        exit(1);
      }
      printf("File\t%s\n", argv[i]);
      printf("type\t%o (%s)\n", (st->st_mode & S_IFMT), filetype(st->st_mode));
      printf("mode\t%o\n", st->st_mode & ~S_IFMT);
      printf("dev\t%llu\n", (unsigned long long)st->st_dev);
      printf("ino\t%lu\n", (unsigned long)st->st_ino);
      printf("rdev\t%llu\n", (unsigned long long)st->st_rdev);
      printf("nlink\t%lu\n", (unsigned long)st->st_nlink);
      printf("uid\t%d\n", st->st_uid);
      printf("gid\t%d\n", st->st_gid);
      printf("size\t%ld\n", st->st_size);
      printf("blksize\t%lu\n", (unsigned long)st->st_blksize);
      printf("blocks\t%lu\n", (unsigned long)st->st_blocks);
      printf("atime\t%s", ctime(&st->st_atime));
      printf("mtime\t%s", ctime(&st->st_mtime));
      printf("ctime\t%s", ctime(&st->st_ctime));
    }
  }
}

char* filetype(mode_t mode) {
  if(S_ISREG(mode)) return "file";
  if(S_ISDIR(mode)) return "directory";
  if(S_ISCHR(mode)) return "chardev";
  if(S_ISBLK(mode)) return "blockdev";
  if(S_ISFIFO(mode)) return "fifo";
  if(S_ISLNK(mode)) return "symlink";
  if(S_ISSOCK(mode)) return "socket";
}
