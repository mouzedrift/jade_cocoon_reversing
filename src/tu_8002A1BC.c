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


extern struct_obj_B reverbAttr_80091CC8; // really a SpuReverbAttr
extern void UpdateReverb_8002A218(void);
// Matched
void InitReverbTask_8002A1BC(int* p)
{
    reverbAttr_80091CC8.flags_0 = 0;
    SetReverbMode_8002A280(&reverbAttr_80091CC8, 0);
    SetReverbDepth_8002A2A0(&reverbAttr_80091CC8, 0x42, 0x42);
    p[2] = (int)UpdateReverb_8002A218;
}
// Matched
void UpdateReverb_8002A218(void)
{
    if (reverbAttr_80091CC8.flags_0 != 0)
    {
        SpuSetReverbModeParam((SpuReverbAttr*)&reverbAttr_80091CC8);
        if (reverbAttr_80091CC8.flags_0 & 1)
        {
            SetReverbDepth_8002A2A0(&reverbAttr_80091CC8, 0x42, 0x42);
            SpuSetReverbDepth((SpuReverbAttr*)&reverbAttr_80091CC8);
        }
        reverbAttr_80091CC8.flags_0 = 0;
    }
}
// Matched
void SetReverbMode_8002A280(struct_obj_B* p, short a1)
{
    p->flags_0 |= 1;
    p->field_4 = (short)(a1 | 0x100);
}
// Matched
void SetReverbDepth_8002A2A0(struct_obj_B* p, short a1, short a2)
{
    SetReverbDepthLeft_8002A2E8(p, a1);
    SetReverbDepthRight_8002A2FC(p, a2);
}
// Matched
void SetReverbDepthLeft_8002A2E8(struct_obj_B* p, short a1)
{
    p->flags_0 |= 2;
    p->field_8 = a1;
}
// Matched
void SetReverbDepthRight_8002A2FC(struct_obj_B* p, short a1)
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
void DrawTextList_8002A310(struct_entry8* e, int a1)
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
INCLUDE_ASM(DrawTextList_8002A310);
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
extern void DrawWindow_80042460(int a, struct_A384_buf* b, void* c, int d);
// Matched
void DrawUiWindow_8002A384(struct_F1C8* p)
{
    struct_A384_buf buf;
    unsigned char c = p->field_8;
    short col = uiColor_8008B590;
    buf.field_3 = 1;
    buf.field_2 = c;
    buf.color = col;
    DrawWindow_80042460(p->field_0, &buf, &pOT_8008D454[p->field_A], p->field_4);
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
        return (short)dword_800827BC[((struct_12_c*)magicData_8007C438)[a].field_8];
    }
    return 36;
}
extern void sub_800A61CC(int a, void* b, void* c);
extern void AddDrawAreaPrim_8003326C(int a, void* b);
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
        AddDrawAreaPrim_8003326C(a2, &pOT_8008D454[a3]);
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
extern void InterpolateWindowRect_8004196C(void* a0, void* a1, int a2, int a3, int a4);
extern void AddClipDrawAreaPrim_80033308(void* a);
extern void DrawMenuWindowContents_8002A710(void* a, int b);
extern void sub_8002AAF0(struct_A5A4* p, int i, int j, RECT* r);
// Matched
void DrawMenuWindows_8002A5A4(struct_A5A4* p)
{
    RECT r;
    int i;
    int j;
    for (i = 0; p->field_10[i]; i++)
    {
        for (j = 0; !(p->field_10[i][j].flags & 1); j++)
        {
            InterpolateWindowRect_8004196C(&r, p->field_10[i][j].field_10, p->field_8, 8, 0);
            AddClipDrawAreaPrim_80033308(pOT_8008D454 + p->field_14);
            DrawMenuWindowContents_8002A710(&p->field_10[i][j], p->field_14);
            AddDrawAreaPrim_8003326C((int)&r, pOT_8008D454 + p->field_14);
            sub_8002AAF0(p, i, j, &r);
        }
    }
    SetFontClutOffset_8003F900(2, 0);
    SetFontClutOffset_8003F900(1, 0);
}
typedef struct
{
    unsigned short flags;
    unsigned short type;
    int text;
    char** f8;
    char** fC;
    unsigned short x;
    unsigned short y;
    unsigned short w;
    unsigned short h;
    short mx;
    short my;
} MenuItemD;
typedef struct
{
    char pad_0[0x10];
    short f10;
    char pad_12[2];
} Elem20;
typedef struct
{
    char pad_0[8];
} Elem8;
typedef struct
{
    unsigned short x;
    unsigned short y;
} Pt;
extern void sub_8002AC88(int flags, unsigned short* a, short b, unsigned short* out);
extern void AddSprtWithTPage_800331C4(unsigned short* a, char* o, char* b, unsigned long* c, unsigned char* col);
extern int MeasureTextWidthFont1_8003E6B0(int text);
extern int MeasureTextWidth_8003E4C8(int text);
extern void sub_8002FAA0(int a0, unsigned short* pos, int name, int a3);
extern void DrawLargeText_8002FBD8(int a0, unsigned short* pos, int name, int a3);
extern void sub_8003F264(unsigned short* pos, int v, int ot);
extern void sub_8003EFBC(unsigned short* pos, int v, int ot);
extern void DrawLargeNumber_8002C100(unsigned short* pos, int v, int ot);
#if 0
// Not matched (2 words): in case 1 the original loads p->fC before p->text; needs "dword_8007415C 0x48" in config/c_rodata.txt (its jump table)
void DrawMenuWindowContents_8002A710(void* a, int ot)
{
    MenuItemD* p = a;
    unsigned char col[8];
    unsigned short r[4];
    unsigned short loc[2];
    int mode;
    if (p->flags & 0x40)
    {
        return;
    }
    if (p->type == 0)
    {
        return;
    }
    r[0] = p->x + p->mx;
    r[1] = p->y + p->my;
    r[2] = p->w - p->mx * 2;
    r[3] = p->h - p->my * 2;
    switch (p->type)
    {
    case 1:
        if ((unsigned int)p->text < 0xFFFFFFFF)
        {
            sub_8002ACE8(p->flags, col);
            sub_8002AC88(p->flags, r, ((Elem20*)*p->f8)[p->text].f10, loc);
            mode = p->text;
            AddSprtWithTPage_800331C4(loc, (char*)&((Elem20*)*p->f8)[mode], (char*)&((Elem8*)*p->fC)[mode], pOT_8008D454 + ot, col);
        }
        break;
    case 2:
        sub_8002AD08(p->flags);
        sub_8002AC88(p->flags, r, MeasureTextWidthFont1_8003E6B0(p->text), loc);
        mode = 1;
        loc[1] += 2;
        DrawText_8003E91C(mode, p->text, loc, ot);
        break;
    case 3:
        sub_8002AD44(p->flags);
        sub_8002AC88(p->flags, r, MeasureTextWidth_8003E4C8(p->text), loc);
        mode = 2;
        loc[1] += 2;
        DrawText_8003E91C(mode, p->text, loc, ot);
        break;
    case 4:
        sub_8002AD08(p->flags);
        loc[0] = r[0];
        loc[1] = r[1];
        if (p->flags & 4)
        {
            sub_8002FAA0(1, loc, p->text, ot);
        }
        else if (p->flags & 8)
        {
            loc[0] += (short)r[2] / 2;
            sub_8002FAA0(2, loc, p->text, ot);
        }
        else
        {
            sub_8002FAA0(0, loc, p->text, ot);
        }
        break;
    case 5:
        sub_8002AD44(p->flags);
        loc[0] = r[0];
        loc[1] = r[1];
        if (p->flags & 4)
        {
            DrawLargeText_8002FBD8(1, loc, p->text, ot);
        }
        else if (p->flags & 8)
        {
            loc[0] += (short)r[2] / 2;
            DrawLargeText_8002FBD8(2, loc, p->text, ot);
        }
        else
        {
            DrawLargeText_8002FBD8(0, loc, p->text, ot);
        }
        break;
    case 6:
        sub_8002AD08(p->flags);
        loc[0] = r[0] + r[2];
        loc[1] = r[1];
        sub_8003F264(loc, p->text, ot);
        break;
    case 7:
        sub_8002AD44(p->flags);
        loc[0] = r[0] + r[2];
        loc[1] = r[1];
        sub_8003EFBC(loc, p->text, ot);
        break;
    case 8:
        sub_8002AD80(p->flags);
        loc[0] = r[0] + r[2] - 3;
        loc[1] = r[1] + 2;
        DrawLargeNumber_8002C100(loc, p->text, ot);
        SetLargeDigitColor_8002C5D0(0);
        break;
    }
}
#endif
INCLUDE_ASM(DrawMenuWindowContents_8002A710);
