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
typedef struct
{
    int field_0;
    int field_4;
    unsigned char field_8;
    char pad_9;
    short field_A;
} struct_text_A384;
typedef struct
{
    short color;
    unsigned char b;
    unsigned char c;
} struct_text_param;
extern short uiColor_8008B590;
extern void sub_80042460(int a0, struct_text_param* p, unsigned long* a2, int a3);
// Matched
void sub_8002A384(struct_text_A384* p)
{
    struct_text_param t;
    t.b = p->field_8;
    t.c = 1;
    t.color = uiColor_8008B590;
    sub_80042460(p->field_0, &t, &pOT_8008D454[p->field_A], p->field_4);
}
extern short dword_800827BC[][2];
// Matched
short sub_8002A3E0(int idx)
{
    if (idx < 30)
    {
        return dword_800827BC[dword_8007C438[idx].field_8][0];
    }
    return 0x24;
}
extern void sub_8003326C(int a, unsigned long* b);
// Matched
void sub_8002A42C(unsigned short* pos, short a1, int a2, short ot)
{
    unsigned short prim[12];
    int mode[2];
    sub_800A61CC(a1, prim, mode);
    prim[4] = pos[0];
    prim[5] = pos[1];
    sub_80040298(&pOT_8008D454[ot], prim, 5);
    sub_80040298(&pOT_8008D454[ot], mode, 2);
    if (a2)
    {
        sub_8003326C(a2, &pOT_8008D454[ot]);
    }
}
extern char aFb[];
#if 0
// Not matched (original addresses aFb + 8 as a separate data symbol, whose INCLUDE_DATA lives in tu_80014954.c)
void sub_8002A4E4(short ot)
{
    unsigned short prim[12];
    int mode[2];
    sub_80042B38((int)aFb, ot);
    sub_800A61CC(1, prim, mode);
    prim[4] = ((unsigned short*)(aFb + 8))[0];
    prim[5] = ((unsigned short*)(aFb + 8))[1];
    sub_80040298(&pOT_8008D454[ot], prim, 5);
    sub_80040298(&pOT_8008D454[ot], mode, 2);
    sub_800429F8((int)aFb, ot);
}
#endif
INCLUDE_ASM(sub_8002A4E4);
INCLUDE_ASM(sub_8002A5A4);
INCLUDE_ASM(sub_8002A710);
