// vfork_test.c
#define _GNU_SOURCE
#include <unistd.h>
#include <sys/wait.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include "test.h"

/*
 * This test checks that:
 *  - vfork() does not corrupt parent stack
 *  - child does not run parent epilogue
 *  - execve() path works
 *  - _exit() path works
 */

static int global_flag = 0;

static int run_vfork_exec(void) {
    pid_t pid;
    int status = -1;

    pid = vfork();
    if (pid < 0) {
        _exit(100);  // must not return
    }

    if (pid == 0) {
        // CHILD
        // CPython-style constraints:
        //  - no malloc
        //  - no stdio
        //  - no stack-heavy logic

        char *argv[] = {
            (char *)"/bin/true",
            NULL
        };
        char *envp[] = { NULL };

        execve("/bin/true", argv, envp);

        // If execve fails, must _exit()
        _exit(127);
    }

    // PARENT
    if (waitpid(pid, &status, 0) < 0)
        return -1;

    if (!WIFEXITED(status))
        return -2;

    return WEXITSTATUS(status);
}

static int run_vfork_exit(void) {
    pid_t pid;

    pid = vfork();
    if (pid < 0)
        return -1;

    if (pid == 0) {
        // CHILD
        global_flag = 42;  // should be visible to parent
        printf("In child before _exit global_flag=%d\n", global_flag);
        ASSERT(42, global_flag);
        printf("OK\n");
        _exit(0);
    }

    // PARENT
    if (global_flag != 42)
        return -2;

    return 0;
}

int main(void) {
    int r1 = run_vfork_exec();
    int r2 = run_vfork_exit();

    if (r1 != 0)
        return 1;

    if (r2 != 0)
        return 2;

    return 0;
}
