#ifdef C2PULSE
int native_test_anchor(void) { return 0; }
#else
#include <assert.h>
int from_a(void);
int from_b(void);
int two_scopes(void);
unsigned *cell_address(void);
unsigned tick(void);
extern int global_tag;
int *tag_address(void);
int main(void) {
    assert(from_a() == 1 && from_b() == 2);
    assert(two_scopes() == 3);
    unsigned *p = cell_address();
    assert(*p == 0);
    *p = 9;
    assert(cell_address() == p && *cell_address() == 9);
    assert(tick() == 1 && tick() == 2);
    assert(tag_address() == &global_tag);
    return 0;
}
#endif
