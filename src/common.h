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
    long vx;
    long vy;
    long vz;
} LVec3;

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
