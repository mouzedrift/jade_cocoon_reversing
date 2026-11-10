#ifndef _COMMON_H
#define _COMMON_H

#define COUNTOF(x) (sizeof(x) / sizeof(*(x)))
#ifdef __psyz
#include <stddef.h>
#else
#define offsetof(type, field) ((unsigned long)&((type*)0)->field) /* PSY-Q has no stddef.h */
#endif

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
// a VECTOR without the pad word
typedef struct
{
    int vx; // 32 bit, as VECTOR's (long is 64 bit on a PC)
    int vy;
    int vz;
} LVec3;

/* a call the original made without a prototype in scope: the caller took the int return as it was, without
   extending it again (IMPLICIT_INT(fn)(args)). The function already extends what it returns, so on PC (where
   calling through another type is undefined) it is the function itself */
#ifdef __psyz
#define IMPLICIT_INT(fn) (fn)
#else
#define IMPLICIT_INT(fn) ((int (*)())(fn))
#endif

/* a signed division that may divide by zero: the game is built without the compiler's break on a zero divisor, and
   the R3000 then gives -1 (dividend >= 0) or 1 (dividend < 0). On PC a zero divisor would raise SIGFPE */
#ifdef __psyz
static inline int PsxDiv(int a, int b)
{
    if (b == 0)
        return a >= 0 ? -1 : 1;
    if (b == -1)
        return (int)(0u - (unsigned int)a); /* INT_MIN / -1 wraps as on the R3000 */
    return a / b;
}
#define DIV0(a, b) PsxDiv((a), (b))
#else
#define DIV0(a, b) ((a) / (b))
#endif

#define COUNTOF_S(x) (int)(sizeof(x) / sizeof(*(x)))

#define MAX_PLAYER_NAME_LENGTH 10

/* uninitialised variables are defined straight into .bss, with a zero initialiser: `int x BSS = 0;`. A tentative
   definition would be a common symbol (also with the attribute, once the file declares the variable extern too), and
   psylink aligns every .bss contribution to 8 bytes as soon as there are commons (the game's .bss is packed, see
   docs/full_build.md). With the initialiser the compiler emits it in place, in definition order. */
#define BSS __attribute__((section(".bss")))
#define SDATA __attribute__((section(".sdata")))

/* the first word of an overlay is linked in front of its .rdata (scripts/overlays.py): `int x SDATA = 1;` */
#define SDATA __attribute__((section(".sdata")))

#endif
