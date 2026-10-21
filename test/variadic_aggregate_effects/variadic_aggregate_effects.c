#include "pal.h"

struct Value { int first; int second; };
struct VolatileValue { volatile int value; };
int log_value(int tag, ...) { return tag; }
int unknown(void);

int incremented(int *p) {
    return log_value(0, (struct Value){.first = (*p)++});
}

int absent_definition(void) {
    return log_value(0, (struct Value){.first = unknown()});
}

int volatile_storage(void) {
    return log_value(0, (struct VolatileValue){0});
}
