#include "test.h"

typedef struct Point {
  int x;
  long y;
} Point;

typedef union Number {
  int i;
  long l;
} Number;

int g_int = 11;
static long g_static_long = 22;
unsigned short g_ushort = 33;
_Bool g_bool = 1;
char g_char = 'A';
float g_float = 1.25f;
double g_double = 2.5;
long double g_ldouble = 3.75L;
const int g_const = 44;
volatile int g_volatile = 55;
int g_arr[3] = {1, 2, 3};
Point g_point = {3, 4};
Number g_num = {7};

static long mix_scalars(int a, long b, char c, double d, long double ld) {
  short s = 5;
  unsigned int ui = 6;
  long long ll = 7;
  unsigned long long ull = 8;
  __int128 i128 = 9;
  unsigned __int128 u128 = 10;
  int out = a + (int)b + c + (int)d + (int)ld + s + (int)ui + (int)ll + (int)ull;
  out += (int)i128 + (int)u128;
  return out;
}

static int use_compound_and_qual(Point *p, int arr[3]) {
  Point local_p = *p;
  Number local_n;
  local_n.l = 9;

  const int c_local = local_p.x;
  volatile int v_local = arr[1];
  int tmp = arr[2];
  int *restrict rp = &tmp;

  Point *pp = &local_p;
  int first = pp->x;
  int second = *(rp);
  return first + second + c_local + v_local + (int)local_n.l;
}

int main(void) {
  int local_arr[3] = {10, 20, 30};
  Point local_point = g_point;
  Point *ptr = &local_point;

  long a = mix_scalars(1, 2, 3, 4.0, 5.0L);
  int b = use_compound_and_qual(ptr, local_arr);

  ASSERT(60, (int)a);
  ASSERT(65, b);

  ASSERT(11, g_int);
  LASSERT(22, g_static_long);
  ASSERT(33, g_ushort);
  ASSERT(1, g_bool);
  ASSERT(65, g_char);
  ASSERT(2, (int)g_double);
  ASSERT(3, (int)g_ldouble);
  ASSERT(44, g_const);
  ASSERT(55, g_volatile);
  ASSERT(2, g_arr[1]);
  ASSERT(3, g_point.x);
  LASSERT(7, g_num.i);

  printf("OK\n");
  return 0;
}
