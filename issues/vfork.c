#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(void) {
    pid_t pid = 0;
    int errpipe = 0;   // simulate parent stack variable for error reporting

    pid = vfork();
    if (pid < 0) {
        perror("vfork");
        return 1;
    }

    if (pid == 0) {  // child
    //     // safe write to parent stack variable
         errpipe = 123;
         return 0;   // child exits safely
     }

    // parent reads updated value
    printf("errpipe = %d\n", errpipe);
    printf("OK\n");
    return 0;
}
