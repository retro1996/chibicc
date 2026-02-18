#include "test.h"
#include <stdlib.h>

typedef unsigned long Datum;
typedef void (*pg_on_exit_callback) (int code, Datum arg);

struct on_proc_exit_list_element
{
    pg_on_exit_callback function;
    Datum       arg;
};

static struct on_proc_exit_list_element *on_proc_exit_list;
static int  on_proc_exit_index;
static int  on_proc_exit_size;

void on_proc_exit(pg_on_exit_callback function, Datum arg)
{
    if (on_proc_exit_index >= on_proc_exit_size)
    {
        on_proc_exit_size = on_proc_exit_size ? on_proc_exit_size * 2 : 10;
        on_proc_exit_list = realloc(on_proc_exit_list,
                                    on_proc_exit_size * sizeof(struct on_proc_exit_list_element));
    }

    on_proc_exit_list[on_proc_exit_index].function = function;
    on_proc_exit_list[on_proc_exit_index].arg = arg;
    on_proc_exit_index++;
}

void proc_exit_prepare(int code)
{
    int         i;

    for (i = on_proc_exit_index - 1; i >= 0; i--)
        on_proc_exit_list[i].function(code, on_proc_exit_list[i].arg);
}

static void my_callback(int code, Datum arg) {
    ASSERT(0, code);
    // We can't easily assert arg here as it changes, but we verify it in main
}

int main() {
    // Force multiple reallocs to stress test memory management and pointer updates
    for (int i = 0; i < 100; i++) {
        on_proc_exit(my_callback, (Datum)i);
    }
    
    // Verify the list content to ensure no corruption occurred during realloc
    for (int i = 0; i < 100; i++) {
        if (on_proc_exit_list[i].function != my_callback) {
            printf("Function pointer mismatch at index %d\n", i);
            exit(1);
        }
        if (on_proc_exit_list[i].arg != (Datum)i) {
            printf("Arg mismatch at index %d: expected %d, got %ld\n", i, i, on_proc_exit_list[i].arg);
            exit(1);
        }
    }

    proc_exit_prepare(0);
    
    printf("OK\n");
    return 0;
}
