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


INCLUDE_ASM(sub_8002A1BC);
INCLUDE_ASM(sub_8002A218);
// Matched
void sub_8002A280(struct_obj_B* p, short a1)
{
    p->flags_0 |= 1;
    p->field_4 = (short)(a1 | 0x100);
}
// Matched
void sub_8002A2A0(struct_obj_B* p, short a1, short a2)
{
    sub_8002A2E8(p, a1);
    sub_8002A2FC(p, a2);
}
// Matched
void sub_8002A2E8(struct_obj_B* p, short a1)
{
    p->flags_0 |= 2;
    p->field_8 = a1;
}
// Matched
void sub_8002A2FC(struct_obj_B* p, short a1)
{
    p->flags_0 |= 4;
    p->field_A = a1;
}
INCLUDE_ASM(sub_8002A310);
INCLUDE_ASM(sub_8002A384);
INCLUDE_ASM(sub_8002A42C);
INCLUDE_ASM(sub_8002A4E4);
INCLUDE_ASM(sub_8002A5A4);
INCLUDE_ASM(sub_8002A710);
