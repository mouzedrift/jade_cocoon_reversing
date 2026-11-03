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

INCLUDE_DATA(dword_8007415C);


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
extern void DrawText_8003E91C(int mode, int a, void* b, int c);
#if 0
// Not matched: loop pointer is strength-reduced differently
void sub_8002A310(struct_entry8* e, int a1)
{
    if (e)
    {
        while (e->field_4)
        {
            unsigned short loc[2];
            loc[0] = e->x;
            loc[1] = e->y;
            DrawText_8003E91C(2, e->field_4, loc, a1);
            e++;
        }
    }
}
#endif
INCLUDE_ASM(sub_8002A310);
typedef struct
{
    int field_0;
    int field_4;
    short field_8;
    short field_A;
} struct_F1C8;
extern short uiColor_8008B590;
typedef struct
{
    short color;
    unsigned char field_2;
    unsigned char field_3;
} struct_A384_buf;
extern void sub_80042460(int a, struct_A384_buf* b, void* c, int d);
// Matched
void sub_8002A384(struct_F1C8* p)
{
    struct_A384_buf buf;
    unsigned char c = p->field_8;
    short col = uiColor_8008B590;
    buf.field_3 = 1;
    buf.field_2 = c;
    buf.color = col;
    sub_80042460(p->field_0, &buf, &pOT_8008D454[p->field_A], p->field_4);
}
typedef struct
{
    int field_0;
    int field_4;
    int field_8;
} struct_12_c;
extern int dword_800827BC[];
// Matched
short sub_8002A3E0(int a)
{
    if (a < 30)
    {
        return (short)dword_800827BC[((struct_12_c*)dword_8007C438)[a].field_8];
    }
    return 36;
}
extern void sub_800A61CC(int a, void* b, void* c);
extern void AddTexWindowPrim_8003326C(int a, void* b);
// Matched
void sub_8002A42C(unsigned short* pos, short a1, int a2, short a3)
{
    unsigned short buf1[10];
    char buf2[8];
    sub_800A61CC(a1, buf1, buf2);
    buf1[4] = pos[0];
    buf1[5] = pos[1];
    AddPrimCopy_80040298(pOT_8008D454 + a3, buf1, 5);
    AddPrimCopy_80040298(pOT_8008D454 + a3, buf2, 2);
    if (a2)
    {
        AddTexWindowPrim_8003326C(a2, &pOT_8008D454[a3]);
    }
}
#if 0
extern char aFb[];
// Not matched (33 words): the original reads the pair at 0x800827EC through its own address, not through aFb
void sub_8002A4E4(short a0)
{
    unsigned short buf1[10];
    char buf2[8];
    sub_80042B38((int)aFb, a0);
    sub_800A61CC(1, buf1, buf2);
    buf1[4] = ((unsigned short*)aFb)[4];
    buf1[5] = ((unsigned short*)aFb)[5];
    AddPrimCopy_80040298(pOT_8008D454 + a0, buf1, 5);
    AddPrimCopy_80040298(pOT_8008D454 + a0, buf2, 2);
    sub_800429F8((int)aFb, a0);
}

#endif
INCLUDE_ASM(sub_8002A4E4);
typedef struct
{
    unsigned short flags;
    char pad_2[0xE];
    char field_10[0xC];
} struct_A5A4_item;
typedef struct
{
    int field_0;
    int field_4;
    int field_8;
    int field_C;
    struct_A5A4_item** field_10;
    int field_14;
} struct_A5A4;
extern void sub_8004196C(void* a0, void* a1, int a2, int a3, int a4);
extern void AddClipTexWindowPrim_80033308(void* a);
extern void sub_8002A710(void* a, int b);
extern void sub_8002AAF0(struct_A5A4* p, int i, int j, RECT* r);
// Matched
void sub_8002A5A4(struct_A5A4* p)
{
    RECT r;
    int i;
    int j;
    for (i = 0; p->field_10[i]; i++)
    {
        for (j = 0; !(p->field_10[i][j].flags & 1); j++)
        {
            sub_8004196C(&r, p->field_10[i][j].field_10, p->field_8, 8, 0);
            AddClipTexWindowPrim_80033308(pOT_8008D454 + p->field_14);
            sub_8002A710(&p->field_10[i][j], p->field_14);
            AddTexWindowPrim_8003326C((int)&r, pOT_8008D454 + p->field_14);
            sub_8002AAF0(p, i, j, &r);
        }
    }
    sub_8003F900(2, 0);
    sub_8003F900(1, 0);
}
INCLUDE_ASM(sub_8002A710);
