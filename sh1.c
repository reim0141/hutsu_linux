#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <ctype.h>
#include <sys/types.h>
#include <sys/wait.h>

typedef struct cmd {
  int argc;
  char** argv;
  int capa;
} cmd;

cmd* parse_cmd(char *buf);
void invoke_cmd(cmd* cmd);
void free_cmd(cmd* cmd);
void do_sh(void);

int main(int argc, char* argv[]) {
  if (argc != 1) {
    fprintf(stderr, "Usage: %s", argv[0]);
  }
  do_sh();
}

void do_sh(void) {
  char buf[2048];
  for (;;) {
    printf("$ ");
    if (fgets(buf, sizeof(buf), stdin) == NULL)
      exit(0);
    cmd* cmd;
    //printf("run parse_cmd\n");
    cmd = parse_cmd(buf);
    //printf("parsed\n");
    if (cmd->argc > 0) {
      invoke_cmd(cmd);
    }
    free_cmd(cmd);
  }
  exit(0);
}

#define INIT_CAPA 16

cmd* parse_cmd(char* buf) {
  char *p = buf;
  cmd* cmd;
  cmd = malloc(sizeof(cmd));
  if (!cmd) {
    perror("malloc");
    exit(1);
  }
  
  cmd->argc = 0;
  cmd->argv = (char **)malloc(sizeof(char*) * INIT_CAPA);
  cmd->capa = INIT_CAPA;
  if (!cmd->argv) {
    perror("malloc");
    exit(1);
  }
  while(*p) {
    while (*p && isspace(*p)) {
      *p++ = '\0';
    }
    if (*p) {
      if (cmd->capa <= cmd->argc + 1) {
        cmd->argc *= 2;
        cmd->argv = realloc(cmd->argv, sizeof(char*) * cmd->capa);
        if (!cmd->argv) {
          perror("realloc");
          exit(1);
        }
      }
      cmd->argv[cmd->argc] = p++;
      cmd->argc++;
    }
    while (*p && !isspace(*p)) {
      p++;
    }
  }
  cmd->argv[cmd->argc] = NULL;
  return cmd;
}

void invoke_cmd(cmd* cmd) {
    pid_t pid;
    pid = fork();
    if (pid < 0) {
      fprintf(stderr, "fork(2) failed\n");
      exit(1);
    }
    if (pid == 0) { 
      execvp(cmd->argv[0], cmd->argv);
      perror(cmd->argv[0]);
      exit(1);
    }
    else {
      waitpid(pid, NULL, 0);
    }
}

void free_cmd(cmd* cmd) {
  free(cmd->argv);
  free(cmd);
}
