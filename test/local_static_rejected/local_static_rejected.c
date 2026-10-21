#include "pal.h"

static const int value = 7;
int shadowed(void) {
    static const int value = 1;
    _ghost_stmt(assert (pure ($(value) == 7)));
    return value;
}

int tls(void) {
    static _Thread_local int state;
    return state;
}

int __pal_static_reserved;
