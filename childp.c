#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <wait.h>
#include <string.h>

#define MSG_SIZE 80

int main() {
    int fd[2];
    char in_buf[MSG_SIZE];
    char message[MSG_SIZE] = "Hello";

    printf("Original message: \"%s\"\n", message);

    if (pipe(fd) < 0) {
        fprintf(stderr, "Couldn't create pipe!");
        return 1;
    }

    pid_t pid = fork();

    if (pid == 0) {
        char *to_append = ", world!";
        close(fd[0]);
        write(fd[1], to_append, strlen(to_append) + 1);

        printf("Child: trying to send through: \"%s\"\n", to_append);
    } else if (pid > 0) {
        close(fd[1]);
        printf("Test\n");
        wait(NULL);
        printf("1\n");
        read(fd[0], in_buf, MSG_SIZE);
        printf("2\n");
        strcat(message, in_buf);
        printf("3\n");
        printf("Parent: final message: \"%s\"\n", message);
    }

    return 0;
}
