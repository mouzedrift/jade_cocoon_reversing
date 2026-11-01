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
#include "LIBSPU.H"
#include "LIBMCX.H"
#include "LIBPRESS.H"
#include "LIBETC.H"
#include "LIBMCRD.H"
#include "sound.h"
#include "data_decls.h"


extern struct_obj_B dword_80091CC8; // really a SpuReverbAttr
extern void sub_8002A218(void);
// Matched
void sub_8002A1BC(int* p)
{
    dword_80091CC8.flags_0 = 0;
    sub_8002A280(&dword_80091CC8, 0);
    sub_8002A2A0(&dword_80091CC8, 0x42, 0x42);
    p[2] = (int)sub_8002A218;
}
// Matched
void sub_8002A218(void)
{
    if (dword_80091CC8.flags_0 != 0)
    {
        SpuSetReverbModeParam((SpuReverbAttr*)&dword_80091CC8);
        if (dword_80091CC8.flags_0 & 1)
        {
            sub_8002A2A0(&dword_80091CC8, 0x42, 0x42);
            SpuSetReverbDepth((SpuReverbAttr*)&dword_80091CC8);
        }
        dword_80091CC8.flags_0 = 0;
    }
}
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
typedef struct
{
    unsigned short x;
    unsigned short y;
    int field_4;
} struct_entry8;
extern void sub_8003E91C(int mode, int a, void* b, int c);
INCLUDE_ASM(sub_8002A310);
INCLUDE_ASM(sub_8002A384);
INCLUDE_ASM(sub_8002A42C);
INCLUDE_ASM(sub_8002A4E4);
INCLUDE_ASM(sub_8002A5A4);
INCLUDE_ASM(sub_8002A710);
