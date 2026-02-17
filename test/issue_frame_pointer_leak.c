#include <stdio.h>

// This function needs a frame pointer to walk the stack.
void func_needs_fp() {
    printf("Parent frame pointer: %p\n", __builtin_frame_address(1));
}

// This function is simple and a good candidate for frame pointer omission.
int simple_func(int x) {
    return x + 5;
}

int main() {
    printf("Calling func_needs_fp()\n");
    func_needs_fp();
    printf("Calling simple_func()\n");
    simple_func(10);
    printf("Done.\n");
    return 0;
}