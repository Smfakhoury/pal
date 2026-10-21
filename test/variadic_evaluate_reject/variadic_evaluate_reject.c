#include "pal.h"
#include <stdint.h>

int32_t first(int32_t value, ...) { return value; }
int32_t write(int32_t *p) { *p = 9; return 1; }
int32_t read(int32_t *p);

int32_t tail_increment(int32_t *p) { return first(42, (*p)++); }
int32_t tail_assignment(int32_t *p) { return first(42, *p = 3); }
int32_t tail_call(int32_t *p) { return first(42, read(p)); }
int32_t volatile_read(volatile int32_t *p) { return first(42, *p); }
int32_t fixed_effect(int32_t *p) { return first(write(p), *p); }
int32_t unsequenced(int32_t *p) { return first((*p)++, *p); }
int32_t nested(int32_t *p) { return 1 + first(42, *p); }
int32_t call_argument(int32_t *p) { return first(first(42, *p)); }
int32_t conditional(int32_t flag, int32_t *p) {
    return flag ? first(42, *p) : 7;
}
int32_t short_circuit(int32_t flag, int32_t *p) {
    return flag && first(42, *p);
}
int32_t comma_tail(int32_t *p) { return first(42, (*p, 0)); }
int32_t conditional_tail(int32_t flag, int32_t *p) {
    return first(42, flag ? (*p)++ : 0);
}
int32_t signed_shift(int32_t *p) { return first(42, *p << 1); }
int32_t atomic_read(_Atomic int32_t *p) { return first(42, *p); }
int32_t wide_shift(uint32_t *p, uint64_t count) { return first(42, *p << count); }
int32_t conditional_initializer(int32_t flag, int32_t *p) {
    int32_t result = flag ? first(42, *p) : 0;
    return result;
}
int32_t effectful_sibling(int32_t *p) {
    int32_t result = first(42, *p) + write(p);
    return result;
}
int32_t fixed_read_call(int32_t *p) { return first(read(p), *p); }
int32_t fixed_assignment(int32_t *p) { return first(*p = 3, *p); }
int32_t fixed_volatile(volatile int32_t *v, int32_t *p) { return first(*v, *p); }
int32_t fixed_atomic(_Atomic int32_t *v, int32_t *p) { return first(*v, *p); }
int32_t fixed_comma(int32_t *p) { return first((*p, 0), *p); }
int32_t fixed_conditional(int32_t flag, int32_t *p) {
    return first(flag ? write(p) : 0, *p);
}
int32_t unsequenced_tail(int32_t *p) { return first(*p, (*p)++); }
int32_t fixed_short_circuit(int32_t flag, int32_t *p) {
    return first(flag && *p, *p);
}
int32_t recursive(int32_t *p) { return recursive(p); }
int32_t recursive_tail(int32_t *p) { return first(0, recursive(p)); }
int32_t unknown_pure(int32_t *p) __attribute__((pure));
int32_t pure_claim(int32_t *p) { return first(0, unknown_pure(p)); }
int32_t impure_body(int32_t *p) { return ++*p; }
int32_t call_write(int32_t *p) { return first(*p, impure_body(p)); }
int32_t call_write_fixed(int32_t *p) { return first(impure_body(p), *p); }
int32_t call_bad_argument(int32_t *p) { return first(0, read((*p = 1, p))); }
int32_t with_local(int32_t *p) { int32_t value = *p; return value; }
int32_t unsupported_body(int32_t *p) { return first(0, with_local(p)); }
int32_t indirect_tail(int32_t (*fn)(int32_t *), int32_t *p) {
    return first(0, fn(p));
}
int32_t claimed_pure_write(int32_t *p) __attribute__((pure));
int32_t claimed_pure_write(int32_t *p) { return ++*p; }
int32_t false_purity(int32_t *p) { return first(0, claimed_pure_write(p)); }
int32_t identity(int32_t value) { return value; }
int32_t known_bad_argument(int32_t *p) { return first(*p, identity((*p)++)); }
int32_t vla_bound(int32_t *p, int32_t values[(*p)++]) { return *values; }
int32_t hidden_vla_effect(int32_t *p, int32_t *values) { return first(*p, vla_bound(p, values)); }
int32_t static_bound(int32_t values[static 4]);
int32_t static_bound(int32_t *values) { return *values; }
int32_t hidden_static_bound(int32_t *values) { return first(0, static_bound(values)); }
