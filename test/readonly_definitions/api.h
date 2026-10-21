#include "pal.h"
#include <stdint.h>

int32_t read_value(int32_t *p) _preserves_value(*p) _ensures(return == *p);
int32_t read_nested(int32_t *p) _preserves_value(*p) _ensures(return == *p);
int32_t increment_value(int32_t value)
    _requires(value < INT32_MAX) _ensures(return == value + 1);
int32_t false_value(void) _ensures(return == 3);
