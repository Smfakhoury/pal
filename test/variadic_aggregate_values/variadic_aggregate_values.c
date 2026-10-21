#include "pal.h"
#include <stdint.h>

struct Value { int32_t first; int32_t second; };

int32_t log_value(struct Value value, ...) _ensures(return == value.first) {
    return value.first;
}

int32_t log_event(struct Value value, ...) _ensures(return == 0) {
    return 0;
}

int32_t initialized_tail(int32_t *p) _preserves_value(*p) _ensures(return == 3) {
    return log_value((struct Value){3, 0}, (struct Value){.first = *p});
}

int32_t conditional_fixed(_nullable struct Value *p)
    _ensures(return == 0) {
    return log_event(p == ((void *)0) ? (struct Value){0} : *p, (struct Value){0});
}

int32_t null_call(void) _ensures(return == 0) {
    return conditional_fixed((void *)0);
}

int32_t nullable_log(_nullable struct Value *p, ...) _ensures(return == 0) {
    return 0;
}

int32_t cast_null_fixed(void) _ensures(return == 0) {
    return nullable_log((struct Value *)((void *)0), (struct Value){0});
}

int32_t bounded_tail(int32_t n) _requires(n < INT32_MAX) _ensures(return == 0) {
    return log_value((struct Value){0}, (struct Value){.first = n + 1});
}

int32_t missing_tail_ownership(_plain int32_t *p) {
    return log_value((struct Value){0}, (struct Value){.first = *p});
}

int32_t overflowing_tail(int32_t n) {
    return log_value((struct Value){0}, (struct Value){.first = n + 1});
}
