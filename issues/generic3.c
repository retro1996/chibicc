#include "test.h"
int main(int argc, char**argv) {

  
  ASSERT(1, ({ void *p; _Generic(argc ? p : "a", void*:1, char*:2); }) );
  ASSERT(1, ({ void *p; _Generic(argc ? "a" : p, void*:1, char*:2); }) );

  ASSERT(1, ({ double *p; char *q; _Generic(argc ? p : q, void*:1 ); }) );
  ASSERT(1, ({ double *p; char *q; _Generic(argc ? q : p, void*:1 ); }) );


  printf("OK\n");
}