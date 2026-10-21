#include "api.h"

int32_t event_value(int32_t value, ...) _ensures(return == value) {
    return value;
}

int32_t later_value(int32_t value) _ensures(return == value);

int32_t selected_body(int32_t *p) _preserves_value(*p) _ensures(return == *p) {
    return event_value(read_nested(p), later_value(*p));
}

int32_t later_value(int32_t value) {
    return value;
}

int32_t checked_tail(int32_t value) _requires(value < INT32_MAX)
    _ensures(return == value) {
    return event_value(value, increment_value(value));
}

int32_t missing_ownership(_plain int32_t *p) {
    return event_value(0, read_nested(p));
}

int32_t missing_bound(int32_t value) {
    return event_value(0, increment_value(value));
}

int32_t wrong_result(int32_t *p) _preserves_value(*p) _ensures(return == 7) {
    return event_value(read_value(p), read_nested(p));
}
