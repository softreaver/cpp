#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <wait.h>

int ls();
int grep();
int wc();

int (*fns[3])() = {ls, grep, wc};
const int n_buff = 1000;

int main() {
    int fds[2], pid, pid2;
    pipe(fds);
    dup2(fds[0], STDIN_FILENO);

    for (int i = 0; i < 3; ++i) {
        pid = fork();
        if (pid < 0) {
            exit (EXIT_FAILURE);
        } else if (pid == 0) {
            dup2(fds[0], STDIN_FILENO);
            dup2(fds[1], STDOUT_FILENO);
        }
    }

    for (int i = 0; i < 3; ++i) {
        fns[i]();
        wait(NULL);
    }

    char buff[n_buff];
    int n = read(fds[0], buff, n_buff - 1);
    buff[n] = '\0';
    printf("%s\n", buff);

    return EXIT_FAILURE;
}

int ls() {
    char statement[25];
    strcpy(statement, "ls -l");
    if (system(statement) > 0) {
        exit(EXIT_FAILURE);
    }

    return EXIT_SUCCESS;
}

int grep() {
    char* in;
    scanf("%s", in);
    char statement[25];
    strcpy(statement, "grep . ");
    strcat(statement, in);
    if (system(statement) > 0) {
        exit(EXIT_FAILURE);
    }

    return EXIT_SUCCESS;
}

int wc() {
    char* in;
    scanf("%s", in);
    char statement[25];
    strcpy(statement, "wc -l ");
    strcat(statement, in);
    if (system(statement) > 0) {
        exit(EXIT_FAILURE);
    }

    return EXIT_SUCCESS;
}
