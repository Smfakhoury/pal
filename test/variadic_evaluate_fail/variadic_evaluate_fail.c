#include "pal.h"
#include <stdint.h>

int32_t first(int32_t value, ...)
    _ensures(return == value)
{
    return value;
}

int32_t missing_ownership(_plain int32_t *p)
{
    return first(42, *p);
}

int32_t unchecked_overflow(int32_t value)
{
    return first(42, value + 1);
}

int32_t unchecked_division(uint32_t divisor)
{
    return first(42, 100u / divisor);
}

int32_t wrong_result(int32_t *p)
    _preserves_value(*p)
    _ensures(return == 99)
{
    return first(42, *p);
}

int32_t unchecked_bounds(_array uint32_t *p)
{
    return first(42, p[0]);
}

int32_t unchecked_shift(uint32_t *p, uint32_t shift)
{
    return first(42, *p << shift);
}

int32_t unchecked_signed_division(int32_t value)
{
    return first(42, value / -1);
}

int32_t missing_fixed_ownership(_plain int32_t *p, int32_t *tail)
{
    return first(*p, *tail);
}

int32_t unchecked_fixed_overflow(int32_t value, int32_t *tail)
{
    return first(value + 1, *tail);
}

int32_t unchecked_fixed_bounds(_array int32_t *p, int32_t *tail)
{
    return first(p[0], *tail);
}

int32_t unchecked_fixed_division(int32_t divisor, int32_t *tail)
{
    return first(100 / divisor, *tail);
}
