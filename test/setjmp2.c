#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <setjmp.h>
#include <unistd.h>
#include <sys/wait.h>

/*
 * In PostgreSQL this is: PG_exception_stack (thread-local).
 * We simplify to a global pointer to a jmp_buf.
 */
static jmp_buf *exception_stack = NULL;

static void child_action_with_error(void) {
    printf("[child] simulating an error -> longjmp\n");
    longjmp(*exception_stack, 1);
}

int main(void) {
    jmp_buf local_env;

    /*
     * Register our jump environment exactly like PG_TRY does.
     * PG_exception_stack = &local_env;
     */
    exception_stack = &local_env;

    int jmp_rc = setjmp(local_env);
    if (jmp_rc != 0) {
        /* This is the PG_CATCH equivalent */
        printf("[parent or child] caught longjmp (rc=%d)\n", jmp_rc);
        return 0;
    }

    /* == PG_TRY block == */

    pid_t pid = fork();

    if (pid < 0) {
        perror("fork");
        exit(1);
    }

    if (pid == 0) {
        /* ---- CHILD ---- */
        printf("[child] running inside forked process\n");

        /*
         * The child inherited the global exception_stack pointer.
         * PostgreSQL relies on this to still work after fork().
         */
        child_action_with_error();

        /* Should never reach */
        printf("[child] ERROR: longjmp failed\n");
        _exit(2);
    }

    /* ---- PARENT ---- */
    printf("[parent] waiting for child\n");
    int status;
    waitpid(pid, &status, 0);

    if (WIFEXITED(status))
        printf("[parent] child exited %d\n", WEXITSTATUS(status));
    else if (WIFSIGNALED(status))
        printf("[parent] child killed by signal %d\n", WTERMSIG(status));

    printf("[parent] normal exit\n");
    return 0;
}
