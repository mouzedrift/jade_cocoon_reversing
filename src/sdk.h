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

#if defined(__psyz) && !defined(DslModeSpeed)
#define DslModeSpeed CdlModeSpeed
#endif

#endif
