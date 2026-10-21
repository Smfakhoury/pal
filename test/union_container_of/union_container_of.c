#include "pal.h"
#include <stdint.h>

struct entry {
    int32_t value;
};

typedef union storage {
    struct entry node;
    int32_t scalar;
    int32_t *link;
} storage_t;

// Every arm is addressable even when it is not active. Recovering its
// container preserves the original union ownership and stored value.
void roundtrip(storage_t *u)
{
    storage_t *a = _container_of(&u->node, storage_t, node);
    union storage *b = _container_of(&u->scalar, union storage, scalar);
    storage_t *c = _container_of(&u->link, storage_t, link);
    _assert(a == u);
    _assert(b == u);
    _assert(c == u);
}

void update(storage_t *u, int32_t value)
    _ensures(u->scalar._active && u->scalar == value)
{
    storage_t *parent = _container_of(&u->node, storage_t, node);
    parent->scalar = value;
}

void readdress(_plain int32_t *p)
{
    storage_t *parent = _container_of(p, storage_t, scalar);
    _assert(&parent->scalar == p);
}

union buffer {
    int32_t values[4];
    int32_t scalar;
};

void array_roundtrip(union buffer *u)
    _requires(u->values._active)
    _ensures(u->values._active)
{
    union buffer *parent = _container_of(u->values, union buffer, values);
    _assert(parent == u);
}

// The contract supplies union ownership; container_of alone never does.
int32_t read_scalar(_plain int32_t *p, int32_t expected)
    _preserves(_inline_pulse(
        exists* (v: $type(storage_t)).
          pts_to $(_container_of(p, storage_t, scalar)) v **
          pure (v == $field(storage_t::scalar) $(expected))))
    _ensures(return == expected)
{
    storage_t *parent = _container_of(p, storage_t, scalar);
    return parent->scalar;
}

// Negative: an address conversion cannot manufacture container ownership.
int32_t unowned(_plain int32_t *p)
{
    storage_t *parent = _container_of(p, storage_t, scalar);
    return parent->scalar;
}

// Negative: recovering through one arm does not activate it.
int32_t inactive(storage_t *u)
    _requires(u->node._active)
{
    storage_t *parent = _container_of(&u->scalar, storage_t, scalar);
    return parent->scalar;
}

// Negative: the address laws do not prove an incorrect functional result.
int32_t false_result(_plain int32_t *p, int32_t expected)
    _preserves(_inline_pulse(
        exists* (v: $type(storage_t)).
          pts_to $(_container_of(p, storage_t, scalar)) v **
          pure (v == $field(storage_t::scalar) $(expected))))
    _ensures(return != expected)
{
    storage_t *parent = _container_of(p, storage_t, scalar);
    return parent->scalar;
}
