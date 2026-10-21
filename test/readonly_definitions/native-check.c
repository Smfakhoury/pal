#ifdef C2PULSE
int native_test_anchor(void) { return 0; }
#else
#include "api.h"

int32_t selected_body(int32_t *p);
int32_t checked_tail(int32_t value);

int main(void) {
    int32_t value = 9;
    return selected_body(&value) != 9 || value != 9 ||
           checked_tail(8) != 8 || false_value() != 2;
}
#endif
