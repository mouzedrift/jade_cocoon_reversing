#include "common.h"
#include "funcs.h"
#include "MALLOC.H"
#include "LIBGTE.H"
#include "LIBGPU.H"
#include "LIBAPI.H"
#include "globals.h"
#include "STDLIB.H"
#include "STDIO.H"
#include "LIBPAD.H"
#include "LIBSND.H"
#include "LIBMCX.H"
#include "LIBPRESS.H"
#include "LIBETC.H"
#include "LIBMCRD.H"
#include "sound.h"
#include "data_decls.h"

INCLUDE_DATA(dword_8007442C);
INCLUDE_DATA(dword_80074430);
INCLUDE_DATA(dword_80074434);

INCLUDE_ASM(sub_8002F6F8);
INCLUDE_ASM(sub_8002F7D0);
INCLUDE_ASM(sub_8002F8E4);
// Matched
short sub_8002FA70(void)
{
    return sub_80033514((Minion*)sub_80033ABC((char*)&saveData_8008B570));
}
INCLUDE_ASM(sub_8002FAA0);
INCLUDE_ASM(sub_8002FBD8);
