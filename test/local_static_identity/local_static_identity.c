#include "pal.h"

static int metadata_value(void) _ensures(return == 1) {
    static const int value = 1;
    return value;
}

int from_a(void) _ensures(return == 1) {
    return metadata_value();
}

int false_a(void) _ensures(return == 2) {
    return metadata_value();
}

int two_scopes(void) _ensures(return == 3) {
    int sum;
    { static const int value = 1; sum = value; }
    { static const int value = 2; sum += value; }
    return sum;
}

_plain unsigned *cell_address(void) {
    static unsigned cell;
    return &cell;
}

unsigned tick(void) _ensures(return == 1) {
    static unsigned calls;
    calls += 1;
    return calls;
}

int global_tag;
_plain int *tag_address(void) {
    extern int global_tag;
    static int *const tag = &global_tag;
    return tag;
}
