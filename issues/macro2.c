#include "test.h"
#ifndef __has_include
#error
#endif

#if !__has_include("test.h")
#error
#endif

#if !__has_include(<stdio.h>)
#error
#endif

#define A B
#define B C(test.h)
#define C(x) STR(x)
#define STR(x) #x

#if !__has_include(A)
#error
#endif

#define HASH(x) #x
#define STR(x) HASH(x)
#define STR_STUFF(X,...) #__VA_OPT__(X X ## X __VA_ARGS__ X ## ## X X)

int main(void) {
#define H(x) #x
#define STR(x) H(x)

#define M1(X) H(X) H(X)
ASSERT(0, strcmp("00", M1(__COUNTER__)) );

#define M2(A,B,...) H(__VA_OPT__(A##B))
ASSERT(0, strcmp("XY", M2(X,Y,z)) );

#define M3(A,B,...) #__VA_OPT__(A##B)
ASSERT(0, strcmp("XY", M3(X,Y,z)) );

#define EXPAND_PASTE(x,y) x + x##y
#define i 5
ASSERT(107, ({ int i3=100; EXPAND_PASTE(1+i,3); }));
#undef i

#define M4(A,...) H((A,##__VA_ARGS__))
ASSERT(0, strcmp("(X,)",  M4(X,) ));

#define M5(x,...) b ## __VA_OPT__(x)
ASSERT(0, strcmp("bbz", STR(M5(M5(z,a),b)) ));

#define hash_hash # ## #
#define mkstr(a) # a
#define in_between(a) mkstr(a)
#define join(c, d) in_between(c hash_hash d)
ASSERT(0, strcmp("x ## y", join(x,y) ));


#define M6(x,y,z) x ## ## y ## ## z
  ASSERT(0, strcmp("3", STR(M(,,3))));

  ASSERT(0, strcmp("3", STR_STUFF(,M(,,3))));

#define M1(X) a X ## X ## b
  ASSERT(0, strcmp("a b", STR(M1())));

#define M2(X, ...) __VA_OPT__(a X) ## b
  ASSERT(0, strcmp("a b", STR(M2(,.))));

#define M3(X, ...) a ## __VA_OPT__(X b)
  ASSERT(0, strcmp("a b", STR(M3(,.))));

#define M4(X, ...) __VA_OPT__(a X ## X) ## b
  ASSERT(0, strcmp("a b", STR(M4(,.))));

#define M5(X, ...) a ## __VA_OPT__(X ## X b)
  ASSERT(0, strcmp("a b", STR(M5(,.))));


printf("OK\n");

}