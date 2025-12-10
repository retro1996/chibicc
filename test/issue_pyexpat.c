#include <stdio.h>

typedef void* XML_Parser;
typedef void (*xmlhandler)(void);
typedef void (*xmlhandlersetter)(XML_Parser, xmlhandler);

// Dummy underlying "library" functions
void XML_SetStartElementHandler(XML_Parser parser, xmlhandler h) {
    (void)parser; (void)h;
    printf("XML_SetStartElementHandler called\n");
}

void my_StartElementHandler(void) {
    printf("my_StartElementHandler called\n");
}

// Wrapper macro
#define SETTER_WRAPPER(NAME, TYPE)                              \
    static inline void                                          \
    pyexpat_Set##NAME(XML_Parser parser, xmlhandler handler)    \
    {                                                           \
        (void)XML_Set##NAME(parser, (TYPE)handler);            \
    }

// Expand one handler
SETTER_WRAPPER(StartElementHandler, xmlhandler)

// Struct holding handlers
struct HandlerEntry {
    const char *name;
    xmlhandlersetter setter;
    xmlhandler handler;
};

// Simulate CPython macro: assign inline function in struct
#define HANDLER_INFO(name) \
    {#name, (xmlhandlersetter)pyexpat_Set##name, (xmlhandler)my_##name},

struct HandlerEntry handlers[] = {
    HANDLER_INFO(StartElementHandler)
};

int main(void) {
    XML_Parser parser = NULL;

    // Call via struct
    handlers[0].setter(parser, handlers[0].handler);
    handlers[0].handler();

    return 0;
}
