#include "test.h"

int main() {
  unsigned __int128 a = 0;
  unsigned __int128 b = (((unsigned __int128)1) << 80) | 123;
  unsigned __int128 c;

  // Test __atomic_store_n and __atomic_load_n
  __atomic_store_n(&a, b, 5);
  c = __atomic_load_n(&a, 5);
  ASSERT(1, c == b);

  // Test __atomic_compare_exchange_n (Success)
  unsigned __int128 expected = b;
  unsigned __int128 desired = (((unsigned __int128)1) << 90) | 456;
  // weak=0, success_memorder=5, failure_memorder=5
  _Bool ret = __atomic_compare_exchange_n(&a, &expected, desired, 0, 5, 5);
  ASSERT(1, ret);
  ASSERT(1, a == desired);

  // Test __atomic_compare_exchange_n (Failure)
  expected = 0; // Incorrect expected value
  ret = __atomic_compare_exchange_n(&a, &expected, b, 0, 5, 5);
  ASSERT(0, ret);
  ASSERT(1, expected == desired); // expected should be updated to current value of a
  ASSERT(1, a == desired); // a should remain unchanged

  // Test __atomic_exchange_n
  unsigned __int128 old = __atomic_exchange_n(&a, b, 5);
  ASSERT(1, old == desired);
  ASSERT(1, a == b);

  // Test _Atomic unsigned __int128 (uses atomic_op -> ND_CAS)
  _Atomic unsigned __int128 u128 = 10;
  u128 += 20;
  ASSERT(1, u128 == 30);

  // Test _Atomic long double (16 bytes, uses atomic_op -> ND_CAS)
  _Atomic long double ld = 1.0L;
  ld += 2.0L;
  ASSERT(1, ld == 3.0L);

  // Test arithmetic builtins for int128
  unsigned __int128 val = 100;
  unsigned __int128 res;

  res = __atomic_fetch_add(&val, 50, 0);
  ASSERT(1, res == 100);
  ASSERT(1, val == 150);

  res = __atomic_add_fetch(&val, 50, 0);
  ASSERT(1, res == 200);
  ASSERT(1, val == 200);

  res = __atomic_fetch_sub(&val, 50, 0);
  ASSERT(1, res == 200);
  ASSERT(1, val == 150);

  res = __atomic_sub_fetch(&val, 50, 0);
  ASSERT(1, res == 100);
  ASSERT(1, val == 100);

  res = __atomic_fetch_or(&val, 1, 0);
  ASSERT(1, res == 100);
  ASSERT(1, val == 101);
  
  res = __atomic_or_fetch(&val, 1, 0);
  ASSERT(1, res == 101);
  ASSERT(1, val == 101);

  res = __atomic_fetch_and(&val, 100, 0);
  ASSERT(1, res == 101);
  ASSERT(1, val == 100);
  
  res = __atomic_and_fetch(&val, 100, 0);
  ASSERT(1, res == 100);
  ASSERT(1, val == 100);

  res = __atomic_fetch_xor(&val, 100, 0);
  ASSERT(1, res == 100);
  ASSERT(1, val == 0);
  
  res = __atomic_xor_fetch(&val, 100, 0);
  ASSERT(1, res == 100);
  ASSERT(1, val == 100);
  
  // Test NAND
  val = 0xF0F0F0F0F0F0F0F0;
  val = (val << 64) | 0xF0F0F0F0F0F0F0F0;
  unsigned __int128 mask = 0xFFFFFFFFFFFFFFFF;
  mask = (mask << 64) | 0xFFFFFFFFFFFFFFFF;
  
  // ~(val & mask) = ~(val)
  res = __atomic_fetch_nand(&val, mask, 0);
  // res should be old val
  // val should be ~old_val
  ASSERT(1, res == (((unsigned __int128)0xF0F0F0F0F0F0F0F0 << 64) | 0xF0F0F0F0F0F0F0F0));
  ASSERT(1, val == ~res);
  
  res = __atomic_nand_fetch(&val, mask, 0);
  // val was ~old_val. new val = ~(val & mask) = ~(~old_val) = old_val
  ASSERT(1, res == (((unsigned __int128)0xF0F0F0F0F0F0F0F0 << 64) | 0xF0F0F0F0F0F0F0F0));
  ASSERT(1, val == res);

  // Test __sync builtins
  val = 10;
  res = __sync_fetch_and_add(&val, 20);
  ASSERT(1, res == 10);
  ASSERT(1, val == 30);
  
  res = __sync_add_and_fetch(&val, 20);
  ASSERT(1, res == 50);
  ASSERT(1, val == 50);
  
  res = __sync_fetch_and_sub(&val, 20);
  ASSERT(1, res == 50);
  ASSERT(1, val == 30);
  
  res = __sync_sub_and_fetch(&val, 20);
  ASSERT(1, res == 10);
  ASSERT(1, val == 10);
  
  res = __sync_val_compare_and_swap(&val, 10, 100);
  ASSERT(1, res == 10);
  ASSERT(1, val == 100);
  
  res = __sync_val_compare_and_swap(&val, 10, 200); // Fail
  ASSERT(1, res == 100);
  ASSERT(1, val == 100);
  
  _Bool bool_res = __sync_bool_compare_and_swap(&val, 100, 200);
  ASSERT(1, bool_res);
  ASSERT(1, val == 200);
  
  bool_res = __sync_bool_compare_and_swap(&val, 100, 300); // Fail
  ASSERT(0, bool_res);
  ASSERT(1, val == 200);
  
  // Test __atomic_load and __atomic_store (generic)
  unsigned __int128 store_val = 555;
  unsigned __int128 load_val;
  __atomic_store(&val, &store_val, 5);
  ASSERT(1, val == 555);
  
  __atomic_load(&val, &load_val, 5);
  ASSERT(1, load_val == 555);
  
  // Test __sync_lock_test_and_set and release
  val = 0;
  res = __sync_lock_test_and_set(&val, 1);
  ASSERT(1, res == 0);
  ASSERT(1, val == 1);
  
  __sync_lock_release(&val);
  ASSERT(1, val == 0);
  
  // Test __atomic_test_and_set and __atomic_clear
  unsigned char flag = 0;
  ASSERT(0, __atomic_test_and_set(&flag, 5));
  ASSERT(1, flag);
  ASSERT(1, __atomic_test_and_set(&flag, 5));
  
  __atomic_clear(&flag, 5);
  ASSERT(0, flag);

  printf("OK\n");
  return 0;
}