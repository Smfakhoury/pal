#include "pal.h"
#include <stdint.h>

void status_value(int32_t status)
{
    status;
}

void checked_read(int32_t *p)
    _preserves_value(*p)
{
    *p;
    (void)*p;
}

void checked_arithmetic(int32_t value)
    _requires(value >= 0 && value < 10)
{
    value + 1;
}

void nullable_read(_nullable int32_t *p)
{
    p == 0 ? 0 : *p;
}

void missing_ownership(_plain int32_t *p)
{
    *p;
}

void missing_void_ownership(_plain int32_t *p)
{
    (void)*p;
}

void missing_overflow(int32_t value)
{
    value + 1;
}

void missing_division(uint32_t divisor)
{
    100u / divisor;
}
