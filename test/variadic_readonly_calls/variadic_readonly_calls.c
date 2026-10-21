#include "pal.h"
#include <stdint.h>

int32_t log_value(int32_t value, ...)
    _ensures(return == value)
{
    return value;
}

int32_t nullable_tail(_nullable int32_t *p)
    _ensures(return == 0)
{
    return log_value(0, p == 0 ? 0 : *p);
}

int32_t conditional_division(uint32_t divisor)
    _ensures(return == 7)
{
    return log_value(7, divisor ? 100u / divisor : 0u);
}

int32_t read_value(int32_t *p)
    _preserves_value(*p)
    _ensures(return == *p)
{
    return *p;
}

int32_t nested_accessor(int32_t *p)
    _preserves_value(*p)
    _ensures(return == *p)
{
    return read_value(p);
}

int32_t accessor_arguments(int32_t *p)
    _preserves_value(*p)
    _ensures(return == *p)
{
    return log_value(read_value(p), nested_accessor(p));
}

struct Request { int32_t field; };

_plain int32_t *field_address(struct Request *request)
    _preserves_value(request->field)
    _ensures(return == &request->field)
{
    return &request->field;
}

int32_t address_accessor(struct Request *request)
    _preserves_value(request->field)
    _ensures(return == request->field)
{
    return log_value(request->field, field_address(request));
}

static int32_t static_zero = 0;

_plain int32_t *activity_default(_plain int32_t *p)
    _ensures(return == (p ? p : &static_zero))
{
    return p ? p : &static_zero;
}

int32_t default_argument(_plain int32_t *p)
    _ensures(return == 0)
{
    return log_value(0, activity_default(p));
}

int32_t conditional_accessor(int32_t enabled, int32_t *p)
    _preserves_value(*p)
{
    if (enabled)
        return *p;
    return 0;
}

int32_t branch_accessor(int32_t enabled, int32_t *p)
    _preserves_value(*p)
    _ensures(return == 0)
{
    return log_value(0, conditional_accessor(enabled, p));
}

int32_t guarded_call(_nullable int32_t *p)
    _ensures(return == 0)
{
    return log_value(0, p ? read_value(p) : 0);
}

int32_t conditional_fixed(int32_t enabled, int32_t *p)
    _preserves_value(*p)
    _ensures(return == (enabled ? *p : 7))
{
    return log_value(enabled ? *p : 7, enabled ? *p : 0);
}

int32_t known_identity(int32_t value)
    _ensures(return == value)
{
    return value;
}

int32_t conditional_call_fixed(int32_t enabled, int32_t value, int32_t *p)
    _preserves_value(*p)
    _ensures(return == (enabled ? value : 7))
{
    return log_value(enabled ? known_identity(value) : 7, enabled ? *p : 0);
}

int32_t null_path(void)
    _ensures(return == 0)
{
    int32_t result = nullable_tail(0);
    return result;
}

int32_t missing_tail_ownership(_plain int32_t *p)
{
    return log_value(0, p == 0 ? 0 : *p);
}

int32_t missing_call_ownership(_plain int32_t *p)
{
    return log_value(0, read_value(p));
}

int32_t reversed_null_guard(_nullable int32_t *p)
{
    return log_value(0, p ? 0 : *p);
}

int32_t conditional_overflow(int32_t enabled, int32_t value)
{
    return log_value(0, enabled ? value + 1 : 0);
}

int32_t checked_add(int32_t value)
    _requires(value < 2147483647)
    _ensures(return == value + 1)
{
    return value + 1;
}

int32_t missing_call_precondition(int32_t value)
{
    return log_value(0, checked_add(value));
}

int32_t bad_contract(int32_t value)
    _ensures(return == 0)
{
    return value;
}

int32_t use_bad_contract(int32_t value)
{
    return log_value(0, bad_contract(value));
}
