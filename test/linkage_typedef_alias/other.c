#include "pal.h"
#include "types.h"

int read_second(PNode p) _ensures(return == p->value) {
    return p->value;
}
