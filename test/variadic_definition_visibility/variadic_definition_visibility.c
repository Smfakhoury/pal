#include "pal.h"
#include <stdint.h>

int32_t external_value(int32_t value);
int32_t later_value(int32_t value);
int32_t log_value(int32_t value, ...) { return value; }

int32_t external_fixed(int32_t *p) {
    return log_value(external_value(1), *p);
}
int32_t external_tail(int32_t value) {
    return log_value(0, external_value(value));
}
int32_t later_tail(int32_t value) {
    return log_value(0, later_value(value));
}
int32_t later_value(int32_t value) { return value; }
int32_t visible_tail(int32_t value) {
    return log_value(0, later_value(value));
}

struct Packet { int32_t value; };
int32_t log_packet(struct Packet value, ...) { return value.value; }
int32_t aggregate_fixed(struct Packet *packet, int32_t *p) {
    return log_packet(packet == 0 ? (struct Packet){0} : *packet, *p);
}
struct Packet packet_value(struct Packet value) { return value; }
int32_t aggregate_call_tail(struct Packet *packet) {
    return log_value(0, packet_value(*packet).value);
}

static int32_t zero;
int32_t *void_null_default(int32_t *p) {
    return p != ((void *)0) ? p : &zero;
}
int32_t void_null_tail(int32_t *p) {
    return log_value(0, void_null_default(p));
}
