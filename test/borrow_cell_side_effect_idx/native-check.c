#ifndef C2PULSE
#include <assert.h>
#include <stddef.h>
#include <stdint.h>

void push_call(uint64_t *, size_t *, size_t);
size_t local_array_index(void);
void update_modes(uint64_t *, size_t *);
uint64_t read_saved_index(uint64_t *);
size_t assign_saved_index(size_t *, size_t);
size_t assign_saved_pure_index(size_t *, size_t);
uint64_t return_saved_index(uint64_t *, size_t *);
void signed_index(uint64_t *, int32_t *);
typedef struct { uint64_t start; uint64_t end; } entry;
void update_field(entry *, size_t *, size_t);

int main(void)
{
  uint64_t values[4] = {8, 9, 10, 11};
  size_t i = 0;
  push_call(values, &i, 4);
  assert(i == 1 && values[0] == 0 && values[1] == 9);
  assert(local_array_index() == 1);
  update_modes(values, &i);
  assert(i == 1 && values[1] == 7 && values[2] == 7 && values[3] == 7);
  values[0] = 8;
  assert(read_saved_index(values) == 8);
  size_t indices[2] = {3, 4};
  assert(assign_saved_index(indices, 0) == 3);
  assert(assign_saved_pure_index(indices, 0) == 3);
  i = 0;
  assert(return_saved_index(values, &i) == 8 && i == 1);
  int32_t signed_i = 0;
  signed_index(values, &signed_i);
  assert(signed_i == 1 && values[0] == 0);
  entry entries[2] = {{5, 6}, {7, 8}};
  i = 0;
  update_field(entries, &i, 2);
  assert(i == 1 && entries[0].start == 0 && entries[0].end == 6);
  assert(entries[1].start == 7 && entries[1].end == 8);
  return 0;
}
#endif
