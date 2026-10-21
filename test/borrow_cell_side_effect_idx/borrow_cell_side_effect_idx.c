// Regression test for #371: a side-effecting index in `&a[i++]` must be
// evaluated exactly once when borrowing the cell.
#include "pal.h"
#include <stddef.h>
#include <stdint.h>

typedef struct {
  uint64_t start;
  uint64_t end;
} entry;

struct _refine(this.stack._length == this.size && this.count <= this.size) stack {
  _array entry *stack;
  size_t count;
  size_t size;
};

void push_range(struct stack *stk, uint64_t start, uint64_t end)
  _requires(stk->count < stk->size)
  _ensures(stk->count == _old(stk->count) + 1)
{
  entry *me = &stk->stack[stk->count++];
  me->start = start;
  me->end = end;
  _ghost_stmt(array_return_cell $(stk->stack));
}

void set_out(uint64_t *_out p) _ensures(*p == 0) { *p = 0; }

void push_call(_array uint64_t *a, size_t *i, size_t n)
  _requires(a._length == n && *i < n)
  _ensures(*i == _old(*i) + 1)
{
  set_out(&a[(*i)++]);
}

size_t local_array_index(void) _ensures(return == 1)
{
  uint64_t a[2] = {0, 0};
  size_t i = 0;
  uint64_t *p = &a[i++];
  *p = 7;
  _ghost_stmt(array_return_cell $(a));
  _assert(a[0] == 7);
  return i;
}

void write_cell(uint64_t *p) _ensures(*p == 7) { *p = 7; }

uint64_t read_cell(const uint64_t *p) _ensures(return == *p) { return *p; }

size_t read_size(const size_t *p) _ensures(return == *p) { return *p; }

void update_modes(_array uint64_t *a, size_t *i)
  _requires(a._length == 4 && *i == 1)
  _ensures(*i == 1)
{
  write_cell(&a[(*i)++]);
  write_cell(&a[++(*i)]);
  write_cell(&a[--(*i)]);
  write_cell(&a[(*i)--]);
  _assert(a[1] == 7 && a[2] == 7 && a[3] == 7);
}

void update_field(_array entry *a, size_t *i, size_t n)
  _requires(a._length == n && *i < n)
  _ensures(*i == _old(*i) + 1)
{
  size_t index = *i;
  set_out(&a[(*i)++].start);
  _assert(a[index].start == 0);
}

void checked_cell_update(_array uint64_t *a, size_t *i, size_t n)
  _requires(a._length == n && *i < n)
  _ensures(*i == _old(*i) + 1)
{
  size_t index = *i;
  set_out(&a[(*i)++]);
  _assert(a[index] == 0);
}

uint64_t read_saved_index(_array uint64_t *a)
  _requires(a._length == 2 && a[0] == 8)
  _ensures(return == 8)
{
  size_t i = 0;
  uint64_t value = read_cell(&a[i++]);
  _assert(i == 1);
  return value;
}

size_t assign_saved_index(_array size_t *a, size_t i)
  _requires(a._length == 2 && i == 0 && a[0] == 3)
  _ensures(return == 3)
{
  i = read_size(&a[i++]);
  return i;
}

size_t assign_saved_pure_index(_array size_t *a, size_t i)
  _requires(a._length == 2 && i == 0 && a[0] == 3)
  _ensures(return == 3)
{
  i = read_size(&a[i]);
  return i;
}

uint64_t return_saved_index(_array uint64_t *a, size_t *i)
  _requires(a._length == 2 && *i == 0 && a[0] == 8)
  _ensures(return == 8 && *i == 1)
{
  return read_cell(&a[(*i)++]);
}

void missing_increment_bound(_array uint64_t *a, size_t *i)
{
  set_out(&a[(*i)++]);
}

void missing_index_bound(_array uint64_t *a, size_t *i)
  _requires(*i == 0)
{
  set_out(&a[(*i)++]);
}

void signed_index(_array uint64_t *a, int32_t *i)
  _requires(a._length == 2 && *i == 0)
  _ensures(*i == 1)
{
  set_out(&a[(*i)++]);
  _assert(a[0] == 0);
}

void missing_cell_ownership(_plain _array uint64_t *a, size_t *i, size_t n)
  _requires(*i < n)
{
  set_out(&a[(*i)++]);
}

void false_increment_count(_array uint64_t *a, size_t *i, size_t n)
  _requires(a._length == n && *i < n)
  _ensures(*i == _old(*i) + 2)
{
  set_out(&a[(*i)++]);
}
