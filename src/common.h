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

#define MAX_PLAYER_NAME_LENGTH 10

/* pull in the assembly generated from the original executable (scripts/split.py), run from the repository root */
#define INCLUDE_ASM(name) __asm__(".include \"asm/f/" #name ".s\"")
#define INCLUDE_OVERLAY_ASM(dir, name) __asm__(".include \"asm/overlays/" #dir "/" #name ".s\"")
#define INCLUDE_DATA(name) __asm__(".include \"asm/d/" #name ".s\"")

#endif
