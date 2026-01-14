#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/wait.h>

typedef struct ThreadState {
    int id;
    int value;
} ThreadState;

// Simulate Python's _PyThreadState_Current using TLS
__thread ThreadState *thread_state = NULL;

// Constructor to initialize main thread state
__attribute__((constructor))
static void init_main_thread_state(void) {
    thread_state = malloc(sizeof(ThreadState));
    thread_state->id = 1;
    thread_state->value = 42;
    printf("Constructor: main thread_state->value=%d\n", thread_state->value);
}

void *thread_func(void *arg) {
    // Each thread must initialize its own thread_state
    thread_state = malloc(sizeof(ThreadState));
    thread_state->id = 2;
    thread_state->value = 100;
    printf("Thread: id=%d, value=%d\n", thread_state->id, thread_state->value);
    thread_state->value += 7;
    printf("Thread after update: id=%d, value=%d\n", thread_state->id, thread_state->value);
    return NULL;
}

int main(void) {
    printf("Main before fork: id=%d, value=%d\n", thread_state->id, thread_state->value);

    // Launch a thread
    pthread_t th;
    if (pthread_create(&th, NULL, thread_func, NULL)) {
        perror("pthread_create");
        exit(1);
    }
    pthread_join(th, NULL);

    printf("Main after thread: id=%d, value=%d\n", thread_state->id, thread_state->value);

    // Fork child process
    pid_t pid = fork();
    if (pid < 0) {
        perror("fork");
        exit(1);
    } else if (pid == 0) {
        // Child process
        printf("Child process before change: id=%d, value=%d\n", thread_state->id, thread_state->value);
        thread_state->value += 1000;
        printf("Child process after change: id=%d, value=%d\n", thread_state->id, thread_state->value);
        exit(0);
    } else {
        // Parent process
        int status;
        waitpid(pid, &status, 0);
        printf("Parent after child: id=%d, value=%d\n", thread_state->id, thread_state->value);
    }

    free(thread_state);
    return 0;
}
