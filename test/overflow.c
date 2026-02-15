#include "test.h"

typedef unsigned __int128 uint128;  

int main() {
  // Add Overflow - Unsigned
  unsigned int ua = 4294967295u; // UINT_MAX
  unsigned int ub = 1;
  unsigned int ures;
  int ov = __builtin_add_overflow(ua, ub, &ures);
  ASSERT(1, ov);
  ASSERT(0, ures);

  ua = 10;
  ub = 20;
  ov = __builtin_add_overflow(ua, ub, &ures);
  ASSERT(0, ov);
  ASSERT(30, ures);

  // Add Overflow - Signed
  int sa = 2147483647; // INT_MAX
  int sb = 1;
  int sres;
  ov = __builtin_add_overflow(sa, sb, &sres);
  ASSERT(1, ov);
  ASSERT(-2147483648, sres);

  sa = 10;
  sb = 20;
  ov = __builtin_add_overflow(sa, sb, &sres);
  ASSERT(0, ov);
  ASSERT(30, sres);

  // Sub Overflow - Unsigned
  ua = 0;
  ub = 1;
  ov = __builtin_sub_overflow(ua, ub, &ures);
  ASSERT(1, ov);
  ASSERT(4294967295u, ures);

  ua = 30;
  ub = 20;
  ov = __builtin_sub_overflow(ua, ub, &ures);
  ASSERT(0, ov);
  ASSERT(10, ures);

  // Sub Overflow - Signed
  sa = -2147483648; // INT_MIN
  sb = 1;
  ov = __builtin_sub_overflow(sa, sb, &sres);
  ASSERT(1, ov);
  ASSERT(2147483647, sres);

  sa = 30;
  sb = 20;
  ov = __builtin_sub_overflow(sa, sb, &sres);
  ASSERT(0, ov);
  ASSERT(10, sres);

  // Mul Overflow - Unsigned
  ua = 4294967295u; // UINT_MAX
  ub = 2;
  ov = __builtin_mul_overflow(ua, ub, &ures);
  ASSERT(1, ov);
  ASSERT(4294967294u, ures);

  ua = 10;
  ub = 20;
  ov = __builtin_mul_overflow(ua, ub, &ures);
  ASSERT(0, ov);
  ASSERT(200, ures);

  // Mul Overflow - Signed
  sa = 2147483647; // INT_MAX
  sb = 2;
  ov = __builtin_mul_overflow(sa, sb, &sres);
  ASSERT(1, ov);
  ASSERT(-2, sres);

  sa = -10;
  sb = -10;
  ov = __builtin_mul_overflow(sa, sb, &sres);
  ASSERT(0, ov);
  ASSERT(100, sres);

  // Add Overflow - Unsigned __int128
  uint128 u128a = (uint128)-1; // Max uint128
  uint128 u128b = 1;
  uint128 u128res;
  ov = __builtin_add_overflow(u128a, u128b, &u128res);
  ASSERT(1, ov);
  ASSERT128(0, u128res);

  u128a = 10;
  u128b = 20;
  ov = __builtin_add_overflow(u128a, u128b, &u128res);
  ASSERT(0, ov);
  ASSERT128(30, u128res);

  // Add Overflow - Signed __int128
  __int128 s128a = ((__int128)1 << 126); // Large positive
  __int128 s128b = ((__int128)1 << 126); 
  // 2^126 + 2^126 = 2^127, which is larger than max int128 (2^127 - 1) -> overflow for signed? 
  // Max signed int128 is 2^127 - 1. 2^126 + 2^126 = 2^127. So yes, overflow.
  // Wait, max int128 is 0x7fff... (127 bits). The sign bit is bit 128.
  // 1<<126 is positive. (1<<126) + (1<<126) = 1<<127 = 0x8000... which is negative.
  __int128 s128res;
  ov = __builtin_add_overflow(s128a, s128b, &s128res);
  ASSERT(1, ov);
  ASSERT128((__int128)1 << 127, s128res);

  s128a = 10;
  s128b = 20;
  ov = __builtin_add_overflow(s128a, s128b, &s128res);
  ASSERT(0, ov);
  ASSERT128(30, s128res);

  // Sub Overflow - Unsigned __int128
  u128a = 0;
  u128b = 1;
  ov = __builtin_sub_overflow(u128a, u128b, &u128res);
  ASSERT(1, ov);
  ASSERT128((uint128)-1, u128res);

  u128a = 30;
  u128b = 10;
  ov = __builtin_sub_overflow(u128a, u128b, &u128res);
  ASSERT(0, ov);
  ASSERT128(20, u128res);

  // Sub Overflow - Signed __int128
  s128a = ((__int128)1 << 127); // Min signed int128 (negative)
  s128b = 1;
  ov = __builtin_sub_overflow(s128a, s128b, &s128res);
  ASSERT(1, ov);
  ASSERT128(((__int128)1 << 127) - 1, s128res);

  s128a = 30;
  s128b = 10; 
  ov = __builtin_sub_overflow(s128a, s128b, &s128res);
  ASSERT(0, ov);
  ASSERT128(20, s128res);


  printf("OK\n");
  return 0;
}
