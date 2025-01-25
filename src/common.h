#ifndef _COMMON_H
#define _COMMON_H

#define COUNTOF(x) (sizeof(x) / sizeof(*(x)))

/*
if this countof version is used then the original code was probably
something like:

enum foo
{
    foo_1,
    foo_2,
    foo_count
}
*/
#define COUNTOF_S(x) (int)(sizeof(x) / sizeof(*(x)))

#endif
