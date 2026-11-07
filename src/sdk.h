#ifndef SDK_H
#define SDK_H

/* The PSY-Q headers. On PC (__psyz) the same names come from PSY-Z (external/psyz/psyz/include), which keeps
   the PSY-Q API on top of the platform. */
#ifdef __psyz
#include <psyz.h>
#define DIRENTRY DIRENTRY /* libapi.h (kernel.h) has it, libmcrd.h would define it again */
#endif
#include <sys/types.h>
#include <libds.h>
#include <malloc.h>
#include <libgte.h>
#include <libgpu.h>
#include <libapi.h>
#include <stdlib.h>
#include <stdio.h>
#ifndef __psyz
#include <libpad.h> /* PSY-Z has the pad functions in libetc.h */
#endif
#include <libsnd.h>
#include <libmcx.h>
#include <libpress.h>
#include <libetc.h>
#include <libmcrd.h>
#include <libspu.h>
#include <memory.h>
#include <string.h>

/* the body of a loop that waits for an interrupt (the vsync callback, a CD callback) to change something: on PC,
   where nothing interrupts the game, a vertical blank (VSync(0) runs the callbacks); nothing on the PlayStation */
#ifdef __psyz
#define WAIT_INTERRUPT() VSync(0)
#else
#define WAIT_INTERRUPT()
#endif

#ifndef O_TAG
#define O_TAG u_long tag /* the head of a GPU primitive (PSY-Z's is bigger on 64-bit) */
#endif

#ifdef __psyz /* PSY-Z's malloc.h is the C library's on PC (src/pc/sdk_extra.c has these) */
void InitHeap3(unsigned long* head, unsigned long size);
void* malloc3(size_t size);
void free3(void* block);
long Lzc(long data);
int IsIdMatrix(MATRIX* m);
void StCdInterrupt(void);
#endif

#if defined(__psyz) && !defined(DslModeSpeed)
#include <libcd.h>
#define DslModeSpeed CdlModeSpeed
#endif

#endif
