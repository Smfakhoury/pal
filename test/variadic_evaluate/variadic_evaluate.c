#include "pal.h"
#include <stdint.h>

int32_t first(int32_t value, ...)
    _ensures(return == value)
{
    return value;
}

int32_t read_tail(int32_t *p)
    _preserves_value(*p)
    _ensures(return == 42)
{
    return first(42, *p, *p);
}

int32_t function_name_tail(int32_t *p)
    _preserves_value(*p)
    _ensures(return == 42)
{
    return first(42, __func__, *p);
}

struct Pair { int32_t x; int32_t y; };

int32_t read_fields(struct Pair *p)
    _preserves_value(p->x)
    _preserves_value(p->y)
    _ensures(return == 7)
{
    int32_t result = first(7, p->x, p->y);
    return result;
}

int32_t checked_arithmetic(int32_t value, uint32_t divisor)
    _requires(value >= 0 && value < 10)
    _requires(divisor > 0)
    _ensures(return == 19)
{
    return first(19, value + 1, value * 2, 100u / divisor);
}

int32_t branch_call(int32_t take_branch, int32_t *p)
    _preserves_value(*p)
    _ensures(return == (take_branch ? 42 : 7))
{
    if (take_branch) {
        return first(42, *p);
    }
    return 7;
}

int32_t write_first(int32_t *p, ...)
    _ensures(*p == 9)
    _ensures(return == 17)
{
    *p = 9;
    return 17;
}

int32_t read_before_callee_write(int32_t *p)
    _requires(*p == 10)
    _ensures(*p == 9)
    _ensures(return == 17)
{
    int32_t result = write_first(p, 100 / (*p - 9));
    return result;
}

void statement_call(int32_t *p)
    _ensures(*p == 9)
{
    write_first(p, *p);
}

int32_t read_array(_array uint32_t *p)
    _requires(p._length == 2)
    _ensures(p._length == 2)
    _ensures(return == 42)
{
    return first(42, p[0], p[1] >> 3);
}

int32_t checked_shift(uint32_t *p, uint32_t shift)
    _requires(shift < 32)
    _preserves_value(*p)
    _ensures(return == 42)
{
    return first(42, *p << shift);
}

int32_t second(int32_t a, int32_t b, ...)
    _ensures(return == b)
{
    return b;
}

int32_t fixed_values(int32_t a, int32_t b, int32_t *p)
    _preserves_value(*p)
    _ensures(return == b)
{
    return second(a, b, *p);
}

int32_t branch_ownership(int32_t enabled, _plain int32_t *p)
    _preserves(_inline_pulse(
        if int32_to_bool $(enabled)
        then Pulse.Lib.Reference.pts_to $(p) 42l else emp))
    _ensures(return == (enabled ? 42 : 7))
{
    if (enabled) {
        _ghost_stmt(rewrite
            (if int32_to_bool $(enabled)
             then Pulse.Lib.Reference.pts_to $(p) 42l else emp)
            as (Pulse.Lib.Reference.pts_to $(p) 42l));
        first(*p, *p);
        _ghost_stmt(rewrite (Pulse.Lib.Reference.pts_to $(p) 42l) as
            (if int32_to_bool $(enabled)
             then Pulse.Lib.Reference.pts_to $(p) 42l else emp));
        return 42;
    }
    return 7;
}

int32_t fixed_dereference(int32_t *p)
    _preserves_value(*p)
    _ensures(return == *p)
{
    return first(*p, *p);
}

int32_t fixed_members(struct Pair *p)
    _preserves_value(p->x)
    _preserves_value(p->y)
    _ensures(return == p->x)
{
    return second(p->y, p->x, p->x, p->y);
}

int32_t fixed_array(_array int32_t *p)
    _requires(p._length == 2)
    _ensures(p._length == 2)
    _preserves_value(p[0])
    _preserves_value(p[1])
    _ensures(return == p[1])
{
    return second(p[0], p[1], p[0], p[1]);
}

int32_t fixed_arithmetic(int32_t value, int32_t *p)
    _requires(value >= 0 && value < 10)
    _preserves_value(*p)
    _ensures(return == value + 1)
{
    int32_t result = first(value + 1, *p);
    return result;
}

int32_t value_then_write(int32_t value, int32_t *p, ...)
    _ensures(*p == 9)
    _ensures(return == value)
{
    *p = 9;
    return value;
}

int32_t fixed_value_before_write(int32_t *p)
    _requires(*p == 10)
    _ensures(*p == 9)
    _ensures(return == 11)
{
    return value_then_write(*p + 1, p, 100 / (*p - 9));
}
