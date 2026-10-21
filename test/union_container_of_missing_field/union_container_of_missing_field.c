#include "pal.h"
#include <stdint.h>

typedef union storage {
    int32_t value;
    unsigned int bits: 3;
} storage_t;

void missing(_plain int32_t *p)
    _requires(_inline_pulse(
        exists* (v: $type(storage_t)).
          pts_to $(_container_of(p, storage_t, missing)) v))
{
}

void wrong_type(_plain int32_t *p)
    _requires(_inline_pulse(
        exists* (v: $type(int32_t)).
          pts_to $(_container_of(p, int32_t, missing)) v))
{
}

void bit_field(_plain unsigned int *p)
    _requires(_inline_pulse(
        exists* (v: $type(storage_t)).
          pts_to $(_container_of(p, storage_t, bits)) v))
{
}
