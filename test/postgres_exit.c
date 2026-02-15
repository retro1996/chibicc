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
    printf("Callback called with code=%d, arg=%ld\n", code, arg);
    ASSERT(0, code);
    ASSERT(12345, arg);
}

static void my_callback2(int code, Datum arg) {
    printf("Callback2 called with code=%d, arg=%ld\n", code, arg);
    ASSERT(0, code);
    ASSERT(67890, arg);
}

int main() {
    on_proc_exit(my_callback, 12345);
    on_proc_exit(my_callback2, 67890);
    
    // Verify values in the list before execution
    ASSERT(12345, on_proc_exit_list[0].arg);
    ASSERT(67890, on_proc_exit_list[1].arg);
    
    proc_exit_prepare(0);
    
    printf("OK\n");
    return 0;
}
