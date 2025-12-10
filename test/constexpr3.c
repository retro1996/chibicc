#include "test.h"
#include <stdint.h>
int main() {
    char arr[3];
    char (*arr_ptr)[UINT32_MAX + 1ULL];
    printf("%lld sizeof(*arr_ptr)=%lld \n", (UINT32_MAX + 1ULL), sizeof(*arr_ptr) );
    DASSERT( sizeof(*arr_ptr) == (UINT32_MAX + 1ULL));
    printf("sizeof( (typeof(arr)){0} )=%d\n", sizeof( (typeof(arr)){0} ));
    DASSERT(3 == sizeof( (typeof(arr)){0} ));
    printf("sizeof((0, arr))=%d\n", sizeof((0, arr)));
    DASSERT(8 == sizeof((0, arr)));      
    printf("sizeof((0 ? 0: arr))=%d\n", sizeof((0 ? 0: arr)));
    DASSERT(8 == sizeof((0 ? 0: arr)));
    return 0;

}