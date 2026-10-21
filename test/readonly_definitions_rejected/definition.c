#include "pal.h"

int mutating(int *p) { return (*p)++; }
int cycle_b(int n);
int cycle_a(int n) { return cycle_b(n); }
int cycle_b(int n) { return cycle_a(n); }
int unknown(void);
int effectful_leaf(void) { return unknown(); }
int late_attribute(int *p) { return *p; }
static int private_value(void) { return 1; }
