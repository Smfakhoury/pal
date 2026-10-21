#include "pal.h"

int log_value(int value, ...) { return value; }
int missing(void);
int mutating(int *p);
int cycle_a(int n);
int effectful_leaf(void);
int late_attribute(int *p);
static int private_value(void);
static int private_wrapper(void) { return private_value(); }

int absent(void) { return log_value(0, missing()); }
int modified(int *p) { return log_value(0, mutating(p)); }
int cyclic(int n) { return log_value(0, cycle_a(n)); }
int transitive_effect(void) { return log_value(0, effectful_leaf()); }
int private_missing(void) { return log_value(0, private_wrapper()); }
int before_attribute(int *p) { return log_value(0, late_attribute(p)); }
int late_attribute(int *p) __attribute__((nonnull));
