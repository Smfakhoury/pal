#include "pal.h"

static int metadata_value(void) _ensures(return == 2) {
    static const int value = 2;
    return value;
}

int from_b(void) _ensures(return == 2) {
    return metadata_value();
}
