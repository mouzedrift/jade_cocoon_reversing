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

INCLUDE_DATA(off_80072278);

INCLUDE_ASM(sub_800174F8);
INCLUDE_ASM(sub_8001761C);
INCLUDE_ASM(sub_80017784);
INCLUDE_ASM(sub_800178C0);
INCLUDE_ASM(sub_80017A6C);
INCLUDE_ASM(sub_80017B10);
INCLUDE_ASM(sub_80017BF0);
INCLUDE_ASM(sub_80017CE4);
INCLUDE_ASM(sub_80017E30);
INCLUDE_ASM(sub_80017FF8);
// Matched
int sub_800181E8(void)
{
    return *dword_80091C00;
}
INCLUDE_ASM(sub_80018200);
INCLUDE_ASM(sub_800182B8);
