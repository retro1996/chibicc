
#include <stdio.h>

typedef struct { int dummy; } PyObject;

static inline void hmacmodule_clear(PyObject *mod) {
    (void)mod; 
    printf("hmacmodule_clear called\n");
}

static inline void hmacmodule_free(void *mod) {
    // call clear but cast to PyObject*
    (void)hmacmodule_clear((PyObject *)mod);
}

struct PyModuleDef {
    const char *m_name;
    int m_size;
    void (*m_traverse)(void);
    void (*m_clear)(void *);
    void (*m_free)(void *);
};

static struct PyModuleDef _hmacmodule = {
    .m_name = "_hmac",
    .m_size = sizeof(PyObject),
    .m_traverse = NULL,
    .m_clear = (void (*)(void *))hmacmodule_clear,
    .m_free = hmacmodule_free,  // <-- inline function assigned directly
};

int main() {
    PyObject obj;
    if (_hmacmodule.m_free)
        _hmacmodule.m_free(&obj);  // will try to call hmacmodule_free
    return 0;
}
