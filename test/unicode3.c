// unicode_torture.c
#define _GNU_SOURCE
#include "test.h"
#include <stdint.h>
#include <stddef.h>
#include <stdarg.h>
#include <string.h>
#include <wchar.h>
#include <locale.h>
#include <stdlib.h>
#include <uchar.h>

/* ------------------------------
 * 1. UTF-8 byte sequences
 * ------------------------------ */
static void test_utf8_bytes(void) {
    const char *utf8[] = {
        "é",            // 2 bytes
        "漢",           // 3 bytes
        "𝄞",           // 4 bytes (U+1D11E)
        "🙂",           // 4 bytes
        "a̐éö̲",       // combining characters
        NULL
    };

    puts("[UTF-8 byte lengths]");
    for (int i = 0; utf8[i]; i++) {
        printf("  \"%s\" -> %zu bytes\n", utf8[i], strlen(utf8[i]));
    }
}

/* ------------------------------
 * 2. wchar_t (UTF-32 on Linux)
 * ------------------------------ */
static void test_wchar(void) {
    wchar_t w[] = L"é漢𝄞🙂";

    puts("\n[wchar_t]");
    printf("  sizeof(wchar_t) = %zu\n", sizeof(wchar_t));
    printf("  length = %zu\n", wcslen(w));

    for (size_t i = 0; w[i]; i++) {
        printf("  U+%08X\n", (unsigned)w[i]);
    }
}

/* ------------------------------
 * 3. char16_t / char32_t
 * ------------------------------ */
static void test_char_types(void) {
    char16_t u16[] = u"é漢";
    char32_t u32[] = U"𝄞🙂";

    puts("\n[char16_t]");
    for (size_t i = 0; u16[i]; i++) {
        printf("  U+%04X\n", u16[i]);
    }

    puts("\n[char32_t]");
    for (size_t i = 0; u32[i]; i++) {
        printf("  U+%08X\n", u32[i]);
    }
}

/* ------------------------------
 * 4. Struct alignment stress
 * ------------------------------ */
struct unicode_struct {
    char c;
    wchar_t w;
    char32_t u32;
    int64_t x;
};

static void test_struct_layout(void) {
    struct unicode_struct s = { 'A', L'漢', U'🙂', 0x1122334455667788 };

    puts("\n[struct layout]");
    printf("  sizeof(struct) = %zu\n", sizeof(s));
    printf("  offsetof(w)    = %zu\n", offsetof(struct unicode_struct, w));
    printf("  offsetof(u32)  = %zu\n", offsetof(struct unicode_struct, u32));
    printf("  offsetof(x)    = %zu\n", offsetof(struct unicode_struct, x));
    ASSERT(24, sizeof(s));
    ASSERT(4, offsetof(struct unicode_struct, w));
    ASSERT(8, offsetof(struct unicode_struct, u32));
    ASSERT(16, offsetof(struct unicode_struct, x));
}

/* ------------------------------
 * 5. Varargs with Unicode
 * ------------------------------ */
static void vtest(const char *fmt, ...) {
    va_list ap;
    va_start(ap, fmt);
    vprintf(fmt, ap);
    va_end(ap);
}

static void test_varargs(void) {
    puts("\n[varargs]");
    vtest("  %s %lc %d %f\n", "漢", L'🙂', 42, 3.14159);
}

/* ------------------------------
 * 6. malloc + Unicode lifetime
 * ------------------------------ */
static void test_heap(void) {
    puts("\n[heap]");
    char *p = strdup("é漢𝄞🙂");
    printf("  %s\n", p);
    free(p);
}

/* ------------------------------
 * 7. Mixed calls (stack stress)
 * ------------------------------ */
static int recurse(int n, const wchar_t *w) {
    if (n == 0)
        return w[0];
    return recurse(n - 1, w) + (int)w[n % wcslen(w)];
}

static void test_stack(void) {
    puts("\n[stack]");
    wchar_t w[] = L"é漢𝄞🙂";
    printf("  result = %d\n", recurse(32, w));
}

/* ------------------------------
 * main
 * ------------------------------ */
int main(void) {
    setlocale(LC_ALL, "");

    test_utf8_bytes();
    test_wchar();
    test_char_types();
    test_struct_layout();
    test_varargs();
    test_heap();
    test_stack();

    puts("\n[OK]");
    return 0;
}
