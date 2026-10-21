#include "pal.h"
#include "types.h"

int read_first(PNode p) _ensures(return == p->value) {
    return p->value;
}
