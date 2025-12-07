#include "test.h"
#include <stdint.h>

void array_cast_to_bool(int j) {
    char vla[j];
    RASSERT((_Bool)vla);
}

int main(void) {
    array_cast_to_bool(11);

    // Test regular arrays
    {
        char arr[3];
        RASSERT(8 == sizeof((0 ? arr:arr)));
        RASSERT(8 == sizeof((0 ? 0: (char*)arr)));
        RASSERT(8 == sizeof((0 ? (char*)arr:0)));
        RASSERT(8 == sizeof(({(char*)arr;})));
        RASSERT(8 == sizeof((0, (char*)arr)));
        RASSERT(8 == sizeof((0 ? 0: arr)));
        RASSERT(8 == sizeof((0 ? arr:0)));
        RASSERT(8 == sizeof(({arr;})));
        RASSERT(8 == sizeof((0, arr)));    
        RASSERT(3 == sizeof((arr)));    
    }

    // Test VLAs
    {
        int n = 5;
        char vla[n];
        char *pvla = vla;

        RASSERT(8 == sizeof((0 ? vla : vla)));      // ternary decay to pointer
        RASSERT(8 == sizeof((0 ? 0 : (char*)vla))); // explicit cast
        RASSERT(8 == sizeof((0 ? (char*)vla : 0))); // explicit cast
        RASSERT(8 == sizeof(({(char*)vla;})));      // statement expression
        RASSERT(8 == sizeof((0, (char*)vla)));      // comma expression
        RASSERT(8 == sizeof((0 ? 0 : vla)));        // ternary decay
        RASSERT(8 == sizeof((0 ? vla : 0)));        // ternary decay
        RASSERT(8 == sizeof(({vla;})));             // statement expression
        RASSERT(8 == sizeof((0, vla)));             // comma expression
        RASSERT(n == sizeof(vla));                  // actual VLA size
    }

    printf("OK\n");
    return 0;
}
