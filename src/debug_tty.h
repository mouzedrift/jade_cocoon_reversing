#ifndef _DEBUG_TTY_H
#define _DEBUG_TTY_H

/*
 * Debug output to the emulator's TTY (see docs/testing_in_emulator.md). Experiments only: the macros
 * expand to nothing unless the build is run with JC_DEFINES=DEBUG_TTY, so matching builds are unchanged.
 *
 *   #include "debug_tty.h"
 *   DEBUG_PRINTF(("hp %d at %08x\n", p->hp, (int)p));      <- note the double parentheses
 *
 * DEBUG_PRINTF calls the BIOS printf (A0 function 3Fh), which writes through the BIOS putchar, the TTY
 * that PCSX-Redux logs. The game's own printf (LIBC2) is not used: it buffers 32 characters before it
 * writes anything. The BIOS printf knows %d %i %u %x %X %o %c %s %p and widths, no floats.
 *
 * The A0 table is entered with the function number in $t1, which C cannot set, so the call goes
 * through a 3-instruction stub kept in .data (li $t2,0xA0; jr $t2; li $t1,0x3F).
 */
#ifdef DEBUG_TTY
static unsigned long debug_tty_printf_stub[3] = {0x240A00A0, 0x01400008, 0x2409003F};
#define DEBUG_PRINTF(args) (((int (*)(const char*, ...))debug_tty_printf_stub) args)
#else
#define DEBUG_PRINTF(args) ((void)0)
#endif

#endif
