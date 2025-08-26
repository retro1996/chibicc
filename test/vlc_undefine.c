#include "test.h"

typedef int vlc_action_id_t;
typedef struct { int dummy; } intf_thread_t;

// Normal function that the action_handler will call
void player_navigate(intf_thread_t *player, int nav) {
    printf("player_navigate called with %d\n", nav);
    ASSERT(42, nav);
}

// Macro defining static inline action handlers
#define PLAYER_ACTION_HANDLER(name) \
    static inline void action_handler_##name(intf_thread_t *player, vlc_action_id_t action_id)

PLAYER_ACTION_HANDLER(Navigate) {
    enum { NAV_UP = 1, NAV_DOWN = 2, NAV_LEFT = 3, NAV_RIGHT = 4, NAV_ACTIVATE = 42 };
    int nav;

    switch (action_id) {
#define PLAYER_NAV_FROM_ACTION(navval) \
        case NAV_##navval: \
            nav = NAV_##navval; \
            break;
        PLAYER_NAV_FROM_ACTION(ACTIVATE)
        PLAYER_NAV_FROM_ACTION(UP)
        PLAYER_NAV_FROM_ACTION(DOWN)
        PLAYER_NAV_FROM_ACTION(LEFT)
        PLAYER_NAV_FROM_ACTION(RIGHT)
#undef PLAYER_NAV_FROM_ACTION
        default:
            ASSERT(0, action_id); // simulate vlc_assert_unreachable
    }

    // Call a normal function
    player_navigate(player, nav);
}

typedef void (*handler_t)(intf_thread_t*, vlc_action_id_t);

struct vlc_action {
    handler_t fptr;
};

// Array of pointers to inline action handlers
static struct vlc_action actions[] = {
    { .fptr = action_handler_Navigate }
};

int main() {
    intf_thread_t i;
    vlc_action_id_t act = 42;  // NAV_ACTIVATE

    actions[0].fptr(&i, act);
    printf("OK\n");
    return 0;
}
