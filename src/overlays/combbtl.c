// COMBBTL.BIN
#include "common.h"
#include "funcs.h"
#include "globals.h"

typedef struct CombBtlTask
{
    unsigned int flags_0;
    int field_4;
    void (*next_8)();
} CombBtlTask;

typedef struct CombBtlNode
{
    unsigned int flags;
} CombBtlNode;

extern CombBtlNode* dword_800A82DC;

typedef struct CombBtl4
{
    int a;
    int b;
    int c;
    int d;
} CombBtl4;

extern short word_800A82E0[4];
extern int* dword_8008B564;
extern int dword_800A85A0;
extern CombBtl4 dword_800A8600;
extern CombBtl4 dword_800A85A8;
extern int dword_800A4078[2];
extern unsigned char byte_800A3A98[2];
extern short word_800A84D0[2];
extern void sub_800A0D1C(int);
extern void sub_800A0B70(int);
extern void StartScreenFlash_8001C02C(void*);
extern void sub_800376A0(int*, int);
typedef struct CombBtlUnit
{
    char pad_0[0xF8];
} CombBtlUnit;

typedef struct CombBtlHist
{
    int a;
    char pad_4[0x10];
} CombBtlHist;

extern CombBtlUnit dword_800A3AA0[2][3];
extern CombBtlHist dword_800A84D8[];
extern int dword_8008D778;
extern void sub_8001A38C();
extern void sub_8001A41C();
extern int sub_800A1958(void*);
extern int sub_800A10DC(int);
extern void sub_800A7EFC();
typedef struct CombBtlObj
{
    int a;
    int b;
    short x;
    short y;
    short w;
    short h;
} CombBtlObj;

typedef struct CombBtlPair
{
    short lo;
    short hi;
} CombBtlPair;

extern short word_800A82D4[][2];
extern void sub_800A7694();
typedef struct CombBtlA24
{
    int w[6];
} CombBtlA24;

typedef struct CombBtlB16
{
    char c[16];
} CombBtlB16;

extern CombBtlA24 dword_800A4AD4;
extern CombBtlB16 dword_800A4AEC;
extern void sub_800A0BA8(int, void*, void*);
typedef struct CombBtlD
{
    unsigned short s0;
    short s2;
    int w[8];
    short s24;
    short s26;
} CombBtlD;

extern CombBtlD dword_800A85C8;
extern int dword_800A85B8;
extern int dword_800A8620;
extern int xarr_800A85B8[];
extern int xarr_800A8620[];
extern CombBtl4 dword_800A8610;
extern int dword_800A84C0;
extern int dword_800A84A0;
extern int dword_800A8498;
extern int dword_800A849C;
extern unsigned char byte_800A38DC;
extern int dword_800A84B8;
extern int dword_800A85F8;
extern short word_800A8488;
extern void sub_800A4C40();
extern void sub_800A4D48();
extern void sub_800A68E0();
extern void sub_800A616C();
extern void sub_800A5000();
extern void sub_80039FA4(int);
extern void sub_800A0A28();
extern int PlayMusic_800300E0(int, int);
extern void sub_800A5EF8();
extern void sub_800A5F60();
extern void sub_800A50E4();
extern void sub_800A5544();
extern void sub_800A5BB4();
extern void sub_800A5080();
extern int dword_800A848C;
extern int dword_800A84D4;
extern int* dword_800A84B0[2];
extern short word_80091CE0[];
extern char dword_80091D40[];
extern short word_800A84A4;
extern short word_800A84A6;
extern short word_800A84BC;
extern short word_800A84C4;
extern short word_800A8470[2];
extern short word_800A8474[2];
extern int dword_800A8480[2];
extern int dword_800A85F0[2];
extern int sub_800CB7AC(void*, int);
extern int sub_800A0B3C(int);
extern void StopSeqSlot_80031334(int);
extern void StopSoundSeqs_80030D68(int);
extern void FreeSeqSlotSound_80030664();
extern void SsSepSetDecrescendo(int, int, int, int);
extern void sub_8001AA50(int);
extern void PlaySeqSlot_80031160(int, int);

INCLUDE_OVERLAY_ASM(combbtl, dword_800A4088);

void sub_800A4B8C(CombBtlTask* t, int a)
{
    dword_800A85A0 = LoadOverlay_80020BF8(1, 6);
    dword_800A84C0 = (unsigned int)gnFrame_8008D610 % 39;
    t->next_8 = sub_800A4C40;
    t->next_8(t, a);
    StopSoundSeqs_80030D68((int)word_80091CE0);
    PlayMusic_800300E0(0, 1);
}

void sub_800A4C40(CombBtlTask* t, int a)
{
    if (GetFileRequestStatus_8003BE30(dword_800A85A0) == 0)
    {
        dword_800A84A0 = -1;
        dword_800A8498 = -1;
        dword_800A849C = -1;
        byte_800A38DC = 2;
        dword_800A85B8 = -1;
        dword_800A8620 = -1;
        sub_80039FA4(dword_800A84C0);
        sub_800A0A28();
        dword_800A84B8 = 0;
        dword_800A85F8 = -1;
        sub_800A4CFC();
        t->next_8 = sub_800A4D48;
        t->next_8(t, a);
    }
}

void sub_800A4CFC()
{
    unsigned int i;
    for (i = 0; i < 2; i++)
    {
        dword_800A4078[i] = -1;
        byte_800A3A98[i] = 0;
        word_800A84D0[i] = 0;
    }
}

extern int LoadSeqSlotSound_800303E8();
extern int IsSoundTaskReady_80030688();
extern int sub_800BC8E8();
extern void sub_800BC878();
extern void sub_80037720();
extern void sub_80037748();
extern void SetFadeMode_8001C19C();
extern void LoadUiTiy_8002BF74();
extern int uiTiyLoaded_8008B4E8;
extern int subInt_800378F8();
extern void sub_800A7290();
extern void sub_800A7420();
extern void sub_800A4EC8();

void sub_800A4D48(CombBtlTask* t, int a)
{
    switch (dword_800A84B8)
    {
    case 0:
        if (!LoadSeqSlotSound_800303E8())
        {
            break;
        }
        dword_800A84B8 = 1;
    case 1:
        if (!IsSoundTaskReady_80030688())
        {
            break;
        }
        FreeBgmAndSfx_800315F4();
        dword_800A84B8 = 2;
    case 2:
        if (!PlayMusic_800300E0(0x99, 1))
        {
            break;
        }
        dword_800A84B8 = 3;
    case 3:
        sub_800BC878();
        dword_800A84B8 = 4;
    case 4:
        if (!sub_800BC8E8())
        {
            break;
        }
        dword_800A84B8 = 5;
    case 5:
        sub_800A7290();
        sub_800A7420();
        sub_80037720();
        sub_80037748();
        dword_800A84B8 = 9;
        break;
    case 6:
        SetFadeMode_8001C19C(3, 0x20);
        dword_800A84B8 = 7;
    case 7:
        LoadUiTiy_8002BF74();
        dword_800A84B8 = 8;
    case 8:
        if (!uiTiyLoaded_8008B4E8)
        {
            break;
        }
        dword_800A84B8 = 9;
    case 9:
        if (subInt_800378F8() != 4)
        {
            t->next_8 = sub_800A4EC8;
            t->next_8(t, a);
        }
        break;
    }
}
INCLUDE_OVERLAY_ASM(combbtl, dword_800A4A54);

extern void sub_800A5638();

void sub_800A4EC8(CombBtlTask* t, int a)
{
    int ok[2];
    unsigned int i;
    unsigned int j;
    for (i = 0; i < 2; i++)
    {
        ok[i] = 1;
        for (j = 0; j < 3; j++)
        {
            if (sub_800A1934(&dword_800A3AA0[i][j]) == 0 && sub_800A1958(&dword_800A3AA0[i][j]) == 0)
            {
                ok[i] = 0;
                break;
            }
        }
        if (ok[i] == 1)
        {
            dword_800A85F8 = i;
            break;
        }
    }
    if (dword_800A85F8 >= 0)
    {
        t->next_8 = sub_800A5000;
    }
    else
    {
        dword_800A84B8 = 10;
        t->next_8 = sub_800A5638;
    }
    t->next_8(t, a);
}

void sub_800A5000(CombBtlTask* t)
{
    if (word_80091CE0[2] >= 0)
    {
        SsSepSetDecrescendo(word_80091CE0[6], word_80091CE0[2], 0x7F, 0x78);
        word_80091CE0[2] = -1;
    }
    StopSeqSlot_80031334(0);
    PlaySeqSlot_80031160(1, 1);
    dword_800A84D4 = 0x78;
    t->next_8 = sub_800A5080;
}

void sub_800A5080(CombBtlTask* t)
{
    if (--dword_800A84D4 <= 0)
    {
        FadeOutSeqSlot_800313C8(0);
        StopSeqSlot_80031334(0);
        StopSoundSeqs_80030D68(dword_80091D40);
        FreeSeqSlotSound_80030664();
        t->next_8 = sub_800A50E4;
    }
}

extern unsigned char byte_800A3A90[];
extern void sub_800A54CC();
extern void sub_800A51EC();
void sub_800A50E4(CombBtlTask* t)
{
    int r = IsEffectTaskIdle_800148D4();
    if (r == 1)
    {
        if (dword_800A85F8 < 0)
        {
            if (byte_800A38DC == r)
            {
                dword_800A85F8 = dword_800A85B8;
                byte_800A3A90[dword_800A85B8]++;
                if (byte_800A3A90[dword_800A85B8] >= 100)
                {
                    byte_800A3A90[dword_800A85B8] = 99;
                }
            }
            else
            {
                t->next_8 = sub_800A54CC;
                return;
            }
        }
        else
        {
            byte_800A38DC = 0;
            byte_800A3A98[dword_800A85F8] = r;
            byte_800A3A90[dword_800A85F8]++;
            if (byte_800A3A90[dword_800A85F8] >= 100)
            {
                byte_800A3A90[dword_800A85F8] = 99;
            }
        }
        t->next_8 = sub_800A51EC;
        dword_800A84D4 = 0x1E;
    }
}

extern void sub_800A8078(short, short, short);
extern int sub_800A8098();
extern void sub_800A5290();
extern void sub_800A54CC();
extern char dword_800A82EC[];
extern char dword_800A8300[];

void sub_800A51EC(CombBtlTask* t)
{
    if (--dword_800A84D4 <= 0)
    {
        if (dword_800A85F8 == 1)
        {
            sub_800A8078(7, 0x3BC, 0x1B);
            dword_800A82DC = sub_800A8098(0, dword_800A82EC, 1);
        }
        else
        {
            sub_800A8078(9, 0x3BF, 0x1F);
            dword_800A82DC = sub_800A8098(0, dword_800A8300, 0);
        }
        t->next_8 = sub_800A5290;
    }
}

typedef struct CombBtlA28
{
    int w[7];
} CombBtlA28;

typedef struct CombBtlBox
{
    short col_0;
    char c_2;
    char c_3;
} CombBtlBox;

extern CombBtlA28 dword_800A4A54;
extern CombBtlA28 dword_800A4A70;
typedef struct CombBtlUi
{
    char pad_0[0x20];
    unsigned short col_20;
} CombBtlUi;

extern CombBtlUi ui_8008B570;
extern void sub_8002ADB4(void*, void*, int, int);

void sub_800A5290(CombBtlTask* t)
{
    CombBtlBox box;
    CombBtlA28 a = dword_800A4A54;
    int pair[2];
    CombBtlA28 b;
    pair[0] = 0x33;
    pair[1] = 0xDF;
    a.w[1] = pair[dword_800A85F8 ^ 1];
    box.c_2 = 1;
    box.c_3 = 1;
    box.col_0 = ui_8008B570.col_20;
    sub_8002ADB4(&a, &box, 0xF, GetTime30Hz_8002C64C());
    b = dword_800A4A70;
    box.c_2 = 1;
    box.c_3 = 1;
    box.col_0 = ui_8008B570.col_20;
    sub_8002ADB4(&b, &box, 0xF, GetTime30Hz_8002C64C());
    if (dword_800A82DC == 0 || (dword_800A82DC->flags & 0x8001) != 1)
    {
        dword_800A82DC = 0;
        t->next_8 = sub_800A54CC;
    }
}

#if 0
// Not matched: the index scaling becomes sllv by the register holding 2 (CSE with kinds[0]); the original shifts by a constant
extern EventEntry* OpenMessageWindow_8003422C(int* cfg);
extern int dword_800A4A8C[];
extern int dword_800A4A94[];
int sub_800A5408(int which, int text, int c)
{
    int cfg[18];
    int kinds[2] = {2, 3};
    int* tbl[2] = {dword_800A4A8C, dword_800A4A94};
    cfg[0] = 2;
    cfg[1] = 0;
    cfg[2] = text;
    cfg[3] = (int)tbl[which];
    cfg[4] = (settingsFlags_8008B58C & 7) != 3;
    cfg[5] = 0;
    cfg[6] = 0;
    cfg[7] = 0;
    cfg[8] = 7;
    cfg[9] = kinds[which];
    cfg[10] = c;
    cfg[11] = 1;
    cfg[12] = 0;
    cfg[13] = 0;
    cfg[14] = (settingsFlags_8008B58C >> 3) & 1;
    cfg[15] = 1;
    cfg[16] = 0;
    return (int)OpenMessageWindow_8003422C(cfg);
}
#endif
INCLUDE_OVERLAY_ASM(combbtl, sub_800A5408);

void sub_800A54CC(CombBtlTask* t)
{
    FadeOutSeqSlot_800313C8(0);
    if (word_80091CE0[2] >= 0)
    {
        SsSepSetDecrescendo(word_80091CE0[6], word_80091CE0[2], 0x7F, 0x78);
        word_80091CE0[2] = -1;
    }
    sub_8001AA50(0x1E);
    sub_800A7BE4();
    t->next_8 = sub_800A5544;
}

extern int sub_8001AB94();
extern void sub_800A73E4();
extern void sub_800A7478();
extern void sub_800A7560();
extern void sub_800A0A6C();
extern void SsUtAllKeyOff();
extern void sub_800A16FC();

void sub_800A5544(CombBtlTask* t)
{
    int i;
    if (sub_8001AB94() == 1)
    {
        sub_800A73E4();
        sub_800A7478();
        for (i = 0; i < 2; i++)
        {
            if (dword_800A4078[i] >= 0)
            {
                if (sub_800A1958(&dword_800A3AA0[i][dword_800A4078[i]]) == 0)
                {
                    sub_800A7560(i);
                }
            }
        }
        sub_800A0A6C();
        FreeSeqSlotSound_80030664();
        SsUtAllKeyOff(0);
        PlayMusic_800300E0(0x8E, 1);
        sub_80039FC0();
        t->next_8 = sub_800A16FC;
    }
}

INCLUDE_OVERLAY_ASM(combbtl, sub_800A5638);

void sub_800A58E8(int i)
{
    CombBtlUnit* u;
    do
    {
        dword_800A4078[i]++;
        if (dword_800A4078[i] >= 3)
        {
            dword_800A4078[i] = 0;
        }
        u = &dword_800A3AA0[i][dword_800A4078[i]];
    } while (sub_800A1934(u) || sub_800A1958(u));
}

#if 0
// Not matched: the original has a jump to the loop increment right after the i == 1 block (one word longer) plus a t0/a3 swap; tried continue/while/switch forms
extern int sub_800A5B70(int a);
extern void sub_800378CC();
extern int dword_8008D610;
extern int dword_800A82E8;
extern unsigned char byte_800A85BD;
extern void sub_800A5C64();
void sub_800A599C(CombBtlTask* t, int a)
{
    int gauge[2];
    int i;
    dword_800A85B8 = -1;
    dword_800A8620 = -1;
    if (word_800A84D0[0] == 0 && word_800A84D0[1] == 0)
    {
        *(short*)((char*)word_800A84D0 + (dword_8008D610 & 2)) += 100;
    }
    for (i = 0; i < 2; i++)
    {
        gauge[i] = (short)sub_800A5B70(i);
    }
    while (dword_800A85B8 < 0)
    {
        for (i = 0; i < 2; i++)
        {
            word_800A84D0[i] += gauge[i];
            if (word_800A84D0[i] >= 1000)
            {
                word_800A84D0[i] -= 1000;
                dword_800A85B8 = i;
                dword_800A8620 = i ^ 1;
                if (i == 1)
                {
                    word_800A84D0[1] += gauge[1];
                }
            }
        }
    }
    if (dword_800A85B8 >= 0)
    {
        void (*f)();
        sub_800378CC();
        dword_800A82E8++;
        byte_800A85BD = dword_800A4078[dword_800A85B8];
        f = sub_800A5C64;
        t->next_8 = f;
        f(t, a);
    }
}
#endif
INCLUDE_OVERLAY_ASM(combbtl, sub_800A599C);

int sub_800A5B70(int a)
{
    int r;
    int v;
    unsigned char buf[0x18];
    r = sub_80014390((a + 8) & 0xFF);
    if (r)
    {
        CalcEquippedStats_80033624(buf, r);
        v = buf[4] + 0xA;
    }
    else
    {
        v = 0;
    }
    return v;
}

// Near miss: the original loads the two shift counts only after all the stores
#if 0
// Not matched: the original loads the two shift counts after all the stores (alias/scheduling), tried array/struct/pointer forms
void sub_800A5BB4()
{
    dword_800A8600.a = 0x14;
    dword_800A8600.b = 0;
    dword_800A85A8.a = 0x14;
    dword_800A85A8.b = 0;
    dword_800A8610.a = 0x14;
    dword_800A8610.b = 0;
    dword_800A85C8.s0 = 0;
    dword_800A85C8.s24 = -1;
    dword_800A85C8.s26 = -1;
    dword_800A85C8.s2 = 0;
    dword_800A85C8.w[0] = 0;
    dword_800A85C8.w[1] = 0;
    dword_800A85C8.w[2] = 0;
    dword_800A85C8.w[3] = 0;
    dword_800A85C8.w[4] = 0;
    dword_800A85C8.w[5] = 0;
    dword_800A85C8.w[6] = 0;
    dword_800A85C8.w[7] = 0;
    dword_800A8600.c = 1 << (xarr_800A85B8[0] + 8);
    dword_800A8600.d = 1 << (xarr_800A8620[0] + 8);
    dword_800A85A8.c = 1 << (xarr_800A85B8[0] + 8);
    dword_800A85A8.d = 1 << (xarr_800A8620[0] + 8);
    dword_800A8610.c = 1 << (xarr_800A8620[0] + 8);
    dword_800A8610.d = 1 << (xarr_800A85B8[0] + 8);
}
#endif
INCLUDE_OVERLAY_ASM(combbtl, sub_800A5BB4);

extern unsigned char byte_800A84A8;
extern unsigned char byte_800A85FC[];
extern int dword_800A8490;
extern void sub_800A5BB4();
extern void sub_800A60F0();
extern void sub_800A5EB8();
extern void name_800BF7C4(void* u, short* a, short* b);
extern int name_800BFA4C(int a, int b);
typedef struct CombBtlActor
{
    int flags;
    int f4;
    short s8;
} CombBtlActor;
void sub_800A5C64(CombBtlTask* t)
{
    CombBtlActor* u;
    int flags0;
    int fl;
    int r;
    sub_800A5BB4();
    word_800A8488 = 0;
    byte_800A84A8 &= 0xFC;
    sub_800A60F0();
    u = (CombBtlActor*)sub_80014390((unsigned char)(dword_800A85B8 + 8));
    flags0 = u->flags;
    name_800BF7C4(u, &word_800A84BC, &word_800A84C4);
    if (word_800A84BC != 0)
    {
        if (word_800A84C4 != 0)
        {
            byte_800A85FC[dword_800A85B8] = 3;
            dword_800A85C8.s0 = 3;
        }
        else
        {
            byte_800A85FC[dword_800A85B8] = 1;
            dword_800A85C8.s0 = 1;
        }
    }
    else if (word_800A8474)
    {
        byte_800A85FC[dword_800A85B8] = 2;
        dword_800A85C8.s0 = 2;
    }
    fl = u->flags;
    r = name_800BFA4C(fl, flags0);
    dword_800A85A8.a = r;
    dword_800A85A8.d = 0;
    if (fl & 0x200)
    {
        t->next_8 = sub_800A68E0;
        word_800A84A6 = 0x6F;
        byte_800A84A8 |= 1;
        dword_800A8490 = dword_800A85B8;
        byte_800A84A8 |= 2;
    }
    else if (u->s8 - word_800A84BC <= 0)
    {
        dword_800A85A8.a = 0xB;
        word_800A84BC = u->s8;
        t->next_8 = sub_800A68E0;
        word_800A84A6 = 0x6F;
        byte_800A84A8 |= 1;
        dword_800A8490 = dword_800A85B8;
    }
    else if (fl & 2)
    {
        t->next_8 = sub_800A4EC8;
    }
    else if (r == 0x14)
    {
        t->next_8 = sub_800A5EB8;
    }
    else
    {
        byte_800A84A8 |= 2;
        t->next_8 = sub_800A68E0;
    }
}

void sub_800A5EB8(CombBtlTask* t)
{
    dword_800A85A0 = LoadOverlay_80020BF8(1, 0x19);
    t->next_8 = sub_800A5EF8;
}

void sub_800A5EF8(CombBtlTask* t)
{
    if (GetFileRequestStatus_8003BE30(dword_800A85A0) == 0)
    {
        sub_800A5BB4();
        dword_800A848C = sub_800CB7AC(&dword_800A8600, dword_800A85B8);
        t->next_8 = sub_800A5F60;
    }
}

void sub_800A5F60(CombBtlTask* t, int a)
{
    if ((*(unsigned int*)dword_800A848C & 0x8001) != 1)
    {
        sub_800A601C();
        if (byte_800A38DC)
        {
            byte_800A3A98[dword_800A85B8] = 2;
            t->next_8 = sub_800A5000;
            t->next_8(t, a);
        }
        else
        {
            sub_800A60A4();
            sub_800A616C();
            word_800A8488 = 0;
            t->next_8 = sub_800A68E0;
        }
    }
}

void sub_800A601C()
{
    int i;
    for (i = 10; i > 0; i--)
    {
        MemCopy_800403E8((unsigned int*)&dword_800A84D8[i], (unsigned int*)&dword_800A84D8[i - 1], 0x14);
    }
    dword_800A84D8[0].a = dword_800A85B8;
    MemCopy_800403E8((unsigned int*)((char*)dword_800A84D8 + 4), (unsigned int*)&dword_800A8600, 0x10);
}

void sub_800A60A4()
{
    int a = dword_800A8600.a;
    dword_800A85A8.a = a;
    dword_800A85A8.b = dword_800A8600.b;
    dword_800A85A8.c = dword_800A8600.c;
    dword_800A85A8.d = dword_800A8600.d;
    if (a == 8)
    {
        dword_800A85A8.a = 3;
        dword_800A85A8.b = 0;
    }
}

void sub_800A60F0()
{
    unsigned int i;
    word_800A84A4 = -1;
    word_800A84A6 = -1;
    word_800A84BC = 0;
    word_800A84C4 = 0;
    for (i = 0; i < 2; i++)
    {
        word_800A8470[i] = 0;
        word_800A8474[i] = 0;
        dword_800A8480[i] = 0;
        dword_800A85F0[i] = 0;
    }
}

INCLUDE_OVERLAY_ASM(combbtl, sub_800A616C);

INCLUDE_OVERLAY_ASM(combbtl, sub_800A68E0);

int sub_800A7164(int i)
{
    int cnt = 0;
    int j;
    for (j = 0; j < 3; j++)
    {
        if (sub_800A1958(&dword_800A3AA0[i][j]) == 0)
        {
            cnt++;
        }
    }
    return cnt;
}

CombBtlPair sub_800A71E4(int n, CombBtlPair* p)
{
    CombBtlPair r;
    short hi = 0;
    short lo = hi;
    int i;
    for (i = 0; i < n; i++)
    {
        p->hi = p->hi - p->lo;
        p->lo = -p->lo;
        if (p->lo < lo)
        {
            lo = p->lo;
        }
        if (hi < p->hi)
        {
            hi = p->hi;
        }
        p++;
    }
    r.lo = lo;
    r.hi = hi;
    return r;
}

#if 0
// Not matched: scheduling/regalloc around the 0x1000 store and the cb_C address (15 words); the flags store only stays ahead of the camera stores with e as int*
extern void ResetCameraToLevant_800376A8(void);
extern void InitCameraTask_800368F8(void);
extern int cameraState_8008D4F0[];
extern int dword_8008B4F8;
extern short dword_8007C2EC[];
extern short dword_8007C30C[];
extern short dword_80087114[];
extern short dword_80087134[];
void sub_800A7290()
{
    int* e = (int*)AllocEventEntry_80043AF8((EventNode*)cameraTask_8008D4A0);
    char* p;
    char* q;
    if (e)
    {
        e[0] = (e[0] | 1) & ~0x8000;
        ResetCameraToLevant_800376A8();
        sub_80037748();
        e[2] = (int)InitCameraTask_800368F8;
        dword_8008B4F8 = 0x1000;
        e[3] = (int)nullsub_5;
        e[0] = (e[0] | 4) & ~0x8000;
        p = (char*)cameraState_8008D4F0;
        *(short*)(p + 0x2E) = 0;
        *(int*)(p + 0x20) = 0;
        *(int*)(p + 0x24) = 0;
        *(int*)(p + 0x28) = 0;
        *(int*)(p + 0x14) = 0;
        *(int*)(p + 0x18) = 0;
        *(int*)(p + 0x1C) = 0;
        *(short*)(p + 0x34) = 0;
        *(short*)(p + 0x36) = 0;
        *(short*)(p + 0x38) = 0;
        *(short*)(p + 0x3C) = 0;
        *(short*)(p + 0x3E) = 0;
        *(short*)(p + 0x40) = 0;
        q = (char*)&saveData_8008B570;
        *(int*)(q + 0x7A8) = 0;
        *(int*)(q + 0x7AC) = 0;
        *(int*)(q + 0x7B0) = 0;
        *(short*)(q + 0x7B4) = 0;
        *(short*)(q + 0x7B6) = 0;
        *(short*)(q + 0x7B8) = 0;
        *(short*)(p + 0x34) = dword_8007C2EC[0];
        *(short*)(p + 0x36) = dword_8007C2EC[1];
        *(short*)(p + 0x38) = dword_8007C2EC[2];
        *(short*)(p + 0x3C) = dword_8007C30C[0];
        *(short*)(p + 0x3E) = dword_8007C30C[3];
        *(short*)(p + 0x40) = dword_8007C30C[6];
        dword_80087114[0] = dword_8007C2EC[0];
        dword_80087114[1] = dword_8007C2EC[1];
        dword_80087114[2] = dword_8007C2EC[2];
        dword_80087134[0] = dword_8007C30C[0];
        dword_80087134[3] = dword_8007C30C[3];
        dword_80087134[6] = dword_8007C30C[6];
    }
}
#endif
INCLUDE_OVERLAY_ASM(combbtl, sub_800A7290);

void sub_800A73E4()
{
    sub_800376A0((int*)cameraTask_8008D4A0 + 4, cameraTask_8008D4A0[9]);
    StopAllEventEntries_80043B40((int*)cameraTask_8008D4A0);
}

void sub_800A7420()
{
    EventEntry* e = AllocEventEntry_80043AF8((EventNode*)dword_8008D628);
    if (e)
    {
        e->flags = (e->flags | 1) & ~0x8000;
        sub_8001A38C();
        e->cb_8 = (EventEntryFn)sub_8001A41C;
    }
}

void sub_800A7478()
{
    StopAllEventEntries_80043B40((int*)dword_8008D628);
}

void sub_800A74A0(int i)
{
    CombBtlA24 a = dword_800A4AD4;
    CombBtlB16 b = dword_800A4AEC;
    sub_800A0BA8(i, (char*)&a + i * 12, (char*)&b + i * 8);
}

void sub_800A7560(int a)
{
    sub_800A0D1C(a);
    sub_800A0B70(a);
}

int sub_800A758C()
{
    unsigned int i;
    for (i = 0; i < 2; i++)
    {
        if (dword_800A84B0[i])
        {
            if (sub_800A0B3C(i) == 0)
            {
                return 0;
            }
        }
    }
    return 1;
}

void sub_800A75F8(int a)
{
    EventEntry* e = AllocEventEntry_80043AF8((EventNode*)dword_8008B564);
    CombBtlObj* p;
    if (e)
    {
        e->flags = (e->flags | 1) & ~0x8000;
        p = (CombBtlObj*)e->buffer;
        p->a = a;
        p->b = 0;
        p->x = word_800A82D4[a][0];
        p->y = word_800A82D4[a][1];
        p->w = 0x64;
        p->h = 0x29;
        e->cb_8 = (EventEntryFn)sub_800A7694;
    }
}

INCLUDE_OVERLAY_ASM(combbtl, sub_800A7694);

void sub_800A7BE4()
{
    StopAllEventEntries_80043B40(dword_8008B564);
}

extern unsigned char byte_800A38D8;
extern void sub_80037BFC(int a);
extern void StartPadVibration_80036528(int pad, int kind);
extern void sub_800A7E34(int a, int b, int c);
extern void sub_800A7ECC();
void sub_800A7C0C(int side)
{
    int me;
    int other;
    if (side == 0)
    {
        other = byte_800A38D8;
        me = 0;
    }
    else
    {
        me = byte_800A38D8;
        other = 0;
    }
    switch (dword_800A85C8.s0)
    {
    case 0:
        break;
    case 1:
        sub_800A7E34(side, dword_800A85C8.s0, word_800A8470[side]);
        if (word_800A8470[side] > 0)
        {
            sub_80037BFC(0x1E);
            StartPadVibration_80036528(me, 0);
            StartPadVibration_80036528(other, 2);
        }
        break;
    case 2:
        sub_800A7E34(side, dword_800A85C8.s0, word_800A8474[side]);
        if (word_800A8474[side] > 0)
        {
            sub_80037BFC(0x1E);
            StartPadVibration_80036528(side ? byte_800A38D8 : 0, 0);
        }
        break;
    case 3:
        sub_800A7E34(side, 1, word_800A8470[side]);
        sub_800A7E34(side, 2, word_800A8474[side]);
        if (word_800A8470[side] > 0 || word_800A8474[side] > 0)
        {
            sub_80037BFC(0x1E);
            StartPadVibration_80036528(side ? byte_800A38D8 : 0, 0);
        }
        break;
    case 4:
        sub_800A7E34(side, 1, word_800A8470[side]);
        sub_80037BFC(0x1E);
        StartPadVibration_80036528(side ? byte_800A38D8 : 0, 1);
        sub_800A7ECC();
        break;
    case 5:
        StartPadVibration_80036528(0, 0x26);
        break;
    }
}

void sub_800A7E34(int a, int b, int c)
{
    EventEntry* e = AllocEventEntry_80043AF8((EventNode*)dword_8008D778);
    int* p;
    if (e)
    {
        e->flags = (e->flags | 1) & ~0x8000;
        p = (int*)e->buffer;
        p[0] = b;
        p[2] = 0;
        p[1] = c;
        p[6] = a;
        p[4] = sub_800A10DC(a);
        e->cb_8 = (EventEntryFn)sub_800A7EFC;
    }
}

void sub_800A7ECC()
{
    unsigned char c[3];
    c[0] = 0xFF;
    c[1] = 0xFF;
    c[2] = 0xFF;
    StartScreenFlash_8001C02C(c);
}

extern void sub_800127D0(int a, int b, int c, int d);
void sub_800A7EFC(EventEntry* e, int* buf)
{
    int* p = buf;
    DVECTOR sxy;
    SVECTOR v;
    long z;
    long flag;
    int d;
    v.vx = ((int*)buf[4])[0];
    v.vy = ((int*)buf[4])[1];
    v.vz = ((int*)buf[4])[2];
    v.vx -= dword_8008D600[0].field_0;
    v.vy -= dword_8008D600[1].field_0;
    v.vz -= dword_8008D600[2].field_0;
    RotTransPers(&v, (long*)&sxy, &z, &flag);
    if (++p[2] > 16)
    {
        e->flags = (e->flags & ~1) | 0x8000;
        return;
    }
    d = p[1] / (17 - p[2]);
    d = -d;
    p[1] += d;
    if (p[0] == 1)
    {
        int r = sub_80014390((unsigned char)(p[6] + 8));
        sub_800127D0(p[6] + 8, 0, d, 0);
        if (*(short*)(r + 8) <= 0)
        {
            sub_800127B8((struct_obj_B*)sub_80014390((unsigned char)(p[6] + 8)));
        }
    }
    else if (p[0] == 2)
    {
        sub_800127D0(p[6] + 8, 2, d, 0);
    }
}

void sub_800A8078(short a, short b, short c)
{
    word_800A82E0[0] = 1;
    word_800A82E0[1] = a;
    word_800A82E0[2] = b;
    word_800A82E0[3] = c;
}

extern int** dword_8008D458;
extern int dword_800A8478;
extern unsigned int dword_800A3A88;
extern int sub_800A5408();
extern void sub_800A816C();

int sub_800A8098(int a, int b, int c)
{
    EventEntry* e = AllocEventEntry_80043AF8((EventNode*)dword_8008D458);
    if (e)
    {
        e->cb_8 = (EventEntryFn)sub_800A816C;
        e->flags = (e->flags | 1) & ~0x8000;
        XaRequestPlay_80043564(word_800A82E0[1], word_800A82E0[2], word_800A82E0[3]);
        dword_800A8478 = sub_800A5408(a, b, c);
        dword_800A3A88 &= ~4;
        dword_800A3A88 &= ~8;
        dword_800A3A88 &= ~0x10;
    }
    return (int)e;
}

extern int sub_800349B4();
extern int XaRequestStop_80043524();
extern void sub_80034A84();

void sub_800A816C(EventEntry* e)
{
    int buf[4];
    int v;
    if (!(dword_800A3A88 & 4))
    {
        if (sub_800349B4(dword_800A8478, buf) && buf[3])
        {
            dword_800A3A88 |= 4;
        }
    }
    v = XaNoRequestPending_800435A4();
    if (v == 1 && XaIsIdle_80043584() == v)
    {
        dword_800A3A88 |= 8;
    }
    if (!(dword_800A3A88 & 8))
    {
        v = (settingsFlags_8008B58C >> 3) & 1;
        if (v == 1 && (dword_800A3A88 & 4))
        {
            if (!(dword_800A3A88 & 0x10))
            {
                if (XaRequestStop_80043524() == v)
                {
                    dword_800A3A88 |= 0x10;
                }
            }
        }
    }
    if ((dword_800A3A88 & 0xC) == 0xC)
    {
        dword_800A3A88 &= ~4;
        dword_800A3A88 &= ~8;
        dword_800A3A88 &= ~0x10;
        sub_80034A84(dword_800A8478);
        e->flags = (e->flags & ~1) | 0x8000;
    }
}

INCLUDE_OVERLAY_ASM(combbtl, dword_800A82D0);
