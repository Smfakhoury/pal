#include "api.h"

int32_t read_nested(int32_t *p) {
    return read_value(p);
}

int32_t read_value(int32_t *p) {
    return *p;
}

int32_t increment_value(int32_t value) {
    return value + 1;
}

int32_t false_value(void) {
    return 2;
}
