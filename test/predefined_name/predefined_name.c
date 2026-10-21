#include "pal.h"
#include <stdint.h>

char expect_name(const _array char *name, ...)
    _requires(name._length == 11)
    _requires(name[0] == 'n' && name[1] == 'a' && name[2] == 'm')
    _requires(name[3] == 'e' && name[4] == '_' && name[5] == 'v')
    _requires(name[6] == 'a' && name[7] == 'l' && name[8] == 'u')
    _requires(name[9] == 'e' && name[10] == 0)
    _ensures(return == 'n')
{
    return name[0];
}

char expect_pretty(const _array char *name, ...)
    _requires(name._length == 13)
    _requires(name[0] == 'c' && name[1] == 'h' && name[2] == 'a')
    _requires(name[3] == 'r' && name[4] == ' ' && name[5] == 'p')
    _requires(name[6] == '(' && name[7] == 'v' && name[8] == 'o')
    _requires(name[9] == 'i' && name[10] == 'd' && name[11] == ')')
    _requires(name[12] == 0)
    _ensures(return == 'c')
{
    return name[0];
}

char name_value(int32_t *p)
    _preserves_value(*p)
    _ensures(return == 'n')
{
    expect_name(__FUNCTION__, *p);
    expect_name(__func__, *p);
    return 'n';
}

char p(void)
    _ensures(return == 'c')
{
    expect_pretty(__PRETTY_FUNCTION__);
    return 'c';
}

char name_wrong(int32_t *p)
    _preserves_value(*p)
{
    expect_name(__func__, *p);
    return 'n';
}
