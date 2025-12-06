#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int global_var = 42;

int main() {
    printf("Parent PID: %d, global_var=%d\n", getpid(), global_var);

    pid_t pid = fork();

    if (pid < 0) {
        perror("fork failed");
        return 1;
    }

    if (pid == 0) {
        // Child process
        global_var += 100;
        printf("Child PID: %d, global_var=%d\n", getpid(), global_var);
        exit(0);
    } else {
        // Parent process
        wait(NULL);
        printf("Parent PID: %d after child exit, global_var=%d\n", getpid(), global_var);
    }

    return 0;
}
