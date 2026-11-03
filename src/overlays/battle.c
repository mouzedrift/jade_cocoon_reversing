// BATTLE.BIN
#include "common.h"
#include "funcs.h"
#include "globals.h"

extern unsigned char dword_800C8B30;
extern int sub_800A2AB4();
extern void sub_80018430(int a);
extern int sub_800AD8E4();
extern void InterpolateWindowRect_8004196C(void* a0, void* a1, int a2, int a3, int a4);
extern void AddDrawAreaPrim_8003326C();
extern void AddClipDrawAreaPrim_80033308();
extern unsigned short padPressed_8009194C;
extern int MeasureTextWidth_8003E4C8();
extern int dword_800C9E38;
extern unsigned char dword_800C9E68;
extern unsigned char dword_800C9E40;
extern unsigned char dword_800C9E72[];
extern unsigned char dword_800C9E80[];
extern unsigned char dword_800C9E4A;
extern int dword_800C9E4C;
extern int dword_800C9E78;
extern int dword_800C9E58[];
extern void sub_8004D1EC(int a0, int a1, int a2, int a3, int a4, int a5, int a6);
extern char stru_8008D534[];
extern unsigned char dword_800C9E49;
typedef struct BatMenu_a
{
    short f0;
    short f2;
    unsigned short count_4;
    unsigned short flags_6;
    short cursor_8;
    short scroll_A;
} BatMenu_a; // same layout as the exe's MenuCursor

extern BatMenu_a dword_800C92D8[1];
extern BatMenu_a dword_800C92E4[1];
extern BatMenu_a dword_800C92F0[1];
extern BatMenu_a dword_800C9308[1];
extern BatMenu_a dword_800C9314[1];
extern BatMenu_a dword_800C9320[1];
extern BatMenu_a dword_800C932C[1];

extern int dword_800C8B34;
extern int dword_800C9DD0[];

typedef struct BatTask
{
    int f0;
    int f4;
    int* f8;
    int fC;
    int f10;
    unsigned char* f14;
    int f18;
} BatTask;

extern void sub_800C6AFC(BatTask* t, int a, int b);
extern unsigned char dword_800C9E54;
extern int dword_800C9E3C;
extern unsigned char dword_800C9E51;
extern unsigned char dword_800C9E48;
extern unsigned char dword_800C9E50;
extern int dword_800C9E7C;
extern int sub_800BE364();
extern void sub_800BE3C0();
extern int sub_800BEA94();

typedef struct BatMin_a
{
    unsigned int f0;
    int f4;
    short h8;
} BatMin_a;

extern int sub_800BC6CC();
extern void FadeOutSeqSlot_800313C8(int);

extern EventNode* dword_8008D624;
extern char dword_800C9D82;
extern char dword_800C9D83;
extern char dword_800C9D56;
extern int dword_800C9C58;
extern int sub_800A5354();
extern int sub_800BAAD8();
extern void sub_800A1F80();
extern void sub_800A8D0C();
extern void sub_800A096C();
extern void sub_800BAC4C();

extern char dword_800C912C[];
extern int sub_800A2C28();
extern int sub_800BEB50();
extern int sub_800BEB68();
extern int sub_800BF47C();
extern int sub_800BC784();

typedef struct BatV12_a
{
    int x;
    int y;
    int z;
} BatV12_a;

extern unsigned int dword_800B122C;
extern int dword_800ADE88;
extern int sub_800C0D60();
extern int sub_800A89F0();
extern int sub_800A2550();
extern int IsEffectTaskIdle_800148D4();
extern int sub_800C09D4();
extern int sub_800B4318();
extern void Midpoint3D_8003B95C();
extern void sub_800BAE74();
extern void sub_800BC850(unsigned int);

extern char dword_80091D40[];
extern int dword_800ADE78;
extern int dword_80091C74;
extern int dword_8007DC74;
extern int dword_800C9188;
extern short dword_80091CE0[];
extern void sub_800B42A8();
extern void sub_800A2618();
extern int StartBattleMenu_800C6EFC();
extern void sub_800BB940();
extern void sub_800A1B78();
extern void FreeActiveOverlay_8002C014();
extern void sub_800AC708();
extern void sub_800A9364();
extern int sub_800A8DAC();
extern int sub_800A1B2C();
extern void ReviveOneHp_80011CF4();
extern void SsSepSetDecrescendo();
extern void sub_800BA848();
extern void sub_800BA4F4();
extern void sub_800C064C();
extern void StartModelTask_80010850();
extern int sub_800BF784();
extern void sub_800BC468();

typedef struct BatEnt_a
{
    int a;
    short b;
    short c;
    short d;
    short e;
} BatEnt_a;

typedef struct BatCol_a
{
    unsigned char r;
    unsigned char g;
    unsigned char b;
    unsigned char a;
} BatCol_a;

extern int dword_800B1230;
extern BatEnt_a dword_800B1238[];
extern short dword_800C9C68[];
extern unsigned char dword_800C9C82;
extern unsigned char dword_800C9C99;
extern short dword_800C9D38[];
extern short dword_800C9D48[];
extern char dword_800C9CBC[];
extern int dword_800C9D58[];
extern int dword_800C9CA0[];
extern short dword_800C9D78;
extern short dword_800C9D80;
extern short dword_800C9C7E;
extern short dword_800C9C80;
extern int dword_800C9D90;
extern short dword_800C9DBC;
extern short dword_800C9DC0[];
extern short dword_800C9D8C[2];
extern EventNode* dword_8008B4C0;
extern int dword_800ADE88;
extern int eventDispatchHalt_8008B540;
extern int dword_80083BD0;
typedef struct BatRow_a
{
    int a;
    unsigned short b;
    short c;
    int d;
    int e;
} BatRow_a;

extern BatRow_a dword_800C8EAC[];
extern int sub_80034AB8();
extern int sub_800349B4();
extern void sub_80034A84();
extern void sub_8001E28C();
extern void sub_800A2924();
extern void ClearStatus_80011C30();
extern void RecoverQuarterHpMp_80011C44();
extern void memset();
extern void LoadEffectFile_80020DDC();
extern void SetFadeMode_8001C19C();
extern void sub_800A2AE8();
extern void PlaySeqSlot_80031160();
extern void sub_80018A4C();
extern int LoadOverlay_80020BF8();
extern void sub_8001AAF4();
extern void sub_800A8D48();
extern void sub_800A25D8();
extern int sub_800A2BE4();
extern int sub_800BF6BC();
extern int sub_800BC378();
extern int sub_800BDE04();
extern int sub_800BC570();
extern int sub_800BC7DC();
extern void sub_800BC4D4();
extern void sub_800BF770();
extern void sub_800BC838();
extern void sub_800BA624();
extern void sub_800BA6A0();
extern void sub_800BA788();
extern void sub_800BA720();
extern void sub_800BAE74();
extern void sub_800BB1B0();
extern void sub_800BB168();
extern void sub_800BB380();
extern void sub_800BBC84();
extern void sub_800BDC3C();
extern void sub_800BF4D0();
extern void sub_800C0254();
extern void sub_800BBDB4();
extern void sub_800C0DB0();
extern void sub_800BC324();
extern void sub_800BBE7C();
extern char levantStatus_8008BD38[];

typedef struct BatObj_a
{
    int f0;
    int f4;
    void (*next_8)();
    int fc;
} BatObj_a;

typedef struct BatPair_a
{
    short a;
    short b;
} BatPair_a;

extern BatPair_a dword_800C9DA0[];
extern int* dword_8008B568;
extern int* dword_8008B564;
extern EventNode* dword_8008D4B0;
extern EventNode* dword_8008D63C;
extern EventNode* dword_8008D778;
extern int dword_800C9D74;
extern int dword_800C9D7C;
extern short effectOutcomeFlag_8008D780;
extern void sub_800BBA70();
extern void sub_800BBE00();
extern void sub_800BC05C();
extern void sub_800BBF64();
extern void sub_800BDA28();
extern void sub_800BDBB0();
extern void sub_800C04A4();
extern int sub_800BDD3C();
extern void sub_800BF2E8();
extern void sub_800BDEBC();
extern void sub_800BDF74();
extern void sub_800BDFAC();
extern void sub_800BE2C8();
extern int sub_800C0A9C();
extern int sub_800C0D50();

typedef struct BatTask_a
{
    int f0;
    int f4;
    void (*next_8)();
    int* fc;
} BatTask_a;

typedef struct BatSlot_a
{
    int a;
    int b;
    int c;
    int d;
} BatSlot_a;

extern short levantPos_8008BD18[];
extern unsigned int dword_800B1228;
typedef struct BatCtx_a
{
    char* obj;
    int f4;
    int f8;
    int fc;
    int f10;
} BatCtx_a;

extern BatCtx_a dword_800C9190;
extern int dword_800C918C;
extern signed char dword_800C9D84;
extern short dword_800C9D94;
extern short dword_800C9D9A;
extern short dword_800C9D98[];
extern int dword_800C9170;
extern int dword_800C9174[3];
extern char dword_800C9DFC;
extern char dword_800C9DFD;
extern int dword_800C9C88[4];
extern unsigned char dword_800C9C7C;
extern unsigned char dword_800C9C98;
extern int dword_800C8B54[];
extern char dword_800C8B38[];
extern int dword_800C9CC8[];
extern int sub_8001AB94(void*);
extern int sub_800A89F0();
extern void sub_800BA624();
extern void sub_800BB894();
extern void sub_800BBCC8();
extern void sub_800BC144();
extern void sub_800BC850(unsigned int);
extern int sub_800BC28C();
extern int sub_800BC1A8();
extern struct BatPair_a* sub_800BE058();
extern void sub_800BFC10();
extern void sub_800BFC40();
extern void sub_800C01D8();
extern void sub_800C0440();
extern int sub_800C0BA0();
extern int sub_800C0AEC();
extern void sub_800BB794();
extern int sub_800C0F78(int);
extern void StartScreenFlash_8001C02C(void*);
extern void sub_8001DB00(char*, int, int);
extern void sub_80018E5C(char*, int);
extern void sub_80018EBC(char*, int);
extern int sub_8001E1DC(void*);
extern int sub_800C0D88();
extern int sub_800A8BE4();
extern int sub_800A2594();

INCLUDE_OVERLAY_ASM(battle, dword_800B66C0);

INCLUDE_OVERLAY_ASM(battle, sub_800BA254);

void sub_800BA444(BatTask_a* t)
{
    int r = sub_8001AB94(t);
    if (r == 1)
    {
        sub_800A9364();
        if (sub_800A8DAC() == r)
        {
            ReviveOneHp_80011CF4(levantStatus_8008BD38);
            t->next_8 = sub_800BA4F4;
            if (sub_800BC820(0x20000) == 0)
            {
                FadeOutSeqSlot_800313C8(0);
            }
            else
            {
                short* p = dword_80091CE0;
                if (p[2] >= 0)
                {
                    SsSepSetDecrescendo(p[6], p[2], 0x7F, 0x78);
                    p[2] = -1;
                }
            }
        }
    }
}

void sub_800BA4F4(BatTask_a* t)
{
    if (sub_8001AB94(t) == 1)
    {
        t->next_8 = sub_800BA624;
    }
}

void sub_800BA52C(BatTask_a* t)
{
    if (sub_800A89F0(t) == 1)
    {
        t->next_8 = sub_800BA624;
    }
}

void sub_800BA564(BatTask_a* t, BatObj_a* u)
{
    int r = sub_800A8DAC();
    if (r == 1)
    {
        if (sub_800A1B2C() == r)
        {
            if (--u->f4 < 0)
            {
                if (sub_800BC820(0x20000) == 0)
                {
                    FadeOutSeqSlot_800313C8(0);
                }
                else
                {
                    short* p = dword_80091CE0;
                    if (p[2] >= 0)
                    {
                        SsSepSetDecrescendo(p[6], p[2], 0x7F, 0x78);
                        p[2] = -1;
                    }
                }
                t->next_8 = sub_800BA624;
            }
        }
    }
}

void sub_800BA624(BatTask_a* t, BatObj_a* u)
{
    SetFadeMode_8001C19C(0, 0x20);
    SetFadeMode_8001C19C(1, 0x20);
    sub_8001AAF4();
    if (dword_800B1230 == 2)
    {
        u->f4 = 0x1E;
        t->next_8 = sub_800BA6A0;
    }
    else
    {
        t->next_8 = sub_800BA788;
    }
}

void sub_800BA6A0(BatTask_a* t, BatObj_a* u)
{
    eventDispatchHalt_8008B540 = 1;
    SetFadeMode_8001C19C(0, 0x20);
    if (--u->f4 <= 0)
    {
        if (dword_800B1230 == 2)
        {
            sub_800BA720();
        }
        t->next_8 = sub_800BA788;
    }
}

void sub_800BA720()
{
    int m = sub_800A248C();
    int i;
    int mask;
    for (i = 0; i < 3; i++)
    {
        mask = 1 << (i + 4);
        if (m & mask)
        {
            sub_800A2924(i);
        }
    }
}

void sub_800BA788(BatTask_a* t)
{
    SetFadeMode_8001C19C(0, 0x20);
    sub_800C0BA0();
    sub_800A1B78();
    FreeActiveOverlay_8002C014();
    sub_80039FC0();
    StopSoundSeqs_80030D68(dword_80091D40);
    StopSeqSlot_80031334(0);
    FreeSeqSlotSound_80030664();
    SsUtAllKeyOff(0);
    PlayMusic_800300E0(sub_800315E4(), 1);
    LoadLoaderModelAnimSets_80020898();
    if (dword_80091C74 >= 0)
    {
        sub_800AC708(dword_80091C74, 1);
    }
    eventDispatchHalt_8008B540 = 1;
    t->next_8 = sub_800BA848;
}

extern int sub_800AC768();
extern void sub_800A1F0C();
extern void sub_800A9384(int a);
extern void sub_800A8DCC();
extern void sub_800A89C8();
extern void sub_800A1E1C();
extern void sub_800A094C();
extern void sub_800A5FAC();
extern void sub_800A14E0();
extern void sub_800A15FC();
extern int dword_80091C9C;
void sub_800BA848(BatTask_a* t, BatObj_a* u)
{
    SetFadeMode_8001C19C(0, 0x20);
    if (AreLoaderModelsLoaded_80020924() && sub_800AC768())
    {
        sub_800A1F0C();
        sub_80037770();
        sub_800A9384(1);
        sub_800A8DCC();
        sub_800A89C8();
        sub_800A1E1C();
        sub_800BA97C();
        sub_800A094C();
        if ((dword_800B1230 == 0 || dword_800B1230 == 2) && u->fc == 1)
        {
            u->f0 = LoadOverlayIfChanged_80020D1C(1, 7);
            t->next_8 = sub_800A14E0;
        }
        else if (dword_800B1230 == 3)
        {
            sub_800A9364();
            sub_800A5FAC();
            if (dword_80091C9C == 0)
            {
                sub_80027314();
            }
            t->next_8 = sub_800A15FC;
        }
        else
        {
            sub_80027314();
            t->next_8 = sub_800A15FC;
        }
    }
    eventDispatchHalt_8008B540 = 1;
}

void sub_800BA97C()
{
    int n;
    int i;
    ClearStatus_80011C30(levantStatus_8008BD38);
    n = CountMinions_80010548(3);
    for (i = 0; i < n; i++)
    {
        RecoverQuarterHpMp_80011C44(GetMinionStatus_800107A0(3, i));
    }
}

EventEntry* sub_800BA9E4()
{
    EventEntry* e = AllocEventEntry_80043AF8(dword_8008D624);
    char buf[0x10];
    int r;
    if (e)
    {
        e->flags = (e->flags | 1) & 0xFFFF7FFF;
        e->cb_8 = (EventEntryFn)sub_800BAC4C;
        r = sub_800A5354();
        dword_800C9D82 = r;
        dword_800C9D84 = r;
        dword_800C9D83 = r;
        sub_800BF648(dword_800C9C68, sub_800BAAD8());
        dword_800B1228 = 0;
        sub_800BC838(0x80000);
        dword_800C9D56 = 0;
        dword_800C9C7C = 0;
        dword_800C9C99 = 0;
        dword_800C9C82 = 0;
        dword_800B122C = 0;
        sub_800A1F80();
        sub_800BC378(sub_800A248C(), buf);
        sub_800A8D0C(buf);
        sub_800BABC4();
        dword_800C9C58 = 0;
        sub_800A096C();
    }
    return e;
}

extern short sinTable_80084540[];
extern int sub_800A1E48(void);
extern int sub_800A1E68(void);

int sub_800BAAD8()
{
    int* sd = (int*)&saveData_8008B570;
    int px = sd[0x7A8 / 4];
    int pz = sd[0x7B0 / 4];
    short ang = *(unsigned short*)((char*)sd + 0x7B6);
    int x = *(int*)sub_800A1E48();
    int z = ((int*)sub_800A1E48())[2];
    short* rot = (short*)sub_800A1E68();
    int a;
    if (sinTable_80084540[(ang - rot[1] + 0x400) & 0xFFF] >= 0)
    {
        a = ratan2_8003B548(x - px, z - pz);
        if (sinTable_80084540[(a - ang + 0x400) & 0xFFF] >= 0)
        {
            return 1;
        }
        return 2;
    }
    return 0;
}

#if 0 // Not matched: goto loop gets the body right but i++ is scheduled ahead of the stores (original: after them, li -1 in the branch delay slot)
void sub_800BABC4()
{
    int i;
    int m;
    BatEnt_a* p;
    i = 0;
    p = dword_800B1238;
loop: // a for loop hoists the constants (-1, 7, 1) out of the loop; the original keeps them inside
    m = sub_800A248C() & (1 << (i + 4));
    if (m != 0)
    {
        sub_800A2BE4(i);
    }
    p->b = -1;
    p->a = 0;
    p->d = 0;
    p->c = 0;
    p->e = 7;
    i++;
    p++;
    if (i < 3)
    {
        goto loop;
    }
}
#endif
INCLUDE_OVERLAY_ASM(battle, sub_800BABC4);

extern int LoadSeqSlotSound_800303E8();
extern int IsSoundTaskReady_80030688();
extern void sub_80037748();
extern void LoadUiTiy_8002BF74();

extern void sub_800BFB80();
void sub_800BAC4C(BatTask_a* t)
{
    int k;
    int m;
    switch (dword_800C9C58)
    {
    case 0:
        if (LoadSeqSlotSound_800303E8() == 0)
        {
            break;
        }
        dword_800C9C58 = 1;
    case 1:
        if (IsSoundTaskReady_80030688() == 0)
        {
            break;
        }
        k = sub_800A2BE4(0);
        if (sub_800BF980(k))
        {
            sub_800BC838(0x20000);
            if (k == 0x37)
            {
                m = 0x92;
            }
            else if (k == 0x32)
            {
                m = 0x23;
            }
            else
            {
                m = 0x24;
            }
            if (PlayMusic_800300E0(m, 1) == 0)
            {
                break;
            }
        }
        else
        {
            sub_800BC850(0x20000);
            FreeBgmAndSfx_800315F4();
            PlaySeqSlot_80031160(0, 1);
        }
        dword_800C9C58 = 2;
    case 2:
        sub_800BC878();
        dword_800C9C58 = 3;
        break;
    case 3:
        if (sub_800BC8E8() == 0)
        {
            break;
        }
        dword_800C9C58 = 4;
    case 4:
        if (IsFadeDone_8001C2FC() == 0)
        {
            break;
        }
        SetFadeMode_8001C19C(3, 0x20);
        sub_80037748();
        dword_800C9C58 = 5;
    case 5:
        if (((int (*)())sub_8001AB94)() == 0) // called without its argument here
        {
            break;
        }
        dword_800C9C58 = 6;
    case 6:
        LoadUiTiy_8002BF74();
        dword_800C9C58 = 7;
    case 7:
        if (uiTiyLoaded_8008B4E8 == 0)
        {
            break;
        }
        sub_800BFB80();
        dword_800C9C58 = 8;
    case 8:
        if (GetCameraMode_800378F8() >= 4u)
        {
            t->next_8 = sub_800BAE74;
        }
        break;
    }
}
INCLUDE_OVERLAY_ASM(battle, dword_800B6700);

int sub_800BAE10()
{
    if (sub_800BC820(4) == 1 || sub_800BC820(0x80) == 1)
    {
        return 1;
    }
    if (sub_800BC820(2) == 1)
    {
        return 0;
    }
    return sub_800A248C() == 0;
}

INCLUDE_OVERLAY_ASM(battle, sub_800BAE74);

void sub_800BB100(BatTask_a* t, BatObj_a* u)
{
    int buf[4];
    if (sub_800349B4(u->fc, buf) && buf[3])
    {
        sub_80034A84(u->fc);
        t->next_8 = sub_800BB168;
    }
}

void sub_800BB168(BatTask_a* t, BatObj_a* u)
{
    if (sub_80034AB8(u->fc) == 0)
    {
        dword_800ADE88 = -1;
        t->next_8 = sub_800BAE74;
    }
}

#if 0 // Not matched: prologue scheduling only: 'li a0,4' lands after 'move s2,a1' (original: before); tried param types, store order
extern void sub_800BFBB8();
void sub_800BB1B0(BatTask_a* t, BatObj_a* u)
{
    if (sub_800BC820(4) == 1)
    {
        sub_800BC850(4);
        dword_800B1230 = 3;
    }
    else if (sub_800BC820(0x80) == 1)
    {
        sub_800BC850(0x80);
        dword_800B1230 = 2;
    }
    else if (sub_800BC820(0x100) == 1)
    {
        if (dword_800C9C82 != 0)
        {
            dword_800C9C7C = dword_800C9C82;
            dword_800C9C88[0] = 3;
            dword_800C9C88[1] = 0;
            dword_800C9C88[3] = 0;
            dword_800C9C88[2] = 1 << dword_800C9C7C;
            t->next_8 = (void (*)())sub_800BC174();
            u->f4 = (int)sub_800BB1B0;
            u->next_8 = sub_800BB1B0;
            return;
        }
        if (sub_800BC820(0x2000) == 1)
        {
            dword_800B1230 = 5;
        }
        else
        {
            dword_800B1230 = 4;
        }
        sub_800BC850(0x100);
    }
    else
    {
        if (sub_800A248C() != 0)
        {
            return;
        }
        if (sub_800BC820(0x40) == 1)
        {
            dword_800B1230 = 0;
        }
        else
        {
            dword_800B1230 = 1;
        }
    }
    sub_800BFBB8();
    t->f0 = (t->f0 & ~1) | 0x8000;
}
#endif
INCLUDE_OVERLAY_ASM(battle, sub_800BB1B0);

void sub_800BB314(BatTask_a* t)
{
    if (dword_800C9C7C == 7)
    {
        dword_800C9C7C = sub_800BF6BC(dword_800C9C68, dword_800C9C82);
    }
    t->next_8 = sub_800BB380;
    dword_800C9C99 = dword_800C9C82;
}

INCLUDE_OVERLAY_ASM(battle, sub_800BB380);

void sub_800BB74C()
{
    dword_800C9C88[0] = 0x14;
    dword_800C9C88[1] = 0;
    dword_800C9C88[3] = 0;
    dword_800C9C88[2] = 1 << dword_800C9C7C;
    sub_800BB794();
}

void sub_800BB794()
{
    int i;
    for (i = 0; i < 7; i++)
    {
        ((BatSlot_a*)dword_800C9CC8)[i].a = 0x14;
        ((BatSlot_a*)dword_800C9CC8)[i].b = 0;
        ((BatSlot_a*)dword_800C9CC8)[i].c = 1 << i;
        ((BatSlot_a*)dword_800C9CC8)[i].d = 0;
    }
}

void sub_800BB7D4()
{
    int i;
    dword_800C9D78 = -1;
    dword_800C9D80 = -1;
    dword_800C9C7E = 0;
    dword_800C9C80 = 0;
    for (i = 0; i < 7; i++)
    {
        dword_800C9D38[i] = 0;
        dword_800C9D48[i] = 0;
        dword_800C9CBC[i] = 0;
        dword_800C9D58[i] = 0;
        dword_800C9CA0[i] = 0;
    }
}

void sub_800BB860(BatTask_a* t)
{
    sub_800BC850(0x80000);
    t->next_8 = sub_800BB894;
}

void sub_800BB894(BatTask_a* t, BatObj_a* u)
{
    if (dword_800C9C7C >= 4)
    {
        if (dword_800ADE78 == 1)
        {
            sub_800B42A8(dword_800C9C88, &dword_800ADE78);
        }
        else
        {
            sub_800A2618(dword_800C9C88, dword_800C9C7C - 4);
        }
        t->next_8 = (void (*)())sub_800BC174();
        u->next_8 = (void (*)())(u->f4 = (int)sub_800BAE74);
    }
    else
    {
        u->fc = StartBattleMenu_800C6EFC();
        t->next_8 = sub_800BB940;
    }
}

void sub_800BB940(BatTask_a* t, BatObj_a* u)
{
    if ((*(int*)u->fc & 0x8001) != 1)
    {
        sub_800BC850(0x2000);
        if (dword_800ADE78 == 1)
        {
            if (((&dword_800ADE78)[4] = sub_800B4318(dword_800C9C88, &dword_800ADE78)) >= 0)
            {
                sub_800BC838(0x2000);
                t->next_8 = sub_800BAE74;
                return;
            }
        }
        t->next_8 = (void (*)())sub_800BC174();
        u->f4 = (int)sub_800BAE74;
        if (dword_800C9C88[0] == 2)
        {
            dword_800B122C |= dword_800C9C88[3];
        }
    }
}

void sub_800BBA24(BatTask_a* t, BatObj_a* u)
{
    u->fc = sub_800BC28C(t);
    u->next_8 = sub_800BBA70;
    t->next_8 = sub_800BC144;
}

#if 0 // Not matched: u and the hoisted constant 1 swap saved registers (s2/s3); tried decl order, int mask, early return, operand order
void sub_800BBA70(BatTask_a* t, BatObj_a* u)
{
    unsigned int mask;
    int i;
    BatSlot_a* s;
    if (sub_800BC1A8(dword_800C9C88[3]) == 1)
    {
        mask = dword_800C9C88[3];
        sub_800BC838(0x1000);
        sub_800BB74C();
        sub_800BB7D4();
        s = (BatSlot_a*)dword_800C9CC8;
        for (i = 0; i < 7; i++)
        {
            if (mask & (1 << i))
            {
                int f = *(int*)sub_80014390(i & 0xFF);
                if (f & 0x200)
                {
                    s[i].a = 0x13;
                }
                else if (f & 0x10000)
                {
                    s[i].a = 0xE;
                }
                else if (f & 2)
                {
                    s[i].a = 0x10;
                }
                else if (f & 0x8000)
                {
                    s[i].a = 0x12;
                }
                s[i].b = 0;
                s[i].c = 1 << i;
                s[i].d = 0;
            }
        }
        dword_800C9C7C = 7;
        u->fc = sub_800BC28C();
        u->next_8 = (void (*)())u->f4;
        t->next_8 = sub_800BC144;
    }
    else
    {
        t->next_8 = (void (*)())u->f4;
    }
}
#endif
INCLUDE_OVERLAY_ASM(battle, sub_800BBA70);

void sub_800BBBA8(BatTask_a* t, BatObj_a* u)
{
    u->fc = sub_800BC28C(t);
    u->next_8 = sub_800BBCC8;
    t->next_8 = sub_800BC144;
}

#if 0 // Not matched: the lbu of dword_800C9C98 is scheduled above the store to dword_800C9C88[3] (original keeps source order); tried early return, pointer local, swapped branches
void sub_800BBBF4(BatTask_a* t, BatObj_a* u)
{
    dword_800C9C88[0] = 3;
    dword_800C9C88[3] = 0;
    if (dword_800C9C98)
    {
        PlaySeqSlot_80031160(0x11, 1);
        u->fc = sub_800BC28C();
        u->next_8 = sub_800BBC84;
        t->next_8 = sub_800BC144;
    }
    else
    {
        sub_800BBDB4(t, u);
    }
}
#endif
INCLUDE_OVERLAY_ASM(battle, sub_800BBBF4);

void sub_800BBC84(BatTask_a* t)
{
    t->next_8 = sub_800BBCC8;
    sub_800C0BA0(t);
    sub_800C0AEC(dword_800C9C98 - 1, levantPos_8008BD18, levantPos_8008BD18[7]);
}

#if 0 // Not matched: needs the second copy of u (s3, from 'v'); remaining: u->fc store / dword_800ADE78 load order and the shared lui of sub_800BAE74 in the branch delay slot
extern int sub_800C0BF0();
extern void sub_800C0F1C();
void sub_800BBCC8(BatTask_a* t, BatObj_a* u)
{
    BatObj_a* v = u;
    if (sub_800C0BF0(t) == 1)
    {
        dword_800C9C88[0] = 2;
        dword_800C9C88[3] = 0;
        dword_800C9C99 = dword_800C9C98;
        dword_800C9C7C = dword_800C9C98;
        dword_800C9C82 = dword_800C9C98;
        dword_800C9C88[2] = 1 << dword_800C9C98;
        u->fc = sub_800BC28C();
        if (dword_800ADE78 == 1)
        {
            u->next_8 = sub_800BAE74;
        }
        else
        {
            sub_800BF770(dword_800C9C68, dword_800C9C7C);
            v->next_8 = sub_800BAE74;
        }
        sub_800C0F1C();
        t->next_8 = sub_800BC144;
    }
}
#endif
INCLUDE_OVERLAY_ASM(battle, sub_800BBCC8);

void sub_800BBDB4(BatTask_a* t, BatObj_a* u)
{
    u->fc = sub_800BC28C(t);
    u->next_8 = sub_800BBE00;
    t->next_8 = sub_800BC144;
}

void sub_800BBE00(BatTask_a* t, BatObj_a* u)
{
    dword_800C9C7C = 0;
    dword_800C9C99 = 0;
    dword_800C9C82 = 0;
    dword_800C9C88[2] = 1 << dword_800C9C98;
    u->fc = sub_800BC28C();
    u->next_8 = sub_800BBE7C;
    t->next_8 = sub_800BC144;
}

void sub_800BBE7C(BatTask_a* t)
{
    sub_800C0BA0();
    if (sub_800BC820(0x100) == 1)
    {
        t->next_8 = sub_800BB1B0;
    }
    else if (sub_800A248C() == 0)
    {
        t->next_8 = sub_800BAE74;
    }
    else
    {
        t->next_8 = sub_800BAE74;
        sub_800BF770(dword_800C9C68, dword_800C9C7C);
    }
}

void sub_800BBEFC(BatTask_a* t, BatObj_a* u)
{
    u->fc = sub_800BC28C(t);
    u->next_8 = sub_800BBF64;
    dword_800C9C88[3] = 0;
    dword_800C9C98 = dword_800C9C88[1] + 4;
    t->next_8 = sub_800BC144;
}

#if 0 // Not matched: instruction scheduling only (s0/s1 save order, C68 address placement); tried assignment-expression, pointer local, byte temp
void sub_800BBF64(BatTask_a* t, BatObj_a* u)
{
    dword_800C9C88[0] = 0x15;
    dword_800C9C7C = dword_800C9C98;
    dword_800C9C88[2] = 1 << dword_800C9C7C;
    sub_800A2AE8(dword_800C9C88);
    u->fc = sub_800BC28C();
    u->next_8 = (void (*)())u->f4;
    t->next_8 = sub_800BC144;
    sub_800BF770(dword_800C9C68, dword_800C9C7C);
}
#endif
INCLUDE_OVERLAY_ASM(battle, sub_800BBF64);

void sub_800BBFFC(BatTask_a* t, BatObj_a* u)
{
    u->fc = sub_800BC28C(t);
    u->next_8 = sub_800BC05C;
    dword_800C9C98 = dword_800C9C88[1] + 4;
    t->next_8 = sub_800BC144;
}

#if 0
void sub_800BC05C(BatTask_a* t, BatObj_a* u)
{
    dword_800C9C88[0] = 0x16;
    dword_800C9C7C = dword_800C9C98;
    dword_800C9C88[2] = 1 << dword_800C9C98;
    sub_800A2AE8(dword_800C9C88);
    sub_800BC838(0x10000);
    u->fc = sub_800BC28C();
    u->next_8 = (void (*)())u->f4;
    t->next_8 = sub_800BC144;
    sub_800BF770(dword_800C9C68, dword_800C9C7C);
}
#endif
INCLUDE_OVERLAY_ASM(battle, sub_800BC05C);

void sub_800BC0FC(BatTask_a* t, int* u)
{
    u[3] = sub_800BC28C(t);
    u[2] = u[1];
    t->next_8 = sub_800BC144;
}

void sub_800BC144(BatTask_a* t, BatTask_a* u)
{
    if ((*u->fc & 0x8001) != 1)
    {
        t->next_8 = u->next_8;
    }
}

int sub_800BC174()
{
    return dword_800C8B54[(unsigned char)dword_800C8B38[dword_800C9C88[0]]];
}

int sub_800BC1A8(unsigned int mask)
{
    int i;
    int m;
    BatMin_a* mn;
    int c;
    for (i = 0; i < 7; i++)
    {
        m = 1 << i;
        if (mask & m)
        {
            mn = (BatMin_a*)sub_80014390(i & 0xFF);
            c = (unsigned char)dword_800C9CBC[i];
            if (c != 0 && c != 5 && c != 6 && mn->h8 > 0)
            {
                if (dword_800C9CA0[i] & 0x18202)
                {
                    return 1;
                }
                if (mn->f0 & 0x8000)
                {
                    return 1;
                }
            }
        }
    }
    return 0;
}

int sub_800BC28C()
{
    EventEntry* e = AllocEventEntry_80043AF8(dword_8008B4C0);
    if (e)
    {
        e->flags = (e->flags | 1) & 0xFFFF7FFF;
        if (sub_800BC820(0x80000) == 1)
        {
            dword_800C9D7C = LoadOverlay_80020BF8(1, 0x1E);
            e->cb_8 = (EventEntryFn)sub_800BC324;
            sub_800BC850(0x80000);
        }
        else
        {
            e->cb_8 = (EventEntryFn)sub_800BDA28;
        }
    }
    return (int)e;
}

void sub_800BC324(BatTask_a* t, int a)
{
    if (GetFileRequestStatus_8003BE30(dword_800C9D7C) == 0)
    {
        t->next_8 = sub_800BDA28;
        t->next_8(t, a);
    }
}

extern BatV12_a* sub_800BC5EC();

int sub_800BC378(unsigned int mask, BatV12_a* out)
{
    BatV12_a arr[7];
    BatV12_a tmp;
    unsigned int i;
    int n;
    int m;
    n = i = 0;
    for (; i < 7; i++)
    {
        m = 1 << i;
        if (mask & m)
        {
            BatV12_a* p = (BatV12_a*)sub_800BC6CC(i);
            if (p)
            {
                arr[n].x = p->x;
                arr[n].y = p->y;
                arr[n].z = p->z;
                n++;
            }
        }
    }
    if (n != 0)
    {
        sub_800BC5EC(&tmp, arr, n);
        *out = tmp;
        return 1;
    }
    return 0;
}

void sub_800BC468(int a, int b)
{
    char buf[0x10];
    unsigned int i;
    int mask;
    if (sub_800BC378(a, buf))
    {
        for (i = 0; i < 7; i++)
        {
            mask = 1 << i;
            if (b & mask)
            {
                sub_800BC4D4(i, buf);
            }
        }
    }
}

void sub_800BC4D4(int a, int b)
{
    int r = sub_800BC570(a);
    if (r == 1)
    {
        switch ((unsigned int)sub_800BC7DC(a))
        {
        case 0:
            sub_800A8D48(b);
            break;
        case 1:
            sub_800C0DB0(b);
            break;
        case 2:
            sub_800A25D8(a - 4, b);
            break;
        default:
            break;
        }
    }
}

int sub_800BC570(int x)
{
    int m;
    if (x == 0 && dword_800C9C82 == 0)
    {
        return 1;
    }
    if (sub_800C0A9C() & (m = 1 << x))
    {
        if (x == dword_800C9C82)
        {
            return 1;
        }
    }
    return (sub_800A248C() & (m = 1 << x)) != 0;
}

BatV12_a* sub_800BC5EC(BatV12_a* dst, BatV12_a* src, unsigned int n)
{
    unsigned char i;
    BatV12_a tmp;
    if (n == 1)
    {
        *dst = *src;
    }
    else
    {
        n--;
        if (n)
        {
            i = 0;
            do
            {
                BatV12_a* p = &src[i];
                Midpoint3D_8003B95C(&tmp, p, &src[i + 1]);
                *p = tmp;
                i++;
            } while (i < n);
        }
        sub_800BC5EC(dst, src, n);
    }
    return dst;
}

int sub_800BC6CC(int a)
{
    int r = 0;
    int m;
    if (sub_800BC784(a))
    {
        int k = sub_800BC7DC(a);
        switch ((unsigned int)k)
        {
        case 1:
            m = sub_800BC7DC(dword_800C9C82);
            if (m == 0)
            {
            case 0:
                r = (int)levantPos_8008BD18;
                break;
            }
            if (m == k)
            {
                r = (int)sub_800C0F9C();
            }
            break;
        case 2:
            r = sub_800A2C28(a - 4);
            break;
        }
    }
    return r;
}

int sub_800BC784(int x)
{
    int m;
    if (x != 0)
    {
        if ((sub_800C0A9C() & (m = 1 << x)) == 0)
        {
            return (sub_800A248C() & m) != 0;
        }
    }
    return 1;
}

#if 0 // Not matched: original has a dead 'li v0,7' before the last return and uses v0 for x-4; tried switch/case ranges, else-if chains, x==7 tails
int sub_800BC7DC(int x)
{
    int r;
    if (x == 0)
    {
        r = 0;
    }
    else if ((unsigned int)(x - 1) < 3)
    {
        r = 1;
    }
    else if ((unsigned int)(x - 4) < 3)
    {
        r = 2;
    }
    else
    {
        r = 3;
    }
    return r;
}
#endif
INCLUDE_OVERLAY_ASM(battle, sub_800BC7DC);

int sub_800BC820(unsigned int m)
{
    return (dword_800B1228 & m) != 0;
}

void sub_800BC838(unsigned int m)
{
    dword_800B1228 |= m;
}

void sub_800BC850(unsigned int m)
{
    dword_800B1228 &= ~m;
}

int sub_800BC868()
{
    return dword_800C9D84;
}

void sub_800BC878()
{
    char buf[4];
    memset(buf, 0, 4);
    LoadEffectFile_80020DDC(dword_800C8EAC[dword_80083BD0].b, dword_80095468, buf, buf, 0, 0);
    dword_800C9D8C[1] = -1;
    dword_800C9D8C[0] = -1;
}

int sub_800BC8E8()
{
    return IsEffectFileLoaded_80020EBC(dword_80095468);
}

#if 0 // Not matched: ~900 of 1095 instructions identical; control flow, stack frame and most blocks match; left are
      // register allocation / loop-invariant hoisting differences (light, saveData and 1/240 constant bases) in every block.
      // Its .rdata (the {0x1000,0x1000,0x1000} initializer at 0x800B6700, then the switch table at 0x800B6710) needs
      // a source-file boundary: one TU puts the table at 0x800B670C. Splitting needs rdata starts 0x800B6700 (at or
      // before this function) and 0x800B6774 (at or before sub_800BE834, so ApplyBattleCommand's table stays at 0x800B6794).
typedef struct BatStage_a
{
    unsigned short* list_0;
    short f4;
    unsigned char model_6;
    unsigned char f7;
    short floor_8;
    short anim_A;
    unsigned short* models_C;
} BatStage_a;

typedef struct BatFxEnt_a
{
    short u_0;
    short v_2;
    short w_4;
    short h_6;
    short f8;
    short fA;
    short fC;
    short fE;
    short x_10;
    short y_12;
    short z_14;
    short f16;
    unsigned char r_18;
    unsigned char g_19;
    unsigned char b_1A;
    unsigned char f1B;
} BatFxEnt_a;

typedef struct BatFxGrp_a
{
    int n_0;
    unsigned char* counts_4;
    BatFxEnt_a** ents_8;
    POLY_FT4 poly_C;
} BatFxGrp_a;

typedef struct BatFxMdl_a
{
    int n_0;
    char* parts_4;
    char pad8[0x14];
} BatFxMdl_a;

typedef struct BatLight_a
{
    char pad0[0x30];
    unsigned char r_30;
    unsigned char g_31;
    unsigned char b_32;
    char pad33[0x1D];
    short r_50;
    short g_52;
    short b_54;
} BatLight_a;

extern char dword_800C9124[];
extern char cameraState_8008D4F0[];
extern short word_8008D4C8;
extern short word_8008D51E;
extern unsigned char dword_800C911C[];
extern void sub_8004D1EC(int a0, int a1, int a2, int a3, int a4, int a5, int a6);
extern void sub_80043DE0(void* a0, void* a1, void* a2, void* a3);
extern void sub_80044010();
extern int sub_80020F00(void* p, int a, int b);
typedef struct BatStageObj_a
{
    char pad0[0x38];
    int x_38;
    int y_3C;
    int z_40;
} BatStageObj_a;

void sub_800BC90C(BatStageObj_a* p)
{
    int scale[3] = { 0x1000, 0x1000, 0x1000 };
    int idx;
    int i;

    unknownFlags_8008D678 &= ~0x10000;
    idx = sub_80020F00(dword_80095468, 1, ((BatStage_a*)dword_800C8EAC)[dword_80083BD0].model_6);
    sub_8004D1EC((int)((BatFxMdl_a*)dword_80095468[10])[idx].parts_4, (int)pOT_8008B4C8, (int)&p->x_38, (int)dword_800C9124, (int)stru_8008D534, 1, (int)scale);
    {
        unsigned short* list = ((BatStage_a*)dword_800C8EAC)[dword_80083BD0].list_0;
        char* sd = (char*)&saveData_8008B570;
        for (; *list != 0xFFFF; list++)
        {
            BatFxGrp_a* g = &((BatFxGrp_a*)dword_80095468[8])[sub_80020F00(dword_80095468, 0, *list)];
            int j;
            for (j = 0; j < g->n_0; j++)
            {
                int k;
                for (k = 0; k < g->counts_4[j]; k++)
                {
                    VECTOR pos;
                    CVECTOR col;
                    short sz[2];
                    BatFxEnt_a* e = &g->ents_8[j][k];
                    BatLight_a* l = (BatLight_a*)cameraState_8008D4F0;
                    pos.vx = p->x_38;
                    pos.vy = p->y_3C;
                    pos.vz = p->z_40;
                    pos.vx += e->x_10;
                    pos.vz += e->z_14;
                    pos.vy = *(int*)(sd + 0x7AC) + e->y_12;
                    if (e->fE != 0)
                    {
                        col.r = l->r_30 + e->r_18 * l->r_50 / 4096;
                        col.g = l->g_31 + e->g_19 * l->g_52 / 4096;
                        col.b = l->b_32 + e->b_1A * l->b_54 / 4096;
                        if (dword_80083BD0 == 0x10)
                        {
                            SetSemiTrans(&g->poly_C, 1);
                        }
                        if (dword_80083BD0 == 0x13)
                        {
                            sz[0] = e->fC * 5;
                            sz[1] = e->fE * 5;
                            sub_80044010(&g->poly_C, &pos, dword_800C9124, e, &e->w_4, &e->f8, sz, &e->x_10, &col, 0, 0, pOT_8008B4C8);
                        }
                        else
                        {
                            sub_80043DE0(&g->poly_C, &pos, &e->fC, &col);
                        }
                    }
                }
            }
        }
    }
    if (((BatStage_a*)dword_800C8EAC)[dword_80083BD0].floor_8 >= 0)
    {
        for (i = 0; i < 32; i++)
        {
            DVECTOR sxy;
            VECTOR v;
            POLY_FT4 poly;
            SVECTOR sv;
            long pp;
            long flag;
            int a;
            int x;
            int w;
            short* cam = &word_8008D4C8;
            v.vx = p->x_38;
            v.vy = p->y_3C;
            v.vz = p->z_40;
            a = -cam[1];
            v.vx += sinTable_80084540[a & 0xFFF];
            v.vy = *(int*)&levantPos_8008BD18[2] - 0x352;
            v.vx -= ((int*)dword_8008D600)[0];
            v.vy -= ((int*)dword_8008D600)[1];
            v.vz += sinTable_80084540[(a + 0x400) & 0xFFF];
            v.vz -= ((int*)dword_8008D600)[2];
            sv.vx = v.vx;
            sv.vy = v.vy;
            sv.vz = v.vz;
            RotTransPers(&sv, (long*)&sxy, &pp, &flag);
            poly = ((BatFxGrp_a*)dword_80095468[8])[((BatStage_a*)dword_800C8EAC)[dword_80083BD0].floor_8 + i % 4].poly_C;
            x = ((cam[1] & 0xFFF) / 4 + i * 96 - 0x400) * word_8008D51E / 240;
            if ((unsigned int)(x + 0x60) < 0x1A0)
            {
                w = word_8008D51E * 96 / 240;
                poly.r0 = poly.r0 * dword_8008D40C >> 12;
                poly.g0 = poly.g0 * dword_8008D40C >> 12;
                poly.b0 = poly.b0 * dword_8008D40C >> 12;
                setShadeTex(&poly, 0);
                setXYWH(&poly, x, sxy.vy - w, w + 1, w + 1);
                *(POLY_FT4*)primAllocPtr_800960A8[bDoubleBuffer_8008D428] = poly;
                addPrim(&pOT_8008B4C8[0x3FF], primAllocPtr_800960A8[bDoubleBuffer_8008D428]);
                primAllocPtr_800960A8[bDoubleBuffer_8008D428] += sizeof(POLY_FT4);
            }
        }
    }
    if (((BatStage_a*)dword_800C8EAC)[dword_80083BD0].anim_A >= 0)
    {
        int cols = 0;
        unsigned int n = 0;
        if (dword_80083BD0 == 0xF)
        {
            cols = 3;
            n = 9;
        }
        else if (dword_80083BD0 == 0x13)
        {
            cols = 4;
            n = 0xE;
        }
        else if (dword_80083BD0 == 0x15 || dword_80083BD0 == 0x1D || dword_80083BD0 == 6 || dword_80083BD0 == 0x1C || dword_80083BD0 == 5)
        {
            cols = 1;
            n = 0xC;
        }
        switch (dword_80083BD0)
        {
        case 5:
        case 6:
        case 0xF:
        case 0x13:
        case 0x15:
        case 0x1C:
        case 0x1D:
        {
            BatFxGrp_a* g = &((BatFxGrp_a*)dword_80095468[8])[sub_80020F00(dword_80095468, 0, ((BatStage_a*)dword_800C8EAC)[dword_80083BD0].anim_A)];
            int j;
            for (j = 0; j < g->n_0; j++)
            {
                int half = n >> 1;
                int t = (dword_800C911C[j % 8] + (unsigned int)frameCount_8008D3FC) % n;
                int k;
                if (dword_80083BD0 == 0x13 && half < t)
                {
                    t = n - t;
                }
                if (dword_80083BD0 == 0x15 || dword_80083BD0 == 0x1D || dword_80083BD0 == 6 || dword_80083BD0 == 0x1C || dword_80083BD0 == 5)
                {
                    if (half < t)
                    {
                        t = n - t;
                    }
                    t = t / 2;
                }
                for (k = 0; k < g->counts_4[j]; k++)
                {
                    VECTOR pos;
                    CVECTOR col;
                    BatFxEnt_a* e = &g->ents_8[j][k];
                    int du;
                    int dv;
                    int uu;
                    int vv;
                    char* sd;
                    BatLight_a* l;
                    if (dword_800C9D8C[1] < 0 && dword_800C9D8C[0] < 0)
                    {
                        dword_800C9D8C[0] = g->poly_C.u0;
                        dword_800C9D8C[1] = g->poly_C.v0;
                    }
                    du = t % cols;
                    dv = t / cols;
                    sd = (char*)&saveData_8008B570;
                    pos.vx = p->x_38;
                    pos.vy = p->y_3C;
                    pos.vz = p->z_40;
                    pos.vx += e->x_10;
                    pos.vz += e->z_14;
                    pos.vy = *(int*)(sd + 0x7AC) + e->y_12;
                    du = du * (e->w_4 + 1);
                    dv = dv * (e->h_6 + 1);
                    uu = e->u_0 + du;
                    vv = e->v_2 + dv;
                    if (cols == 1)
                    {
                        uu = e->u_0;
                    }
                    g->poly_C.u0 = dword_800C9D8C[0] + uu;
                    g->poly_C.v0 = dword_800C9D8C[1] + vv;
                    g->poly_C.u1 = dword_800C9D8C[0] + uu + e->w_4;
                    g->poly_C.v1 = dword_800C9D8C[1] + vv;
                    g->poly_C.u2 = dword_800C9D8C[0] + uu;
                    g->poly_C.v2 = dword_800C9D8C[1] + vv + e->h_6;
                    g->poly_C.u3 = dword_800C9D8C[0] + uu + e->w_4;
                    g->poly_C.v3 = dword_800C9D8C[1] + vv + e->h_6;
                    if (e->fE != 0)
                    {
                        l = (BatLight_a*)cameraState_8008D4F0;
                        col.r = l->r_30 + e->r_18 * l->r_50 / 4096;
                        col.g = l->g_31 + e->g_19 * l->g_52 / 4096;
                        col.b = l->b_32 + e->b_1A * l->b_54 / 4096;
                        SetSemiTrans(&g->poly_C, 1);
                        sub_80043DE0(&g->poly_C, &pos, &e->fC, &col);
                    }
                }
            }
            break;
        }
        default:
        {
            BatFxGrp_a* g = &((BatFxGrp_a*)dword_80095468[8])[sub_80020F00(dword_80095468, 0, ((BatStage_a*)dword_800C8EAC)[dword_80083BD0].anim_A)];
            int j = ((unsigned int)frameCount_8008D3FC % (g->n_0 * 2)) / 2;
            int k;
            for (k = 0; k < g->counts_4[j]; k++)
            {
                int m;
                for (m = 0; m < 8; m++)
                {
                    VECTOR pos;
                    CVECTOR col;
                    int d;
                    int ang;
                    BatFxEnt_a* e = &g->ents_8[j][k];
                    char* sd = (char*)&saveData_8008B570;
                    BatLight_a* l = (BatLight_a*)cameraState_8008D4F0;
                    pos.vx = p->x_38;
                    pos.vy = p->y_3C;
                    pos.vz = p->z_40;
                    d = ISqrt_8003B918(e->x_10 * e->x_10 + e->z_14 * e->z_14);
                    ang = ratan2_8003B548(e->x_10, e->z_14) + m * 512;
                    pos.vx += sinTable_80084540[(ang + 0x400) & 0xFFF] * d / 4096;
                    pos.vz += sinTable_80084540[ang & 0xFFF] * d / 4096;
                    pos.vy = *(int*)(sd + 0x7AC) + e->y_12;
                    g->poly_C.u0 = e->u_0;
                    g->poly_C.v0 = e->v_2;
                    g->poly_C.u1 = e->u_0 + e->w_4;
                    g->poly_C.v1 = e->v_2;
                    g->poly_C.u2 = e->u_0;
                    g->poly_C.v2 = e->v_2 + e->h_6;
                    g->poly_C.u3 = e->u_0 + e->w_4;
                    g->poly_C.v3 = e->v_2 + e->h_6;
                    if (e->fE != 0)
                    {
                        col.r = l->r_30 + e->r_18 * l->r_50 / 4096;
                        col.g = l->g_31 + e->g_19 * l->g_52 / 4096;
                        col.b = l->b_32 + e->b_1A * l->b_54 / 4096;
                        sub_80043DE0(&g->poly_C, &pos, &e->fC, &col);
                    }
                }
            }
            break;
        }
        }
    }
    if (((BatStage_a*)dword_800C8EAC)[dword_80083BD0].models_C != 0)
    {
        for (i = 0; i < 3; i++)
        {
            unsigned short* ent = &((BatStage_a*)dword_800C8EAC)[dword_80083BD0].models_C[i * 4];
            int id = ent[0];
            int fl = ent[1];
            unsigned long* ot = pOT_8008B4C8;
            if (id != 0xFF)
            {
                int sc[3] = { 0x1000, 0x1000, 0x1000 };
                VECTOR pos;
                SVECTOR rot;
                BatFxMdl_a* mdl = &((BatFxMdl_a*)dword_80095468[10])[sub_80020F00(dword_80095468, 1, id)];
                int k;
                memset(&rot, 0, 8);
                if (dword_80083BD0 == 0x10)
                {
                    rot.vy = frameCount_8008D3FC * 100;
                }
                pos.vx = p->x_38;
                pos.vy = p->y_3C;
                pos.vz = p->z_40;
                pos.vy = *(int*)&levantPos_8008BD18[2];
                if (dword_80083BD0 == 0x13 && i == 0)
                {
                    sc[0] *= 3;
                    sc[1] *= 3;
                    sc[2] *= 3;
                }
                if (dword_80083BD0 == 0x14)
                {
                    pos.vy -= 0x2F8;
                }
                for (k = 0; k < mdl->n_0; k++)
                {
                    sub_8004D1EC((int)(mdl->parts_4 + k * 0x54), (int)ot, (int)&pos, (int)&rot, 0, fl, (int)sc);
                }
            }
        }
    }
}
#endif
INCLUDE_OVERLAY_ASM(battle, sub_800BC90C);

extern void ApplyBattleCommand_800BEBB8();
extern void sub_80037828(int a, int b, int c);
extern void sub_800BDB4C();
void sub_800BDA28(BatTask_a* t)
{
    int i;
    int f;
    int m;
    if (!(dword_800B1228 & 0x1000))
    {
        sub_800BB794();
        sub_800BB7D4();
        ApplyBattleCommand_800BEBB8();
        if (!(*(int*)&saveData_8008B570 & 2))
        {
            f = 0;
            for (i = 4; i < 7; i++)
            {
                m = sub_800A248C() & (1 << i);
                if (m != 0)
                {
                    if (sub_800BF980(sub_800A2BE4(i - 4)))
                    {
                        f = 1;
                        break;
                    }
                }
            }
            if (f)
            {
                sub_80037828(sub_800BC7DC(dword_800C9C7C), (short)dword_800C9C88[0], 1);
            }
            else
            {
                sub_80037828(sub_800BC7DC(dword_800C9C7C), (short)dword_800C9C88[0], 0);
            }
        }
    }
    t->next_8 = sub_800BDB4C;
}

void sub_800BDB4C(BatTask_a* t)
{
    if (sub_800BDD3C() == 1)
    {
        sub_800BF2E8();
        sub_800BDEBC();
        sub_800BDF74();
        sub_800BDFAC();
        sub_800BE2C8();
        t->next_8 = sub_800BDBB0;
    }
}

void sub_800BDBB0(BatTask_a* t)
{
    if (sub_800BDE04() == 1)
    {
        if (dword_800C9C88[0] == 2 && dword_800C9C7C == 0)
        {
            sub_800C0AEC(dword_800C9C98 - 1, levantPos_8008BD18, levantPos_8008BD18[7]);
        }
        dword_800C9D90 = 0;
        dword_800C9D94 = 0;
        t->next_8 = sub_800BDC3C;
    }
}

void sub_800BDC3C(BatTask_a* t)
{
    int k;
    if ((short)sub_800BE364() < dword_800C9D94 && sub_800BEA94() == 1)
    {
        while ((k = dword_800C9D90--) != 0)
        {
            sub_800A2924(dword_800C9DD0[dword_800C9D90]);
        }
        t->f0 = (t->f0 & ~1) | 0x8000;
        dword_800B1228 &= ~0x1000;
    }
    else
    {
        sub_800BE3C0();
    }
    dword_800C9D94++;
}

int sub_800BDD3C()
{
    unsigned char i;
    int r;
    int m;
    if (*(int*)&saveData_8008B570 & 0x20)
    {
        return 1;
    }
    if (dword_800C9C82 == 0)
    {
        r = sub_800A89F0();
    }
    else
    {
        r = sub_800C0D60();
    }
    if (r == 0)
    {
        return 0;
    }
    for (i = 4; i < 7; i++)
    {
        m = sub_800A248C() & (1 << i);
        if (m != 0)
        {
            if (sub_800A2550(i - 4) == 0)
            {
                return 0;
            }
        }
    }
    return IsEffectTaskIdle_800148D4() != 0;
}

int sub_800BDE04()
{
    unsigned char i;
    int r;
    int m;
    if (*(int*)&saveData_8008B570 & 0x20)
    {
        return 1;
    }
    if (dword_800C9C82 == 0)
    {
        r = sub_800A8BE4();
    }
    else
    {
        r = sub_800C0D88();
    }
    if (r == 0)
    {
        return 0;
    }
    for (i = 4; i < 7; i++)
    {
        r = sub_800A248C();
        m = 1 << i;
        if (r & m)
        {
            if (sub_800A2594(i - 4) == 0)
            {
                return 0;
            }
        }
    }
    return 1;
}

void sub_800BDEBC()
{
    int x;
    int y;
    int ny;
    if (!(*(int*)&saveData_8008B570 & 0x20))
    {
        x = dword_800C9C88[2];
        if (x & 0xF)
        {
            x &= ~0xE;
            x |= 1;
        }
        y = dword_800C9C88[3];
        if (y & 0xF)
        {
            y &= ~0xE;
            y |= 1;
        }
        ny = y & ~x;
        x = x & ~y;
        y = ny;
        if (y)
        {
            if (dword_800C9C88[2])
            {
                sub_800BC468(y, dword_800C9C88[2]);
            }
        }
        if (x)
        {
            if (dword_800C9C88[3])
            {
                sub_800BC468(x, dword_800C9C88[3]);
            }
        }
    }
}

void sub_800BDF74()
{
    sub_800BE058(dword_800C9D98, dword_800C9C88, 0, dword_800C9C7C);
}

void sub_800BDFAC()
{
    unsigned char i;
    BatPair_a t;
    for (i = 0; i < 7; i++)
    {
        if (dword_800C9C7C == i)
        {
            t.a = 0;
            t.b = 0;
        }
        else
        {
            sub_800BE058(&t, &((BatSlot_a*)dword_800C9CC8)[i], 1, i);
        }
        dword_800C9DA0[i] = t;
    }
}

extern void sub_800A8A30();
extern void sub_800A2684();
BatPair_a* sub_800BE058(BatPair_a* out, int* p, int c, int a)
{
    BatPair_a r;
    if ((*(int*)&saveData_8008B570 & 0x20) || sub_800BC570(a) == 0)
    {
        r.a = 0;
        r.b = 0;
    }
    else
    {
        switch ((unsigned int)sub_800BC7DC(a))
        {
        case 0:
            sub_800A8A30(&r, p, c);
            break;
        case 1:
            sub_800C0DDC(&r, p, c);
            break;
        case 2:
            sub_800A2684(&r, p, c);
            break;
        }
    }
    *out = r;
    return out;
}

extern void sub_800A8C0C(int b);
extern void sub_800A2760(int* p, int b);
extern void sub_800377B4(int a, int b, int c);
void sub_800BE14C(int* p, int b, int k)
{
    int r;
    if (*(int*)&saveData_8008B570 & 0x20)
    {
        return;
    }
    if (sub_800BC570(k) == 0)
    {
        return;
    }
    r = sub_800BC7DC(k);
    switch ((unsigned int)r)
    {
    case 0:
        sub_800A8C0C(b);
        break;
    case 1:
        sub_800C0E84(p, b);
        break;
    case 2:
        sub_800A2760(p, b);
        if (p[0] == 0x13 || p[0] == 0xB || p[0] == 7 || (p[0] == 5 && sub_80013358(p[1]) == 1) || (p[0] == 0x1A && sub_80013358(p[1]) == 1))
        {
            dword_800C9DD0[dword_800C9D90] = k - 4;
            dword_800C9D90++;
        }
        break;
    }
    if (!(*(int*)&saveData_8008B570 & 2) && b == 0)
    {
        sub_800377B4(r, (short)p[0], k - 4);
    }
}

void sub_800BE2C8()
{
    int m = sub_800BE364();
    unsigned char i;
    dword_800C9DBC = m - dword_800C9D98[0];
    dword_800C9D98[1] += dword_800C9DBC;
    for (i = 0; i < 7; i++)
    {
        dword_800C9DC0[i] = m - dword_800C9DA0[i].a;
        dword_800C9DA0[i].b += dword_800C9DC0[i];
    }
}

int sub_800BE364()
{
    unsigned char i;
    short m = dword_800C9D98[0];
    for (i = 0; i < 7; i++)
    {
        if (m < dword_800C9DA0[i].a)
        {
            m = dword_800C9DA0[i].a;
        }
    }
    return m;
}

extern void sub_80037BFC(int a);
extern void PlaySfx_80031494(int id);
extern void StartPadVibration_80036528(int pad, int kind);
extern void sub_800AD944(int a);
extern void sub_800AD1E0(int a, int b, int c);
extern void sub_800A2898(int a);
extern void sub_800A284C(int a);
extern void sub_80039ED8(int a);
extern void sub_800127D0(int a0, int a1, int a2, int a3);
extern void sub_800BF3DC(int a, int b, int c, int d, int e);
extern void sub_800BE834(int a, int b);
extern void sub_800C0F1C();
typedef struct BatSettingsBits
{
    unsigned int pad0 : 21;
    unsigned int b21 : 1;
} BatSettingsBits;
void sub_800BE3C0()
{
    unsigned char i;
    int v;
    if (dword_800C9DBC == dword_800C9D94 && dword_800C9C7C < 7)
    {
        sub_800BE14C(dword_800C9C88, 0, dword_800C9C7C);
        sub_800BF3DC(dword_800C9C7C, 0, dword_800C9C7E, sub_800BC6CC(dword_800C9C7C), 0);
        if (dword_800C9C7E > 0)
        {
            sub_80037BFC(0x1E);
            PlaySfx_80031494(0x72);
        }
        sub_800BF3DC(dword_800C9C7C, 1, dword_800C9C80, sub_800BC6CC(dword_800C9C7C), 0);
        v = dword_800C9C88[0];
        if (v == 5 || v == 0x1A)
        {
            sub_800AD944(1);
        }
        else if (v == 4)
        {
            sub_800AD1E0(dword_800C9C88[1], 1, 0);
        }
        else if (v == 0x13)
        {
            sub_800127B8((struct_obj_B*)sub_80014390(dword_800C9C7C));
        }
        if (dword_800C9C88[0] == 7 && dword_800C9C7C != 0)
        {
            PlaySeqSlot_80031160(0x1C, 1);
        }
        if (sub_800BC7DC(dword_800C9C7C) == 0 || sub_800BC7DC(dword_800C9C7C) == 1)
        {
            v = dword_800C9C88[0];
            if (v == 5)
            {
                if (((BatSettingsBits*)&settingsFlags_8008B58C)->b21 == 1)
                {
                    StartPadVibration_80036528(0, 3);
                }
                else
                {
                    StartPadVibration_80036528(0, 4);
                }
            }
            else if (v - 2 < 2U)
            {
                StartPadVibration_80036528(0, 9);
            }
        }
    }
    if (dword_800C9D98[0] + dword_800C9DBC == dword_800C9D94)
    {
        if (dword_800C9D78 >= 0)
        {
            if ((unsigned short)(dword_800C9D78 - 0x70) < 3)
            {
                PlaySfx_80031494(dword_800C9D78);
            }
        }
        if (dword_800C9D80 >= 0)
        {
            if (sub_800BC820(4) == 1 || (sub_800BC820(8) != 1 && sub_800BC820(0x100000) == 1))
            {
                PlaySeqSlot_80031160(0x1C, 1);
            }
            else
            {
                PlaySfx_80031494(0x6F);
            }
        }
        if (dword_800C9D84 != *(signed char*)&dword_800C9D82)
        {
            sub_80039ED8(dword_800C9D84);
            dword_800C9D82 = dword_800C9D84;
        }
    }
    for (i = 0; i < 7; i++)
    {
        if (dword_800C9DC0[i] == dword_800C9D94)
        {
            if (dword_800C9C7C != i)
            {
                BatSlot_a* s = &((BatSlot_a*)dword_800C9CC8)[i];
                if ((s->a == 5 && sub_80013358(s->b) == 1) || (s->a == 0x1A && sub_80013358(s->b) == 1))
                {
                    sub_800A2898(i - 4);
                }
                sub_800BE14C(&dword_800C9CC8[i * 4], 1, i);
            }
            if (dword_800C9DC0[i] == dword_800C9D94)
            {
                sub_800127D0(i, 0x11, 0, dword_800C9D58[i]);
                sub_800127D0(i, 0x10, 0, dword_800C9CA0[i]);
                sub_800BE834(i, sub_800BC6CC(i));
                if (sub_800BC784(i) == 1)
                {
                    if (i >= 4)
                    {
                        sub_800A284C(i - 4);
                    }
                    else if (i != 0 && dword_800C9C82 != 0)
                    {
                        sub_800C0F1C();
                    }
                }
            }
        }
    }
}

INCLUDE_OVERLAY_ASM(battle, sub_800BE834);

#if 0 // Not matched: the shared 'return 1' block sits after the sub_800BEB68 test in the original (here it lands at the end and the last test flips); tried goto/early-return layouts
int sub_800BEA94()
{
    if (!(*(int*)&saveData_8008B570 & 0x20))
    {
        if (sub_800BF47C() == 1)
        {
            return 0;
        }
        if (sub_800BC820(4) == 1)
        {
            if (sub_800BEB50() == 0)
            {
                return 0;
            }
            if (sub_800BEB68() == 0)
            {
                return 0;
            }
        }
        else
        {
            if (dword_800C912C[(unsigned char)dword_800C8B38[dword_800C9C88[0]]] == 0)
            {
                return sub_800BEB50();
            }
            return sub_800BEB68();
        }
    }
    return 1;
}
#endif
INCLUDE_OVERLAY_ASM(battle, sub_800BEA94);

int sub_800BEB50()
{
    return dword_800C9D94 > dword_800C9D9A;
}

int sub_800BEB68()
{
    int i;
    for (i = 0; i < 7; i++)
    {
        if (dword_800C9D94 < dword_800C9DA0[i].b)
        {
            return 0;
        }
    }
    effectOutcomeFlag_8008D780 = 1;
    return 1;
}

typedef struct BatUnit_a
{
    unsigned int flags_0;
    int f4;
    short hp_8;
    short hpLoss_A;
    short mp_C;
    short mpLoss_E;
    char pad10[0x34];
    unsigned char f44;
} BatUnit_a;

typedef struct BatCmd_a
{
    int f0;
    int f4;
    int f8;
    int fC;
} BatCmd_a;

typedef struct BatResult_a
{
    unsigned short kind_0;
    unsigned short arg_2;
    int f4;
    int f8;
    int fC;
    int f10;
    int f14;
    int f18;
    int f1C;
    int f20;
    short f24;
    short f26;
} BatResult_a;

extern void sub_80012BB0(BatUnit_a* a, BatUnit_a* b, BatCmd_a* c, BatResult_a* r);
extern void sub_800B4390(BatUnit_a* a, BatUnit_a* b, int* c, BatResult_a* r, int* e);
extern void sub_800BF9F0(int a);
void ApplyBattleCommand_800BEBB8()
{
    BatCmd_a cmd;
    BatResult_a res;
    BatUnit_a* actor;
    BatUnit_a* m;
    int flag;
    int r;
    unsigned int i;
    int bit;
    int a;

    sub_800BC7DC(dword_800C9C7C);
    flag = 1;
    actor = (BatUnit_a*)sub_80014390(dword_800C9C7C);
    cmd = *(BatCmd_a*)dword_800C9C88;
    if (dword_800C9C88[0] == 0x12)
    {
        actor = (BatUnit_a*)sub_80014390(dword_800C9C7C);
        actor->flags_0 |= 0x8000;
    }
    for (i = 0; i < 7; i++)
    {
        r = sub_800BC7DC(i);
        bit = 1 << i;
        ((BatSlot_a*)dword_800C9CC8)[i].a = 0x14;
        ((BatSlot_a*)dword_800C9CC8)[i].b = 0;
        ((BatSlot_a*)dword_800C9CC8)[i].c = bit;
        ((BatSlot_a*)dword_800C9CC8)[i].d = 0;
        if (dword_800C9C88[3] & bit)
        {
            m = (BatUnit_a*)sub_80014390(i & 0xFF);
            res.f24 = (signed char)dword_800C9D82;
            res.f26 = (signed char)dword_800C9D83;
            cmd.fC = bit;
            sub_80012BB0(actor, m, &cmd, &res);
            if (dword_800ADE78 == 1)
            {
                sub_800B4390(actor, m, dword_800C9C88, &res, &dword_800ADE78);
            }
            dword_800C9D84 = res.f24;
            dword_800C9D38[i] = res.f1C;
            dword_800C9D48[i] = res.f20;
            if (dword_800C9C7C < 7 && i != dword_800C9C7C)
            {
                dword_800C9D38[dword_800C9C7C] += res.f14;
                dword_800C9D48[dword_800C9C7C] += res.f18;
                if (dword_800C9D38[dword_800C9C7C] != 0)
                {
                    if (dword_800C9D48[dword_800C9C7C] != 0)
                    {
                        dword_800C9CBC[dword_800C9C7C] = 3;
                    }
                    else
                    {
                        dword_800C9CBC[dword_800C9C7C] = 1;
                    }
                }
                else if (dword_800C9D48[dword_800C9C7C] != 0)
                {
                    dword_800C9CBC[dword_800C9C7C] = 2;
                }
            }
            if (dword_800C9D38[i] > 0)
            {
                if (m->hp_8 < dword_800C9D38[i])
                {
                    dword_800C9D38[i] = m->hp_8;
                }
            }
            else if (dword_800C9D38[i] < m->hp_8 - m->hpLoss_A)
            {
                dword_800C9D38[i] = m->hp_8 - m->hpLoss_A;
            }
            if (dword_800C9D48[i] > 0)
            {
                if (m->mp_C < dword_800C9D48[i])
                {
                    dword_800C9D48[i] = m->mp_C;
                }
            }
            else if (dword_800C9D48[i] < m->mp_C - m->mpLoss_E)
            {
                dword_800C9D48[i] = m->mp_C - m->mpLoss_E;
            }
            if (res.fC != 0)
            {
                dword_800C9C7E = res.fC;
            }
            if (res.f10 != 0)
            {
                dword_800C9C80 = res.f10;
            }
            if (sub_800BC784(i) == 1)
            {
                dword_800C9CBC[i] = res.kind_0;
                dword_800C9D58[i] = res.f4;
                dword_800C9CA0[i] = res.f8;
                switch (res.kind_0)
                {
                case 0:
                    ((BatSlot_a*)dword_800C9CC8)[i].b = res.arg_2;
                    if (res.arg_2 != 0)
                    {
                        flag = 0;
                    }
                    break;
                case 1:
                case 2:
                case 3:
                    if (dword_800C9D38[i] > 0 || dword_800C9D48[i] > 0)
                    {
                        ((BatSlot_a*)dword_800C9CC8)[i].a = 9;
                        dword_800C9D78 = 0x72;
                    }
                    break;
                case 4:
                    ((BatSlot_a*)dword_800C9CC8)[i].a = 10;
                    dword_800C9D78 = 0x71;
                    break;
                case 5:
                    a = m->flags_0 & 0x8000;
                    ((BatSlot_a*)dword_800C9CC8)[i].a = a ? 0x14 : 0xC;
                    dword_800C9D78 = 0x70;
                    break;
                case 7:
                    ((BatSlot_a*)dword_800C9CC8)[i].a = 5;
                    ((BatSlot_a*)dword_800C9CC8)[i].b = res.arg_2;
                    dword_800C9C88[1] = res.arg_2;
                    if (sub_80013358(res.arg_2) == 1)
                    {
                        sub_800BF9F0(sub_800A2BE4(i - 4));
                        if (GetCapturedMinionsFromBitfield_8003BA58(sub_800A248C()) == 1)
                        {
                            dword_800C9C88[0] = 0x1A;
                        }
                        sub_800BC838(0x40);
                        if (r == 2)
                        {
                            
                            dword_800B1238[i - 4].c = dword_800C9C7C;
                            dword_800B1238[i - 4].e = dword_800C9C88[0];
                            dword_800B1238[i - 4].a = m->f4;
                            dword_800B1238[i - 4].d = m->f44;
                        }
                    }
                    break;
                }
                if (m->hp_8 <= dword_800C9D38[i] || (dword_800C9CA0[i] & 0x600))
                {
                    dword_800C9D38[i] = m->hp_8;
                    ((BatSlot_a*)dword_800C9CC8)[i].a = 0xB;
                    if (r == 2)
                    {
                        sub_800BC838(0x40);
                        if (sub_800BF9B4(sub_800A2BE4(i - 4)) == 1)
                        {
                            sub_800BC838(0x100000);
                        }
                        else
                        {
                            sub_800BC850(0x100000);
                        }
                        if (sub_800A2AB4() == 2)
                        {
                            sub_800BC838(2);
                        }
                        
                        dword_800B1238[i - 4].b = sub_800A2BE4(i - 4);
                        dword_800B1238[i - 4].c = dword_800C9C7C;
                        dword_800B1238[i - 4].e = dword_800C9C88[0];
                        dword_800B1238[i - 4].a = m->f4;
                        dword_800B1238[i - 4].d = m->f44;
                        if (sub_800BC820(0x100000) == 1)
                        {
                            dword_800C9D80 = 0x1C;
                        }
                        else
                        {
                            dword_800C9D80 = 0x6F;
                        }
                    }
                    else if (r == 0)
                    {
                        sub_800BC838(4);
                        dword_800C9D80 = 0x1C;
                    }
                    else
                    {
                        sub_800BC838(8);
                        dword_800C9D80 = 0x6F;
                    }
                }
            }
            if (i == dword_800C9C7C)
            {
                ((BatSlot_a*)dword_800C9CC8)[i].a = 0x14;
            }
        }
    }
    if (dword_800C9C88[0] == 7)
    {
        if (flag == 1)
        {
            dword_800C9C88[1] = 0;
            if (sub_800BC7DC(dword_800C9C7C) == 0)
            {
                sub_800BC838(0x80);
            }
        }
        else
        {
            dword_800C9C88[1] = 1;
            if (sub_800BC7DC(dword_800C9C7C) == 2)
            {
                dword_800C9C88[0] = 0x14;
            }
        }
    }
}

void sub_800BF2E8()
{
    int v;
    if ((sub_800BC7DC(dword_800C9C7C) == 0 && ((v = dword_800C9C88[0]) == 5 || v == 0x1A || v == 2 || v == 3 || v == 7))
        || (sub_800BC7DC(dword_800C9C7C) == 1 && ((v = dword_800C9C88[0]) - 2 < 2U || v == 8)))
    {
        sub_800BC838(0x8000);
        sub_800BC838(0x10000);
    }
    else
    {
        sub_800BC850(0x8000);
        sub_800BC850(0x10000);
    }
}

void sub_800BF3AC()
{
    unsigned char buf[3];
    buf[0] = 0xFF;
    buf[1] = 0xFF;
    buf[2] = 0xFF;
    StartScreenFlash_8001C02C(buf);
}

void sub_800BF3DC(int a, int b, int c, int d, int e)
{
    EventEntry* p = AllocEventEntry_80043AF8(dword_8008D778);
    if (p)
    {
        int* q = p->buffer;
        p->flags = (p->flags | 1) & 0xFFFF7FFF;
        q[0] = b;
        q[2] = 0;
        q[3] = 0;
        q[1] = c;
        q[4] = d;
        q[5] = e;
        q[6] = a;
        p->cb_8 = (EventEntryFn)sub_800BF4D0;
    }
}

int sub_800BF47C()
{
    EventNode* h = dword_8008D778;
    EventNode* n;
    int i = 0;
    int cnt = h->count;
    for (n = h; i < cnt; i++)
    {
        if ((n->entry.flags & 0x8001) == 1)
        {
            return 1;
        }
        n = n->next;
    }
    return 0;
}

extern void sub_800127D0(int a0, int a1, int a2, int a3);
void sub_800BF4D0(EventEntry* t, int* u)
{
    DVECTOR sxy;
    SVECTOR v;
    long p;
    long flag;
    int x;
    v.vx = ((unsigned short*)u[4])[0];
    v.vy = ((unsigned short*)u[4])[2];
    v.vz = ((unsigned short*)u[4])[4];
    v.vx -= dword_8008D600[0].field_0;
    v.vy -= dword_8008D600[1].field_0;
    v.vz -= dword_8008D600[2].field_0;
    RotTransPers(&v, (long*)&sxy, &p, &flag);
    u[2]++;
    if (u[2] > 0x10)
    {
        t->flags = (t->flags & ~1) | 0x8000;
        return;
    }
    if (u[2] > 8)
    {
        u[3] -= 4;
    }
    else
    {
        u[3] += 4;
    }
    x = u[1] / (0x11 - u[2]);
    x = -x;
    u[1] += x;
    if (u[0] == 0)
    {
        sub_800127D0(u[6], 0, x, 0);
        if (*(short*)(sub_80014390((unsigned char)u[6]) + 8) <= 0)
        {
            sub_800127B8((struct_obj_B*)sub_80014390((unsigned char)u[6]));
        }
    }
    if (u[0] == 1)
    {
        sub_800127D0(u[6], 2, x, 0);
    }
}

#if 0 // Not matched: cse keeps 500 in a register for case 2 (original reloads it), which reorders the init stores; tried if-chains, struct, returns, default
void sub_800BF648(short* p, int mode)
{
    p[0] = 500;
    p[1] = 0;
    p[2] = 0;
    p[3] = 0;
    p[4] = 0;
    p[5] = -0x2BC;
    p[6] = -0x578;
    switch (mode)
    {
    case 1:
        p[0] = 1000;
        return;
    case 0:
        return;
    case 2:
        p[0] = 0;
        p[4] = 1000;
        p[5] = 500;
        p[6] = 0x14D;
        return;
    }
}
#endif
INCLUDE_OVERLAY_ASM(battle, sub_800BF648);

#if 0 // Not matched: body matches with a goto inner loop (a for loop gets strength-reduced); prologue saves are not interleaved and a/b take s3/s2 in the original (s2/s3 here)
int sub_800BF6BC(unsigned short* a, int b)
{
    int r;
    unsigned int i;
    r = -1;
    do
    {
        i = 0;
    loop:
        if (i >= 4 || b == i)
        {
            a[i] += sub_800BF784(i);
            if ((short)a[i] >= 1000)
            {
                a[i] = 0;
                r = i;
                continue;
            }
        }
        i++;
        if (i < 7)
        {
            goto loop;
        }
    } while (r < 0);
    return r;
}
#endif
INCLUDE_OVERLAY_ASM(battle, sub_800BF6BC);

void sub_800BF770(short* p, int i)
{
    p[i] = 0x320;
}

int sub_800BF784(int a)
{
    unsigned char buf[0x18];
    int p = sub_80014390(a & 0xFF);
    if (p == 0)
    {
        return 0;
    }
    CalcEquippedStats_80033624(buf, p);
    return buf[4] + 10;
}

#if 0 // Not matched: body close with a goto loop; prologue saves are not interleaved with the arg copies in the original and b/f/table-base get different saved registers
typedef struct BatChance_a
{
    unsigned int mask;
    unsigned int chance;
} BatChance_a;
extern BatChance_a dword_800C9138[];
extern int GetEquipmentId_8003356C(unsigned char* p, unsigned int idx);
extern unsigned int Rand100_80013E30();
void sub_800BF7C4(unsigned char* p, short* a, short* b)
{
    unsigned int f = *(unsigned int*)p;
    unsigned int f0 = f;
    int i;
    BatChance_a* e;
    *a = 0;
    *b = 0;
    f = sub_800BFA34(f);
    if ((GetEquipmentId_8003356C(p, 2) & 0xFF) == 0x10)
    {
        f |= 0x4000;
    }
    if (f0 & 1)
    {
        *a = *(short*)(p + 0xA) / 10;
        f &= ~2;
    }
    else if (f & 0x4000)
    {
        *a = -(short)(*(short*)(p + 0xA) / 20);
    }
    if (f0 & 0x8000)
    {
        *b = -((p[0x44] >> 2) + 3);
        f &= ~0x8000;
    }
    if (f & 0x200)
    {
        *a = *(short*)(p + 8);
    }
    i = 0;
loop:
    e = &dword_800C9138[i];
    if (f0 & e->mask)
    {
        if (Rand100_80013E30() >= e->chance)
        {
            f &= ~e->mask;
        }
    }
    i++;
    if (i < 1)
    {
        goto loop;
    }
    *(unsigned int*)p = f;
}
#endif
INCLUDE_OVERLAY_ASM(battle, sub_800BF7C4);

int sub_800BF980(int x)
{
    int r = 0;
    if (x >= 0x29)
    {
        if (x < 0x39)
        {
            r = 1;
        }
        else if (x < 0xD3)
        {
            if (x > 0xC8)
            {
                r = 1;
            }
        }
    }
    return r;
}

int sub_800BF9B4(int x)
{
    int r = 0;
    switch (x)
    {
    case 0x29:
    case 0x2C:
    case 0x2E:
    case 0x30:
    case 0x31:
    case 0x32:
    case 0x33:
    case 0x37:
        r = 1;
        break;
    }
    return r;
}
INCLUDE_OVERLAY_ASM(battle, dword_800B67F0);

#if 0 // Not matched: x is copied to v1 and the mask is built before the load in the original; regalloc/schedule differ in every variant tried
void sub_800BF9F0(int a)
{
    unsigned int x = a;
    unsigned int* p = allMinionsBitfields_8008BD84;
    if (x < 0xE0)
    {
        unsigned int* q = &p[x >> 5];
        int m = 1 << (x & 0x1F);
        *q = m | *q;
    }
}
#endif
INCLUDE_OVERLAY_ASM(battle, sub_800BF9F0);

int sub_800BFA34(int x)
{
    int y = x & 0x3F8;
    return (x & ~0x3F8) | (y << 1);
}

#if 0 // Not matched: only the last test: andi goes to v1 instead of v0 (and branch sense/layout); tried ternary, if/else, r variable, int params
int sub_800BFA4C(unsigned int a, unsigned int b)
{
    if (a & 0x200)
    {
        return 0x13;
    }
    if (a & 2)
    {
        if (!(b & 2))
        {
            return 0x10;
        }
    }
    if (a & 0x8000)
    {
        if (!(b & 0x8000))
        {
            return 0x12;
        }
    }
    if (a & 1)
    {
        return 9;
    }
    if (b & 2)
    {
        if (!(a & 2))
        {
            return 0xF;
        }
    }
    if (b & 0x8000)
    {
        if (!(a & 0x8000))
        {
            return 0x11;
        }
    }
    if (!(a & 0x4000))
    {
        return 0x14;
    }
    return 0x19;
}
#endif
INCLUDE_OVERLAY_ASM(battle, sub_800BFA4C);

void sub_800BFAF8(int x)
{
    int a;
    switch (x)
    {
    case 9:
        a = 1;
        break;
    case 7:
        a = 8;
        break;
    case 11:
        a = 4;
        break;
    case 14:
        a = 0;
        break;
    case 18:
        a = 2;
        break;
    case 2:
        a = 3;
        break;
    case 13:
        a = 5;
        break;
    case 21:
        a = 7;
        break;
    case 22:
    default:
        return;
    }
    sub_80018430(a);
}

void sub_800BFB80()
{
    sub_800BFC10();
    sub_800BFC40();
    sub_800C01D8();
    sub_800C0440();
}

void sub_800BFBB8()
{
    StopAllEventEntries_80043B40(dword_8008B568);
    StopAllEventEntries_80043B40(dword_8008B564);
    StopAllEventEntries_80043B40((int*)dword_8008D4B0);
    StopAllEventEntries_80043B40((int*)dword_8008D63C);
}

void sub_800BFC10()
{
    dword_800C9DFD = 0;
    dword_800C9DFC = 0;
    dword_800C9170 = 0;
    dword_800C9174[0] = 0;
    dword_800C9174[1] = 0;
    dword_800C9174[2] = 0;
}

typedef struct BatXY_a
{
    short x;
    short y;
} BatXY_a;
extern int dword_800C9DF8;
extern int dword_800C9E24;
extern BatXY_a dword_800C9140[];
extern char* dword_800C9E28[];
extern BatXY_a dword_800C9E18[];
extern EventEntry* dword_800C9E08[];
extern void sub_800BFDEC();
extern void sub_800C0074();
void sub_800BFC40()
{
    EventEntry* e = AllocEventEntry_80043AF8((EventNode*)dword_8008B568);
    int m;
    int n;
    int i;
    int b;
    if (e)
    {
        m = sub_800A248C();
        n = GetCapturedMinionsFromBitfield_8003BA58(m);
        if (sub_800A2AB4())
        {
            m = 0x10;
        }
        dword_800C9DF8 = 0;
        dword_800C9E24 = 0;
        e->cb_8 = (EventEntryFn)sub_800BFDEC;
        e->flags = (e->flags | 1) & 0xFFFF7FFF;
        for (i = 0; i < 3; i++)
        {
            b = m & (1 << (i + 4));
            if (b != 0)
            {
                e = AllocEventEntry_80043AF8((EventNode*)dword_8008B564);
                if (e)
                {
                    BatXY_a* pp = (BatXY_a*)((char*)dword_800C9140 + ((n - 1) * 12 + i * 4));
                    short* q;
                    e->flags = (e->flags | 1) & 0xFFFF7FFF;
                    q = e->buffer;
                    *(int*)q = i;
                    *(int*)(q + 2) = 0;
                    q[4] = pp->x;
                    q[5] = pp->y;
                    q[6] = 0x64;
                    q[7] = 0x29;
                    e->cb_8 = (EventEntryFn)sub_800C0074;
                    dword_800C9E28[i] = (char*)q;
                    dword_800C9E18[i].x = pp->x;
                    dword_800C9E18[i].x = pp->x;
                    dword_800C9E18[i].y = pp->y;
                    dword_800C9E08[i] = e;
                }
            }
        }
    }
}

INCLUDE_OVERLAY_ASM(battle, sub_800BFDEC);

#if 0 // Not matched: one word: 'k = 1' reuses the compare constant (move s2,v1) instead of li; u must be copied after the early return
typedef struct BatWin_a
{
    int slot_0;
    int frame_4;
    short from_8[4];
    short rect_10[4];
} BatWin_a;
extern void sub_8002F1C8();
extern int dword_800C9164[];
void sub_800C0074(EventEntry* t, void* arg)
{
    int k;
    int m;
    int r;
    BatWin_a* u;
    if (dword_800B1228 & 0x10000)
    {
        return;
    }
    u = arg;
    r = sub_800A2AB4();
    k = 0;
    if (r != 1)
    {
        k = 1;
        if (sub_800A2AB4() != 2)
        {
            k = u->slot_0;
        }
    }
    m = sub_80014390((k + 4) & 0xFF);
    AddClipDrawAreaPrim_80033308((char*)pOT_8008D454 + 0x28);
    SetFontClutOffset_8003F900(1, 0);
    InterpolateWindowRect_8004196C(u->rect_10, u->from_8, u->frame_4, 4, 9);
    if (sub_800BF980(sub_800A2BE4(k)))
    {
        sub_8002F1C8(m, dword_800C9164[k], dword_800C9DFC, dword_800C9174[k], u->rect_10, 10, 1);
    }
    else
    {
        sub_8002F1C8(m, dword_800C9164[k], dword_800C9DFC, dword_800C9174[k], u->rect_10, 10, 0);
    }
    u->frame_4++;
    AddDrawAreaPrim_8003326C(u->rect_10, (char*)pOT_8008D454 + 0x28);
}
#endif
INCLUDE_OVERLAY_ASM(battle, sub_800C0074);

void sub_800C01D8()
{
    struct_cb* r = AllocEventEntry_80043AF8(dword_8008D4B0);
    if (r != 0)
    {
        unsigned char* p = (unsigned char*)r->field_14;
        r->flags_0 = (r->flags_0 | 1) & ~0x8000;
        *(int*)p = 0;
        *(short*)(p + 4) = 0x6E;
        *(short*)(p + 6) = 0xAC;
        *(short*)(p + 8) = 0x64;
        *(short*)(p + 10) = 0x29;
        r->fn_8 = (void (*)(struct_cb*, int*))sub_800C0254;
    }
}

INCLUDE_OVERLAY_ASM(battle, sub_800C0254);

void sub_800C0440()
{
    EventEntry* e = AllocEventEntry_80043AF8(dword_8008D63C);
    if (e)
    {
        dword_800C9D74 = 0;
        e->flags = (e->flags | 1) & 0xFFFF7FFF;
        *(int*)e->buffer = 0;
        e->cb_8 = (EventEntryFn)sub_800C04A4;
    }
}

#if 0 // Not matched: u and w swap saved registers (s1/s0); tried w types, decl order, pre-increment
typedef struct BatHelp_a
{
    unsigned int frame_0;
    short from_4[4];
    short rect_C[4];
} BatHelp_a;
extern unsigned char dword_800793C8[];
extern void DrawText_8003E91C(int mode, void* str, void* pos, int z);
extern void sub_8003F264(void* pos, int val, int ot);
extern void DrawUiColorWindow_800424C0();
void sub_800C04A4(EventEntry* t, BatHelp_a* u)
{
    int w;
    short pos[2];
    unsigned char* g;
    if (padPressed_8009194C & 0x100)
    {
        *(int*)&saveData_8008B570 ^= 0x10;
    }
    if (*(int*)&saveData_8008B570 & 0x10)
    {
        return;
    }
    if (dword_800C9D74 == 0)
    {
        return;
    }
    AddClipDrawAreaPrim_80033308(pOT_8008D454);
    w = MeasureTextWidth_8003E4C8(dword_800C9D74);
    g = dword_800793C8 + 0x14;
    if (*(int*)(g + 0x24) == dword_800C9D74)
    {
        w += 0x10;
    }
    u->from_4[2] = w + 4;
    u->from_4[3] = 0x14;
    u->from_4[0] = 0xA;
    u->from_4[1] = 0x88;
    pos[0] = u->from_4[0] + 2;
    pos[1] = u->from_4[1] + 3;
    DrawText_8003E91C(2, (void*)dword_800C9D74, pos, 0);
    if (*(int*)(g + 0x24) == dword_800C9D74)
    {
        pos[0] += w;
        pos[1] += 3;
        sub_8003F264(pos, sub_800AD8E4(), 0);
    }
    InterpolateWindowRect_8004196C(u->rect_C, u->from_4, u->frame_0, 4, 7);
    DrawUiColorWindow_800424C0(u->rect_C, 0, pOT_8008D454, 0);
    if (++u->frame_0 >= 5)
    {
        u->frame_0 = 4;
    }
    AddDrawAreaPrim_8003326C(u->rect_C, pOT_8008D454);
}
#endif
INCLUDE_OVERLAY_ASM(battle, sub_800C04A4);

INCLUDE_OVERLAY_ASM(battle, sub_800C064C);

int sub_800C0904(unsigned char* p)
{
    int n = 0;
    int i;
    int r;
    for (i = 0; i < 4; i++)
    {
        if (p[i])
        {
            n++;
        }
    }
    if (n == 1)
    {
        r = -1000;
    }
    else if (n == 2)
    {
        if (p[3] && p[1])
        {
            if (p[1] < p[3])
            {
                r = 0xF5;
            }
            else
            {
                r = 0x41;
            }
        }
        else if (p[0] && p[2])
        {
            if (p[2] < p[0])
            {
                r = 0x14F;
            }
            else
            {
                r = 0x9B;
            }
        }
        else
        {
            r = sub_800C09D4(p);
        }
    }
    else
    {
        r = sub_800C09D4(p);
    }
    return r;
}

#if 0 // Not matched: temp register numbering of the eight products (same function as SHOP sub_800BF3B4)
extern short word_80084540[];
int sub_800C09D4(unsigned char* p)
{
    int t1 = word_80084540[0x2E3] * p[0];
    int t2 = word_80084540[0xEE3] * p[0];
    int t3 = word_80084540[0xEE3] * p[3];
    int t4 = word_80084540[0xAE3] * p[3];
    int t5 = word_80084540[0xAE3] * p[2];
    int t6 = word_80084540[0x6E3] * p[2];
    int t7 = word_80084540[0x6E3] * p[1];
    int t8 = word_80084540[0x2E3] * p[1];
    return ratan2Degrees_8003B56C(t1 + t3 + t5 + t7, t2 + t4 + t6 + t8);
}
#endif
INCLUDE_OVERLAY_ASM(battle, sub_800C09D4);

void sub_800C0A94()
{
}

int sub_800C0A9C()
{
    int n = CountMinions_80010548(3);
    int r = 0;
    int i;
    for (i = 0; i < n; i++)
    {
        r |= 1 << (i + 1);
    }
    return r;
}

int sub_800C0AEC(int a, int* b, int c)
{
    char buf[0x38];
    int h;
    if (sub_800C0D50() != -1)
    {
        return 0;
    }
    h = (int)GetMinion_80010598(3, a);
    if (h == 0)
    {
        return 0;
    }
    dword_800C9188 = h;
    sub_800C064C(h, buf, dword_8007DC74);
    StartModelTask_80010850(buf);
    dword_800C9190.f4 = b[0];
    dword_800C9190.f8 = b[1];
    dword_800C9190.fc = b[2];
    dword_800C918C = a;
    dword_800C9190.f10 = c;
    return 1;
}

int sub_800C0BA0()
{
    if (sub_800C0D50() >= 0)
    {
        FreeModelTask_8001098C(0);
        DestroyActor_8001D600(dword_800C9190.obj);
        dword_800C918C = -1;
        return 1;
    }
    return 0;
}

extern int* CreateActor_8001D45C(int a0);
extern int sub_80010A44();
extern void sub_80019B14(int a, int b, int c);
extern int dword_80079140;
int sub_800C0BF0()
{
    struct
    {
        int field_0;
        int field_4;
        int pos[3];
        short rot[3];
        short pad_1A;
        int field_1C;
        int field_20;
        int field_24;
        int field_28;
        int field_2C;
        int field_30;
        int* field_34;
        int field_38;
        int field_3C;
        int field_40;
        int field_44;
        int field_48;
        int field_4C;
    } s;
    void* m;
    int k;
    int x;
    // RunModelTask_80010A10 is declared void in funcs.h, but its result is used here
    if (((int (*)(int))RunModelTask_80010A10)(0) != 0)
    {
    m = (void*)sub_80010A44(0);
    k = sub_80019A80(((unsigned char*)dword_800C9188)[0xC8]);
    s.field_0 = -1;
    s.field_4 = 2;
    s.pos[0] = dword_800C9190.f4;
    s.pos[1] = dword_800C9190.f8;
    s.pos[2] = dword_800C9190.fc;
    s.rot[0] = 0;
    s.rot[1] = dword_800C9190.f10;
    s.rot[2] = 0;
    s.field_1C = 3;
    s.field_20 = 4;
    s.field_24 = -1;
    s.field_28 = 0x1000;
    s.field_2C = 4;
    s.field_30 = 0;
    s.field_48 = (int)m;
    s.field_34 = &dword_80079140;
    s.field_38 = (int)sub_80024E90(m, k);
    s.field_3C = (int)sub_80024EC8(m, k);
    s.field_40 = (int)sub_80024E38(m);
    s.field_44 = (int)sub_80024E64(m);
    s.field_4C = 1;
    dword_800C9190.obj = (char*)CreateActor_8001D45C((int)&s);
    sub_8001D68C((struct_obj_A*)dword_800C9190.obj, 0);
    x = (int)sub_80024F00(m, k);
    sub_80019B14(*(int*)(dword_800C9190.obj + 0x134), x, (int)sub_80024F38(m, k));
        return 1;
    }
    return 0;
}

int sub_800C0D50()
{
    return dword_800C918C;
}

int sub_800C0D60()
{
    return sub_8001E1C8((void*)dword_800C9190.obj);
}

int sub_800C0D88()
{
    return sub_8001E1DC(dword_800C9190.obj);
}

void sub_800C0DB0(int a)
{
    sub_8001DB00(dword_800C9190.obj, a, 0x55);
}

#if 0 // Not matched: struct-return copy: 'move v0,s1' is scheduled before the lwl/lwr copy (original: after); tried explicit out-pointer form
BatCol_a* sub_800C0DDC(BatCol_a* out, int* p, int c)
{
    BatCol_a buf;
    int mask;
    memset(&buf, 0, 4);
    if (p[0] != 0x14 && (p[2] & (mask = 1 << (dword_800C918C + 1))))
    {
        sub_80018A4C(&buf, dword_800C9190.obj, p, 0, c);
    }
    *out = buf;
    return out;
}
#endif
INCLUDE_OVERLAY_ASM(battle, sub_800C0DDC);

int sub_800C0E84(int* p)
{
    int mask;
    if (p[0] == 0x14)
    {
        return 0;
    }
    mask = 1 << (dword_800C918C + 1);
    if (p[2] & mask)
    {
        sub_8001E28C(dword_800C9190.obj);
    }
    return 1;
}

void sub_800C0EE8(int a)
{
    sub_80018E5C(dword_800C9190.obj, a);
}

int sub_800C0F14()
{
    return 0;
}

void sub_800C0F1C()
{
    sub_80018EBC(dword_800C9190.obj, sub_800C0F78(dword_800C918C));
}

void sub_800C0F54(int a)
{
    GetMinionName_800106F8(3, a);
}

int sub_800C0F78(int a)
{
    GetMinionStatus_800107A0(3, a);
}

char* sub_800C0F9C()
{
    return dword_800C9190.obj + 0x38;
}

int sub_800C0FAC()
{
    return *(int*)(dword_800C9190.obj + 0x1C4);
}

void sub_800C0FC4(int* p)
{
    char* q = dword_800C9190.obj;
    p[0] = *(int*)(q + 0x14C);
    p[1] = (int)(q + 0x38);
    p[2] = *(int*)(q + 0x1C4);
    p[3] = *(int*)(q + 0x1C8);
    p[11] = *(int*)(q + 0x144);
    p[12] = (int)(q + 0x2C);
}

int sub_800C100C(int a)
{
    int h = (int)GetMinion_80010598(3, a);
    if (h)
    {
        return h + 0xDE;
    }
    return 0;
}

int sub_800C103C(int a)
{
    int h = (int)GetMinion_80010598(3, a);
    if (h)
    {
        return h + 0xF4;
    }
    return 0;
}

void sub_800C106C(unsigned int* a, int* b)
{
    if (--b[1] < 0)
    {
        *a = (*a & ~1) | 0x8000;
        StopSeqSlot_80031334(b[0]);
    }
}

extern EventNode* dword_8008D60C;
void sub_800C10B8(int a, int b)
{
    EventEntry* e = AllocEventEntry_80043AF8(dword_8008D60C);
    if (a > 0 && e)
    {
        int* q;
        PlaySeqSlot_80031160(b, 1);
        e->flags = (e->flags | 1) & 0xFFFF7FFF;
        q = e->buffer;
        q[0] = b;
        q[1] = a;
        e->cb_8 = (EventEntryFn)sub_800C106C;
    }
}

void sub_800C1140(unsigned int* a, short* b)
{
    if (--*(int*)(b + 2) < 0)
    {
        *a = (*a & ~1) | 0x8000;
        SfxKeyOff_80031574(b[4], b[0]);
    }
}

void sub_800C1190(int a, int b)
{
    EventEntry* e = AllocEventEntry_80043AF8(dword_8008D60C);
    if (a > 0 && e)
    {
        int* q;
        e->flags = (e->flags | 1) & 0xFFFF7FFF;
        q = e->buffer;
        q[1] = a;
        *(short*)(q + 2) = SfxKeyOn_800314F4(b);
        q[0] = b;
        e->cb_8 = (EventEntryFn)sub_800C1140;
    }
}

INCLUDE_OVERLAY_ASM(battle, sub_800C1220);

INCLUDE_OVERLAY_ASM(battle, sub_800C1450);

extern void sub_800C17EC();
void sub_800C1654(int* p, short* q, int c, int d, int e, int f)
{
    int i;
    for (i = 0; i < 30; i++)
    {
        EventEntry* ev = AllocEventEntry_80043AF8(dword_8008D60C);
        if (ev)
        {
            char* b = ev->buffer;
            ev->flags = (ev->flags | 1) & 0xFFFF7FFF;
            *(int*)(b + 0x1C) = p[0];
            *(int*)(b + 0x20) = p[1];
            *(int*)(b + 0x24) = p[2];
            *(int*)(b + 0x10) = p[0];
            *(int*)(b + 0x14) = p[1];
            *(int*)(b + 0x18) = p[2];
            *(short*)(b + 0x34) = q[0];
            *(short*)(b + 0x36) = q[1];
            *(short*)(b + 0x38) = q[2];
            *(int*)(b + 0x3C) = c;
            *(int*)(b + 0x28) = ((rand() & 0x7F) - 0x3F) << 10;
            *(int*)(b + 0x2C) = -(rand() & 0x3F) << 10;
            *(int*)(b + 0x30) = ((rand() & 0x7F) - 0x3F) << 10;
            *(short*)(b + 0x34) = 0;
            *(short*)(b + 0x36) = 0;
            *(short*)(b + 0x38) = 0;
            *(int*)b = 0;
            *(short*)(b + 8) = ((rand() & 0xFFF) >> 1) + 0x800;
            *(int*)(b + 0x40) = e;
            *(int*)(b + 0x44) = f;
            ev->cb_8 = (EventEntryFn)sub_800C17EC;
        }
    }
}

INCLUDE_OVERLAY_ASM(battle, sub_800C17EC);

extern void sub_800C1B2C();
void sub_800C1A5C(int* p, short* q, int c, int d)
{
    EventEntry* e = AllocEventEntry_80043AF8(dword_8008D60C);
    if (e)
    {
        char* b;
        e->flags = (e->flags | 1) & 0xFFFF7FFF;
        b = e->buffer;
        *(int*)(b + 0x10) = p[0];
        *(int*)(b + 0x14) = p[1];
        *(int*)(b + 0x18) = p[2];
        *(short*)(b + 0x34) = q[0];
        *(short*)(b + 0x36) = q[1];
        *(short*)(b + 0x38) = q[2];
        *(int*)(b + 0x3C) = c;
        *(int*)b = 0;
        *(short*)(b + 8) = d;
        e->cb_8 = (EventEntryFn)sub_800C1B2C;
    }
}

#if 0 // Not matched: register permutation only (u/d/offset get s2/s0/s1, original s0/s1/s2); tried decl order and an explicit offset counter
typedef struct BatFx_a
{
    int frame_0;
    int f4;
    short speed_8;
    short padA;
    int padC;
    int pos_10[3];
    char pad1C[0x18];
    short rot_34[4];
    int* anim_3C;
} BatFx_a;
extern void sub_80044010();
void sub_800C1B2C(EventEntry* t, BatFx_a* u)
{
    int* d = u->anim_3C;
    int i;
    char* e;
    if (u->frame_0 / 4096 < d[0])
    {
        for (i = 0; i < ((unsigned char*)d[1])[u->frame_0 / 4096]; i++)
        {
            e = ((char**)d[2])[u->frame_0 / 4096] + i * 0x1C;
            sub_80044010(&d[3], u->pos_10, u->rot_34, e, e + 4, e + 8, e + 0xC, e + 0x10, e + 0x18, 0, 0x30, pOT_8008D690);
        }
        u->frame_0 += u->speed_8;
    }
    else
    {
        t->flags = (t->flags & ~1) | 0x8000;
    }
}
#endif
INCLUDE_OVERLAY_ASM(battle, sub_800C1B2C);

extern void sub_800C1DA4();
void sub_800C1C5C(int* p, short* q, int c)
{
    int i;
    for (i = 0; i < 16; i++)
    {
        EventEntry* e = AllocEventEntry_80043AF8(dword_8008D60C);
        if (e)
        {
            char* b = e->buffer;
            e->flags = (e->flags | 1) & 0xFFFF7FFF;
            *(int*)(b + 0x10) = p[0];
            *(int*)(b + 0x14) = p[1];
            *(int*)(b + 0x18) = p[2];
            *(short*)(b + 0x34) = q[0];
            *(short*)(b + 0x36) = q[1];
            *(short*)(b + 0x38) = q[2];
            *(int*)(b + 0x3C) = c;
            *(int*)(b + 0x28) = ((rand() & 0x3F) - 0x1F) << 10;
            *(int*)(b + 0x2C) = ((rand() & 0x3F) - 0x1F) << 10;
            *(int*)(b + 0x30) = ((rand() & 0x3F) - 0x1F) << 10;
            *(int*)b = 0;
            *(short*)(b + 8) = ((rand() & 0xFFF) >> 1) + 0x800;
            e->cb_8 = (EventEntryFn)sub_800C1DA4;
        }
    }
}

INCLUDE_OVERLAY_ASM(battle, sub_800C1DA4);

extern void sub_800C2170();
void sub_800C1FFC(int* p, short* q, int c, int d, int n)
{
    int i;
    for (i = 0; i < n; i++)
    {
        EventEntry* e = AllocEventEntry_80043AF8(dword_8008D60C);
        if (e)
        {
            char* b = e->buffer;
            e->flags = (e->flags | 1) & 0xFFFF7FFF;
            *(int*)(b + 0x1C) = p[0];
            *(int*)(b + 0x20) = p[1];
            *(int*)(b + 0x24) = p[2];
            *(short*)(b + 0x34) = q[0];
            *(short*)(b + 0x36) = q[1];
            *(short*)(b + 0x38) = q[2];
            *(int*)(b + 0x3C) = c;
            *(int*)(b + 0x28) = ((rand() & 0x3F) - 0x1F) << 10;
            *(int*)(b + 0x2C) = -(rand() & 0x1F) << 10;
            *(int*)(b + 0x30) = ((rand() & 0x3F) - 0x1F) << 10;
            *(int*)(b + 0x10) = 0;
            *(int*)(b + 0x14) = 0;
            *(int*)(b + 0x18) = 0;
            *(int*)b = 0;
            *(short*)(b + 8) = d + ((rand() & 0xFFF) >> 1) + 0x800;
            e->cb_8 = (EventEntryFn)sub_800C2170;
        }
    }
}

INCLUDE_OVERLAY_ASM(battle, sub_800C2170);

INCLUDE_OVERLAY_ASM(battle, sub_800C23D0);

typedef struct BatShard_a
{
    int frame_0;
    int f4;
    short f8;
    short fA;
    int scale_C;
    int pos_10[3];
    int base_1C[3];
    int vel_28[3];
    short rot_34[4];
    int* anim_3C;
} BatShard_a;
void sub_800C273C(EventEntry* t, BatShard_a* u)
{
    int v[4];
    int s[3];
    u->vel_28[1] += 0x1000;
    u->vel_28[0] = u->vel_28[0] * 31 / 32;
    u->vel_28[1] = u->vel_28[1] * 31 / 32;
    u->vel_28[2] = u->vel_28[2] * 31 / 32;
    u->pos_10[0] += u->vel_28[0];
    u->pos_10[1] += u->vel_28[1];
    u->pos_10[2] += u->vel_28[2];
    if (u->pos_10[1] > 0)
    {
        u->vel_28[1] = -u->vel_28[1] * 3 / 4;
        u->pos_10[1] = 0;
        if (u->vel_28[1] >= -0xFFF)
        {
            t->flags = (t->flags & ~1) | 0x8000;
        }
    }
    u->rot_34[2] += u->rot_34[3];
    s[0] = s[1] = s[2] = u->scale_C;
    v[0] = u->base_1C[0] + u->pos_10[0] / 1024;
    v[1] = u->base_1C[1] + u->pos_10[1] / 1024;
    v[2] = u->base_1C[2] + u->pos_10[2] / 1024;
    sub_8004D1EC((int)u->anim_3C, (int)pOT_8008D690, (int)v, (int)u->rot_34, (int)stru_8008D534, 0x30, (int)s);
    u->frame_0++;
}

INCLUDE_OVERLAY_ASM(battle, sub_800C2914);

void sub_800C2CD8(EventEntry* t, BatShard_a* u)
{
    int* d = u->anim_3C;
    int v[4];
    int s[3];
    if (u->frame_0 >= 0x1A)
    {
        if (u->frame_0 < 0x1E)
        {
            u->pos_10[0] += u->vel_28[0];
            u->pos_10[1] += u->vel_28[1];
            u->pos_10[2] += u->vel_28[2];
        }
        else
        {
            t->flags = (t->flags & ~1) | 0x8000;
        }
    }
    u->rot_34[2] += 0xAA;
    s[0] = s[1] = s[2] = u->scale_C;
    v[0] = u->base_1C[0] + u->pos_10[0] / 1024;
    v[1] = u->base_1C[1] + u->pos_10[1] / 1024;
    v[2] = u->base_1C[2] + u->pos_10[2] / 1024;
    sub_8004D1EC(d[1], (int)pOT_8008D690, (int)v, (int)u->rot_34, (int)stru_8008D534, 0x30, (int)s);
    u->frame_0++;
}

extern void sub_800C2FC8();
void sub_800C2E28(int* p, short* q, int c, int d, int e, int n)
{
    int i;
    for (i = 0; i < n; i++)
    {
        EventEntry* ev = AllocEventEntry_80043AF8(effectObjects_8008B4A8);
        if (ev)
        {
            char* b;
            ev->flags = (ev->flags | 1) & 0xFFFF7FFF;
            b = ev->buffer;
            *(int*)(b + 0x44) = p[0];
            *(int*)(b + 0x48) = p[1];
            *(int*)(b + 0x4C) = p[2];
            *(int*)(b + 0x50) = p[0];
            *(int*)(b + 0x54) = p[1];
            *(int*)(b + 0x58) = p[2];
            *(int*)(b + 0x5C) = p[0];
            *(int*)(b + 0x60) = p[1];
            *(int*)(b + 0x64) = p[2];
            *(int*)(b + 0x68) = p[0];
            *(int*)(b + 0x6C) = p[1];
            *(int*)(b + 0x70) = p[2];
            *(short*)(b + 0x80) = q[0];
            *(short*)(b + 0x82) = q[1];
            *(short*)(b + 0x84) = q[2];
            *(int*)(b + 0x88) = c;
            *(int*)(b + 0x8C) = d;
            *(short*)(b + 0x80) = 0;
            *(short*)(b + 0x84) = 0;
            *(int*)b = 0;
            *(int*)(b + 4) = 0;
            *(short*)(b + 8) = e;
            *(short*)(b + 0x82) = (i << 12) / n;
            ev->cb_8 = (EventEntryFn)sub_800C2FC8;
        }
    }
}

INCLUDE_OVERLAY_ASM(battle, sub_800C2FC8);

extern int sub_80020F00(void* p, int a, int b);
extern void sub_800C33E4();
int sub_800C32DC(int a0, int a1, int a2, int a3)
{
    int* pos = (int*)a0;
    EventEntry* e = AllocEventEntry_80043AF8(effectObjects_8008B4A8);
    char* b;
    int idx;
    int t;
    if (e != 0)
    {
    b = e->buffer;
    *(int*)(b + 0x44) = pos[0];
    *(int*)(b + 0x48) = pos[1];
    *(int*)(b + 0x4C) = pos[2];
    *(int*)b = 0;
    *(short*)(b + 8) = 0;
    *(short*)(b + 0x82) = a3;
    idx = sub_80020F00(effectFile_80091BD0, 1, a1);
    e->flags = (e->flags | 1) & 0xFFFF7FFF;
    t = effectFile_80091BD0[0x28 / 4] + idx * 28;
    *(int*)(b + 0x88) = t + a2 * 28;
    e->cb_8 = (EventEntryFn)sub_800C33E4;
    return *(int*)(t + 0x14);
    }
    return -1;
}

INCLUDE_OVERLAY_ASM(battle, sub_800C33E4);

typedef struct BatGlow_a
{
    int frame_0;
    int end_4;
    char pad8[0x14];
    int* base_1C;
    int* path_20;
    char pad24[0xC];
    int f30;
    char pad34[0x10];
    char f44[0x44];
    int* f88;
    char pad8C[8];
    int* f94;
    int idx_98;
    char pad9C[4];
    int* scale_A0;
} BatGlow_a;

extern char dword_800795D4[];
extern void sub_800C3B50(int* p, int id);
extern void sub_8003A6C4();
extern void sub_80021804(int* p, int heap);
extern void free3_8003FC6C(void* p);
extern void sub_800C4090(int a0, int a1, int c, int a3);

void sub_800C371C(EventEntry* t, void* arg)
{
    unsigned char col[4] = { 0xE8, 0xE8, 0x80, 0 };
    BatGlow_a* u = arg;
    int* m = u->f88;
    if (u->frame_0 < u->end_4 && effectOutcomeFlag_8008D780 == 0)
    {
        int s[4];
        int v[4];
        int a;
        u->f30 += 0x100;
        if (u->f30 > 0x1000)
        {
            u->f30 = 0x1000;
        }
        s[0] = u->scale_A0[0] * 3 / 2;
        s[1] = u->scale_A0[1] * 3 / 2;
        s[2] = u->scale_A0[2] * 3 / 2;
        a = u->f30;
        v[0] = u->path_20[u->idx_98 * 3 + 0] + u->base_1C[0];
        v[1] = u->path_20[u->idx_98 * 3 + 1] + u->base_1C[1];
        v[2] = u->path_20[u->idx_98 * 3 + 2] + u->base_1C[2];
        sub_8003A6C4(a, m[1], m[1] + 0x54, u->f94);
        sub_8004D1EC(m[1], (int)pOT_8008D690, (int)v, (int)dword_800795D4, (int)stru_8008D534, ((0x1000 - a) << 16) | 0xB0, (int)s);
        sub_800C4090((int)u->f44, (int)col, 0x5DC, u->f30);
        u->frame_0++;
    }
    else
    {
        int s[4];
        int v[4];
        int a;
        s[0] = u->scale_A0[0] * 3 / 2;
        s[1] = u->scale_A0[1] * 3 / 2;
        s[2] = u->scale_A0[2] * 3 / 2;
        a = u->f30;
        v[0] = u->path_20[u->idx_98 * 3 + 0] + u->base_1C[0];
        v[1] = u->path_20[u->idx_98 * 3 + 1] + u->base_1C[1];
        v[2] = u->path_20[u->idx_98 * 3 + 2] + u->base_1C[2];
        sub_8003A6C4(a, m[1], m[1] + 0x54, u->f94);
        sub_8004D1EC(m[1], (int)pOT_8008D690, (int)v, (int)dword_800795D4, (int)stru_8008D534, ((0x1000 - a) << 16) | 0xB0, (int)s);
        if (u->f30 == 0x1000)
        {
            sub_800C3B50(v, 0x25);
        }
        sub_800C4090((int)u->f44, (int)col, 0x5DC, u->f30);
        if (u->f30 <= 0)
        {
            sub_800C410C();
            sub_80021804(u->f94, 1);
            free3_8003FC6C(u->f94);
            t->flags = (t->flags & ~1) | 0x8000;
        }
        u->f30 -= 0x100;
    }
}

INCLUDE_OVERLAY_ASM(battle, dword_800B684C);

#if 0 // Not matched: regalloc only: the 0xFFFF7FFF mask and the effect-file base swap saved registers (orig s0/s3); body and schedule otherwise match
extern char* dword_8008B4A4;
extern void PlaySfx_80031494(int id);
extern void sub_800C3DF8();
extern void sub_800C3D34();
void sub_800C3B50(int* p, int id)
{
    EventEntry* e = AllocEventEntry_80043AF8(effectObjects_8008B4A8);
    char* b;
    int* ent;
    int* q;
    int f;
    int idx;
    if (e == 0)
    {
        return;
    }
    b = e->buffer;
    *(int*)(b + 0x44) = p[0];
    *(int*)(b + 0x48) = p[1];
    *(int*)(b + 0x4C) = p[2];
    *(int*)b = 0;
    *(short*)(b + 0xE) = sub_80020F00(effectFile_80091BD0, 0, id);
    *(int*)(b + 0x30) = 0x1000;
    *(int*)(b + 0x34) = 0;
    *(short*)(b + 0x84) = 0;
    *(short*)(b + 0x82) = 0;
    *(short*)(b + 0x80) = 0;
    *(int*)(b + 0x38) = 0;
    *(int*)(b + 0x3C) = -0xC8;
    *(int*)(b + 0x40) = 0;
    f = (&effectOutcomeFlag_8008D780)[1];
    e->flags = (e->flags | 1) & 0xFFFF7FFF;
    if (f == 0)
    {
    idx = sub_80020F00(effectFile_80091BD0, 1, 0x1F);
    e->flags = (e->flags | 1) & 0xFFFF7FFF;
    ent = (int*)(effectFile_80091BD0[0x28 / 4] + idx * 28);
    *(int**)(b + 0x88) = ent;
    *(void**)(b + 0x94) = malloc3_8003FC4C(0x54);
    sub_800218A8(ent[1], *(void**)(b + 0x94), 1);
    sub_80039FE4(ent[1], ent[1] + 0x54, *(int*)(b + 0x94));
    q = *(int**)(dword_8008B4A4 + 0x24);
    *(int*)(b + 0x44) = q[0x5E4 / 4];
    *(int*)(b + 0x48) = q[0x5E8 / 4];
    *(int*)(b + 0x4C) = q[0x5EC / 4];
    *(int*)(b + 0x44) += ((int*)levantPos_8008BD18)[0];
    *(int*)(b + 0x48) += ((int*)levantPos_8008BD18)[1];
    *(int*)(b + 0x4C) += ((int*)levantPos_8008BD18)[2];
    e->cb_8 = (EventEntryFn)sub_800C3D34;
    PlaySfx_80031494(0x3F);
    }
    else
    {
        PlaySfx_80031494(0x47);
        e->cb_8 = (EventEntryFn)sub_800C3DF8;
    }
}
#endif
INCLUDE_OVERLAY_ASM(battle, sub_800C3B50);

typedef struct BatFade_a
{
    char pad0[0x30];
    int f30;
    char pad34[0x10];
    char f44[0x3C];
    char f80[8];
    int* f88;
    char pad8C[8];
    int* f94;
} BatFade_a;

extern void sub_8003A6C4();
extern void sub_80021804(int* p, int heap);
extern void free3_8003FC6C(void* p);

void sub_800C3D34(EventEntry* t, BatFade_a* u)
{
    int* m = u->f88;
    int v = u->f30 - 0x100;
    u->f30 = v;
    if (v > 0)
    {
        sub_8003A6C4(v, m[1], m[1] + 0x54, u->f94);
    }
    else
    {
        t->flags = (t->flags & ~1) | 0x8000;
        sub_80021804(u->f94, 1);
        free3_8003FC6C(u->f94);
    }
    sub_8004D1EC(m[1], (int)pOT_8008D690, (int)u->f44, (int)u->f80, (int)stru_8008D534, ((0x1000 - u->f30) << 16) | 0xB0, 0);
}

INCLUDE_OVERLAY_ASM(battle, sub_800C3DF8);

extern int dword_8008D680[3];
extern short dword_8008D418[3];
extern int dword_8008D3F0;
void sub_800C4090(int a0, int a1, int c, int a3)
{
    int* a = (int*)a0;
    unsigned char* b = (unsigned char*)a1;
    unsigned int d = a3;
    dword_8008D680[0] = a[0];
    dword_8008D680[1] = a[1];
    dword_8008D680[2] = a[2];
    dword_8008D3F0 = c;
    dword_8008D418[0] = b[0] * d >> 7;
    dword_8008D418[1] = b[1] * d >> 7;
    dword_8008D418[2] = b[2] * d >> 7;
}

extern int dword_8008D3F0;
void sub_800C410C()
{
    dword_8008D3F0 = 0;
}

INCLUDE_OVERLAY_ASM(battle, sub_800C4118);

void sub_800C4328(BatTask* t)
{
    Minion* s = (Minion*)t->f14;
    short x = sub_800334D8(s);
    short y = sub_800334CC(s);
    if (x < (short)(y / 10))
    {
        sub_800C6AFC(t, 6, 0);
    }
    else if (rand() & 1)
    {
        sub_800C6AFC(t, 6, 1);
    }
    else
    {
        sub_800C6AFC(t, 0, 0);
    }
}

void sub_800C43D8(BatTask* t)
{
    if (rand(t) & 1)
    {
        sub_800C6AFC(t, 1, 8);
    }
    else
    {
        sub_800C6AFC(t, 1, 6);
    }
}

void sub_800C4424(BatTask* t)
{
    if (rand(t) & 1)
    {
        sub_800C6AFC(t, 6, 2);
    }
    else
    {
        sub_800C6AFC(t, 0, 0);
    }
}

extern void sub_800C6AFC();
void sub_800C4470(int a)
{
    sub_800C6AFC(a, 1, 0x14);
}

void sub_800C4494(BatTask* t)
{
    int x = rand();
    if (x % 3)
    {
        sub_800C6AFC(t, 6, 3);
    }
    else
    {
        sub_800C6AFC(t, 0, 0);
    }
}
void sub_800C44FC(BatTask* t)
{
    if (rand(t) & 1)
    {
        sub_800C6AFC(t, 6, 1);
    }
    else
    {
        sub_800C6AFC(t, 6, 2);
    }
}

void sub_800C4548(BatTask* t)
{
    if (sub_800C6DF8(t, 0xD) == 0)
    {
        if (rand() & 1)
        {
            sub_800C6C44(t);
        }
        else
        {
            sub_800C6AFC(t, 0, 0);
        }
    }
}
void sub_800C45A8(BatTask* t)
{
    if (sub_800C6EC8(t, 0x3F8) == 0 && rand() % 10 < 7)
    {
        sub_800C6AFC(t, 6, 0);
    }
    else if (sub_800C6EC8(t, 2) == 0 && rand() % 10 < 7)
    {
        sub_800C6AFC(t, 6, 1);
    }
    else if (sub_800C6EC8(t, 1) == 0 && rand() % 10 < 7)
    {
        sub_800C6AFC(t, 6, 2);
    }
    else
    {
        sub_800C6A68(t);
    }
}

extern void sub_800C473C();
void sub_800C46FC()
{
    sub_800C473C();
}

void sub_800C471C()
{
    sub_800C473C();
}

INCLUDE_OVERLAY_ASM(battle, sub_800C473C);

int sub_800C4A40(BatTask* t)
{
    int r;
    if (rand() & 1)
    {
        if (sub_800C6EC8(t, 0x3F8) == 0)
        {
            r = sub_800C6BD0(t, 0x13);
        }
        else
        {
            r = sub_800C6A8C(t);
        }
        if (r)
        {
            return r;
        }
        if (sub_800C6EC8(t, 2) == 0)
        {
            r = sub_800C6BD0(t, 0x12);
        }
        else
        {
            r = sub_800C6A8C(t);
        }
        if (r)
        {
            return r;
        }
        if (sub_800C6EC8(t, 1) == 0)
        {
            r = sub_800C6BD0(t, 0x11);
        }
        else
        {
            r = sub_800C6A8C(t);
        }
        if (r)
        {
            return r;
        }
        r = sub_800C6BD0(t, 0x14);
        if (r == 0)
        {
            r = sub_800C6A8C(t);
        }
        return r;
    }
    return sub_800C6C58(t);
}

int sub_800C4B34(BatTask* t)
{
    int r;
    Minion* s = (Minion*)t->f10;
    short x = sub_800334D8(s);
    short y = sub_800334CC(s);
    if (x < (short)(y / 3))
    {
        r = sub_800C6A8C(t);
        if (r)
        {
            return r;
        }
        if (rand() & 1)
        {
            r = sub_800C6C44(t);
            if (r)
            {
                return r;
            }
        }
    }
    return sub_800C6A68(t);
}

int sub_800C4BE4(BatTask* t)
{
    int r;
    Minion* s = (Minion*)t->f10;
    r = sub_800C6DF8(t, 0xD);
    if (r)
    {
        return r;
    }
    {
        short x = sub_800334D8(s);
        short y = sub_800334CC(s);
        if (x < y)
        {
            if (rand() & 1)
            {
                r = sub_800C6C44(t);
                if (r)
                {
                    return r;
                }
            }
        }
    }
    return sub_800C6A68(t);
}
int sub_800C4C74(BatTask* t)
{
    int r;
    if (sub_800C6EC8(t, 1) == 0)
    {
        r = sub_800C6A8C(t);
        if (r)
        {
            return r;
        }
    }
    return sub_800C6A68(t);
}

int sub_800C4CBC(BatTask* t)
{
    int r;
    int m = rand() % 100;
    if (m < 30)
    {
        r = sub_800C6BD0(t, 0);
        if (r)
        {
            return r;
        }
    }
    return sub_800C6A68(t);
}

int sub_800C4D38(BatTask* t)
{
    int r;
    Minion* s = (Minion*)t->f10;
    short x = sub_800334D8(s);
    short y = sub_800334CC(s);
    if (x < y / 4)
    {
        r = sub_800C6A8C(t);
        if (r)
        {
            return r;
        }
    }
    return sub_800C6A68(t);
}

int sub_800C4DB8(BatTask* t)
{
    int r;
    int m = rand() % 100;
    if (m < 50)
    {
        r = sub_800C6BD0(t, 9);
        if (r)
        {
            return r;
        }
    }
    return sub_800C6A68(t);
}

int sub_800C4E34(BatTask* t)
{
    int r;
    if (rand() % 10 < 7)
    {
        r = sub_800C6A8C(t);
        if (r)
        {
            return r;
        }
    }
    return sub_800C6A68(t);
}

int sub_800C4EA8(BatTask* t)
{
    int r;
    int m = rand() % 100;
    if (dword_800C8B30 < 2)
    {
        if (sub_800C6EC8(t, 2) == 0 && m < 40)
        {
            r = sub_800C6BD0(t, 0x12);
            if (r)
            {
                return r;
            }
            dword_800C8B30++;
        }
        if (sub_800C6EC8(t, 2) == 0 && m < 40)
        {
            r = sub_800C6A8C(t);
            if (r)
            {
                return r;
            }
            dword_800C8B30++;
        }
    }
    return sub_800C6A68(t);
}

extern int sub_800C6BD0();
int sub_800C4FA8(BatTask* t)
{
    int r = sub_800C6BD0(t, 4);
    if (r == 0)
    {
        r = sub_800C6A68(t);
    }
    return r;
}

int sub_800C4FE0(BatTask* t)
{
    int r;
    if (sub_800C6EE4(t))
    {
        r = sub_800C6BD0(t, 7);
        if (r)
        {
            return r;
        }
    }
    r = sub_800C6A8C(t);
    if (r)
    {
        return r;
    }
    return sub_800C6A68(t);
}

int sub_800C5034(BatTask* t)
{
    int r;
    if (sub_800C6EC8(t, 0x3F8) == 0)
    {
        r = sub_800C6A8C(t);
        if (r)
        {
            return r;
        }
    }
    return sub_800C6A68(t);
}

int sub_800C507C(BatTask* t)
{
    int r = sub_800C6A8C(t);
    if (r == 0)
    {
        r = sub_800C6A68(t);
    }
    return r;
}

int sub_800C50B0(BatTask* t)
{
    int r;
    Minion* s = (Minion*)t->f10;
    short x;
    short y;
    if (sub_800BC868() == 3 || sub_800BC868() == -1)
    {
        r = sub_800C6BD0(t, 0x17);
        if (r)
        {
            return r;
        }
    }
    if (rand() % 10 < 6)
    {
        r = sub_800C6BD0(t, 6);
        if (r)
        {
            return r;
        }
    }
    x = sub_800334D8(s);
    y = sub_800334CC(s);
    if (x <= (short)(y / 3) && (rand() & 1))
    {
        r = sub_800C6C58(t);
        if (r)
        {
            return r;
        }
    }
    return sub_800C6C44(t);
}

extern int rand();
int sub_800C51D8(BatTask* t)
{
    int r;
    if (rand(t) & 1)
    {
        r = sub_800C6A8C(t);
    }
    else
    {
        r = sub_800C6A68(t);
    }
    return r;
}

int sub_800C5220(BatTask* t)
{
    unsigned char* s = t->f14;
    int r = sub_800C6DF8(t, 0xD);
    if (r)
    {
        return r;
    }
    if ((short)sub_800334D8(s) != 1)
    {
        r = sub_800C6A8C(t);
        if (r)
        {
            return r;
        }
    }
    return sub_800C6A68(t);
}
int sub_800C5290(BatTask* t)
{
    int r;
    if (rand() % 10 < 6)
    {
        r = sub_800C6BD0(t, 2);
        if (r)
        {
            return r;
        }
    }
    return sub_800C6A68(t);
}

int sub_800C5304(BatTask* t)
{
    int r;
    if (sub_800C6EC8(t, 1) == 0 && rand() % 10 < 7)
    {
        r = sub_800C6BD0(t, 0x11);
        if (r)
        {
            return r;
        }
    }
    if (rand() & 1)
    {
        r = sub_800C6A8C(t);
        if (r)
        {
            return r;
        }
    }
    return sub_800C6A68(t);
}

int sub_800C53B0(BatTask* t)
{
    int r;
    if (rand() % 10 < 6)
    {
        r = sub_800C6BD0(t, 5);
        if (r)
        {
            return r;
        }
    }
    return sub_800C6A68(t);
}

int sub_800C5424(BatTask* t)
{
    int r;
    Minion* s = (Minion*)t->f10;
    short x = sub_800334D8(s);
    short y = sub_800334CC(s);
    if (x <= y / 2)
    {
        r = sub_800C6A8C(t);
        if (r)
        {
            return r;
        }
    }
    return sub_800C6A68(t);
}

int sub_800C54A4(BatTask* t)
{
    int r;
    if (sub_800BC868() == 1 || sub_800BC868() == -1)
    {
        r = sub_800C6BD0(t, 0x15);
        if (r)
        {
            return r;
        }
    }
    r = sub_800C6A8C(t);
    if (r)
    {
        return r;
    }
    return sub_800C6A68(t);
}
int sub_800C5510(BatTask* t)
{
    int r;
    if (sub_800C6BD0(t, 8) == 0)
    {
        return sub_800C6C58(t);
    }
    r = rand() & 1;
    if (r)
    {
        return r;
    }
    if (sub_800334F0((Minion*)t->f14) != 0)
    {
        r = sub_800C6A8C(t);
        if (r)
        {
            return r;
        }
    }
    r = sub_800C6A68(t);
    if (r)
    {
        return r;
    }
    return sub_800C6C58(t);
}

int sub_800C5594(BatTask* t)
{
    int r;
    if (rand() % 10 < 7)
    {
        r = sub_800C6A8C(t);
        if (r)
        {
            return r;
        }
    }
    return sub_800C6A68(t);
}

int sub_800C5608(BatTask* t)
{
    int r;
    if (sub_800BC868() == 0 || sub_800BC868() == -1)
    {
        r = sub_800C6BD0(t, 0x16);
        if (r)
        {
            return r;
        }
    }
    r = sub_800C6A8C(t);
    if (r)
    {
        return r;
    }
    return sub_800C6A68(t);
}
int sub_800C5670(BatTask* t)
{
    int r;
    if (sub_800C6EC8(t, 0x3F8) == 0)
    {
        r = sub_800C6BD0(t, 0x13);
        if (r)
        {
            return r;
        }
    }
    return sub_800C6C44(t);
}

int sub_800C56B8(BatTask* t)
{
    int r = sub_800C6BD0(t, 0xB);
    if (r)
    {
        return r;
    }
    r = sub_800C6A8C(t);
    if (r)
    {
        return r;
    }
    return sub_800C6A68(t);
}

int sub_800C5700(BatTask* t)
{
    int r;
    if (sub_800BC868() == 2 || sub_800BC868() == -1)
    {
        r = sub_800C6BD0(t, 0x18);
        if (r)
        {
            return r;
        }
    }
    r = sub_800C6A8C(t);
    if (r)
    {
        return r;
    }
    return sub_800C6A68(t);
}
int sub_800C576C(BatTask* t)
{
    int r;
    if (sub_800BC868() == 3 || sub_800BC868() == -1)
    {
        r = sub_800C6BD0(t, 0x17);
        if (r)
        {
            return r;
        }
    }
    r = sub_800C6A8C(t);
    if (r)
    {
        return r;
    }
    return sub_800C6A68(t);
}
int sub_800C57D8(BatTask* t)
{
    int r = sub_800C6A8C(t);
    if (r == 0)
    {
        r = sub_800C6A68(t);
    }
    return r;
}

int sub_800C580C(BatTask* t)
{
    int r = sub_800C6A8C(t);
    if (r == 0)
    {
        r = sub_800C6A68(t);
    }
    return r;
}

int sub_800C5840(BatTask* t)
{
    int r = sub_800C6A8C(t);
    if (r == 0)
    {
        r = sub_800C6A68(t);
    }
    return r;
}

int sub_800C5874(BatTask* t)
{
    int r = sub_800C6BD0(t, 0x14);
    if (r == 0)
    {
        r = sub_800C6A68(t);
    }
    return r;
}

void sub_800C58AC(BatTask* t)
{
    *t->f8 = 0x12;
}

void sub_800C58BC(BatTask* t)
{
    unsigned char k = dword_800C8B30 % 6;
    switch (k)
    {
    case 0:
        t->f8[0] = 6;
        t->f8[1] = 2;
        t->f8[3] = t->f18;
        break;
    case 2:
        t->f8[0] = 6;
        t->f8[1] = 3;
        t->f8[3] = t->f18;
        break;
    case 4:
        t->f8[0] = 6;
        t->f8[1] = 1;
        t->f8[3] = t->f18;
        break;
    case 1:
    case 3:
    case 5:
        t->f8[0] = 0;
        t->f8[3] = t->f18;
        break;
    }
    dword_800C8B30++;
}
INCLUDE_OVERLAY_ASM(battle, dword_800B68AC);

void sub_800C59A0(BatTask* t)
{
    unsigned char k = dword_800C8B30 % 3;
    switch (k)
    {
    case 0:
        t->f8[0] = 6;
        t->f8[1] = 3;
        t->f8[3] = t->f18;
        break;
    case 1:
        t->f8[0] = 6;
        t->f8[1] = 2;
        t->f8[3] = t->f18;
        break;
    case 2:
        t->f8[0] = 6;
        t->f8[1] = 1;
        t->f8[3] = t->f18;
        break;
    }
    dword_800C8B30++;
}

void sub_800C5A7C(BatTask* t)
{
    if (t->fC == 0)
    {
        if (dword_800C8B34 == 0)
        {
            t->f8[2] = 0x10;
            t->f8[0] = 0x15;
            dword_800C8B34 = 1;
            t->f8[1] = 1;
            t->f8[3] = 2;
        }
        else
        {
            t->f8[0] = 0;
            t->f8[3] = t->f18;
        }
    }
    else if (t->fC == 1)
    {
        unsigned char k = dword_800C8B30 % 3;
        switch (k)
        {
        case 0:
            t->f8[0] = 0;
            t->f8[3] = t->f18;
            break;
        case 1:
            t->f8[0] = 6;
            t->f8[1] = 0;
            t->f8[3] = t->f18;
            break;
        case 2:
            t->f8[0] = 1;
            t->f8[1] = 2;
            t->f8[3] = t->f18;
            break;
        }
        dword_800C8B30++;
    }
}

void sub_800C5BC0(BatTask* t)
{
    if (t->fC == 0)
    {
        if (dword_800C8B34 == 0)
        {
            t->f8[2] = 0x10;
            t->f8[0] = 0x15;
            dword_800C8B34 = 1;
            t->f8[1] = 1;
            t->f8[3] = 2;
        }
        else
        {
            t->f8[0] = 0;
            t->f8[3] = t->f18;
        }
    }
    else if (t->fC == 1)
    {
        unsigned char k = dword_800C8B30 % 3;
        switch (k)
        {
        case 0:
            t->f8[0] = 0;
            t->f8[3] = t->f18;
            break;
        case 1:
            t->f8[0] = 6;
            t->f8[1] = 0;
            t->f8[3] = t->f18;
            break;
        case 2:
            t->f8[0] = 1;
            t->f8[1] = 2;
            t->f8[3] = t->f18;
            break;
        }
        dword_800C8B30++;
    }
}

void sub_800C5D04(BatTask* t)
{
    if (t->fC == 0)
    {
        if (dword_800C8B34 == 0)
        {
            t->f8[2] = 0x10;
            t->f8[0] = 0x15;
            dword_800C8B34 = 1;
            t->f8[1] = 1;
            t->f8[3] = 2;
        }
        else
        {
            t->f8[0] = 0;
            t->f8[3] = t->f18;
        }
    }
    else
    {
        unsigned char* p = &dword_800C8B30;
        if (p[1])
        {
            t->f8[0] = 6;
            t->f8[1] = 2;
            t->f8[3] = t->f18;
            p[1] = 0;
        }
        else
        {
            switch (rand() % 3)
            {
            case 0:
                t->f8[0] = 1;
                t->f8[1] = 0x1B;
                t->f8[3] = t->f18;
                sub_80018430(2);
                break;
            case 1:
                t->f8[0] = 6;
                t->f8[1] = 1;
                t->f8[3] = t->f18;
                break;
            default:
                t->f8[0] = 6;
                t->f8[1] = 0;
                t->f8[3] = t->f8[2];
                (&dword_800C8B30)[1] = 1;
                break;
            }
        }
    }
    dword_800C8B30++;
}

void sub_800C5EB8(BatTask* t)
{
    if (t->fC == 0)
    {
        if (dword_800C8B34 == 0)
        {
            t->f8[2] = 0x10;
            t->f8[0] = 0x15;
            dword_800C8B34 = 1;
            t->f8[1] = 1;
            t->f8[3] = 2;
        }
        else
        {
            t->f8[0] = 0;
            t->f8[3] = t->f18;
        }
    }
    else
    {
        switch (rand() % 3)
        {
        case 0:
            if (sub_800334F0((Minion*)t->f14))
            {
                t->f8[0] = 6;
                t->f8[1] = 1;
                t->f8[3] = t->f18;
                break;
            }
        case 1:
            t->f8[0] = 1;
            t->f8[1] = 0x19;
            t->f8[3] = t->f18;
            sub_80018430(0);
            break;
        case 2:
            t->f8[0] = 6;
            t->f8[1] = 3;
            t->f8[3] = t->f18;
            break;
        }
    }
    dword_800C8B30++;
}

#if 0 // Not matched: one spot: in the 'f8[3] = f8[2]; dword_800C8B30 = 0' arm the byte store is scheduled above the word store (original keeps it in the j delay slot), which also swaps v0/v1
void sub_800C6038(BatTask* t)
{
    if (t->fC == 0)
    {
        if (dword_800C8B34 == 0)
        {
            t->f8[2] = 0x10;
            t->f8[0] = 0x15;
            dword_800C8B34 = 1;
            t->f8[1] = 1;
            t->f8[3] = 2;
        }
        else
        {
            t->f8[0] = 0;
            t->f8[3] = t->f18;
        }
    }
    else if (dword_800C8B30 != 0 && sub_800C6EC8(t, 2))
    {
        t->f8[0] = 6;
        t->f8[1] = 0;
        t->f8[3] = t->f8[2];
        dword_800C8B30 = 0;
    }
    else
    {
        dword_800C8B30++;
        switch (rand() % 3)
        {
        case 0:
            t->f8[0] = 1;
            t->f8[1] = 0x1C;
            t->f8[3] = t->f18;
            sub_80018430(1);
            break;
        case 1:
            t->f8[0] = 6;
            t->f8[1] = 1;
            t->f8[3] = t->f18;
            break;
        case 2:
            t->f8[0] = 6;
            t->f8[1] = 3;
            t->f8[3] = t->f18;
            break;
        }
    }
}
#endif
INCLUDE_OVERLAY_ASM(battle, sub_800C6038);

extern void sub_800C66B4(unsigned char* buf, unsigned int b);
extern void sub_800C6B24(BatTask* t, int a, int b);
void sub_800C61FC(BatTask* t)
{
    unsigned short f;
    if (t->fC == 0)
    {
        if (dword_800C8B34 == 0)
        {
            t->f8[2] = 0x10;
            t->f8[0] = 0x15;
            dword_800C8B34 = 1;
            t->f8[1] = 1;
            t->f8[3] = 2;
        }
        else
        {
            *(short*)(t->f10 + 0x42) = 0;
            sub_800C66B4((unsigned char*)t->f10, 0xC);
            t->f8[0] = 6;
            t->f8[1] = 1;
            t->f8[3] = t->f18;
        }
    }
    else if ((sub_800BC868() == 0 && !(*(unsigned short*)(t->f10 + 0x42) & 1)) || (dword_800C8B30 >= 3 && sub_800BC868() == 0))
    {
        sub_800C6AFC(t, 6, 2);
        ((unsigned char*)t->f4)[9] = 0x25;
        *(short*)(t->f10 + 0x42) = 8;
        sub_80018430(3);
        sub_800C66B4((unsigned char*)t->f10, 2);
        dword_800C8B30 = 0;
    }
    else if ((sub_800BC868() == 1 && !(*(unsigned short*)(t->f10 + 0x42) & 2)) || (dword_800C8B30 >= 3 && sub_800BC868() == 1))
    {
        sub_800C6AFC(t, 6, 2);
        ((unsigned char*)t->f4)[9] = 0x22;
        *(short*)(t->f10 + 0x42) = 1;
        sub_80018430(0);
        sub_800C66B4((unsigned char*)t->f10, 3);
        dword_800C8B30 = 0;
    }
    else if ((sub_800BC868() == 2 && !(*(unsigned short*)(t->f10 + 0x42) & 4)) || (dword_800C8B30 >= 3 && sub_800BC868() == 2))
    {
        sub_800C6AFC(t, 6, 2);
        ((unsigned char*)t->f4)[9] = 0x23;
        *(short*)(t->f10 + 0x42) = 2;
        sub_80018430(1);
        sub_800C66B4((unsigned char*)t->f10, 0);
        dword_800C8B30 = 0;
    }
    else if ((sub_800BC868() == 3 && !(*(unsigned short*)(t->f10 + 0x42) & 8)) || (dword_800C8B30 >= 4 && sub_800BC868() == 3) || sub_800BC868() == -1)
    {
        sub_800C6AFC(t, 6, 2);
        ((unsigned char*)t->f4)[9] = 0x24;
        *(short*)(t->f10 + 0x42) = 4;
        sub_80018430(2);
        sub_800C66B4((unsigned char*)t->f10, 1);
        dword_800C8B30 = 0;
    }
    else
    {
        f = *(unsigned short*)(t->f10 + 0x42);
        if (f & 8)
        {
            if (dword_800C8B30 == 1)
            {
                sub_800C6B24(t, 1, 0x1D);
            }
            else
            {
                sub_800C6AFC(t, 6, 0);
            }
        }
        else if (f & 1)
        {
            if (rand() & 1)
            {
                sub_800C6AFC(t, 6, 1);
                ((unsigned char*)t->f4)[5] = 4;
            }
            else
            {
                sub_800C6AFC(t, 1, 0x19);
                sub_80018430(0);
            }
        }
        else if (f & 2)
        {
            if (rand() % 3 != 0)
            {
                sub_800C6AFC(t, 1, 0x1C);
                sub_80018430(1);
            }
            else
            {
                sub_800C6AFC(t, 6, 1);
                ((unsigned char*)t->f4)[5] = 5;
            }
        }
        else if (f & 4)
        {
            if (rand() % 3 != 0)
            {
                sub_800C6AFC(t, 6, 1);
                ((unsigned char*)t->f4)[5] = 2;
            }
            else
            {
                sub_800C6AFC(t, 1, 0x1B);
                sub_80018430(2);
            }
        }
    }
    dword_800C8B30 += ((rand() & 3) >> 1) + 1;
}

void sub_800C66B4(unsigned char* buf, unsigned int b)
{
    int i;
    unsigned int c = 0xC;
    unsigned char* p;
    if (b == c)
    {
        c = 0x30;
    }
    for (i = 3, p = buf + 3; i >= 0; i--, p--)
    {
        p[0x20] = c;
    }
    if (b < 0xC)
    {
        (buf + b)[0x20] = 0x18;
    }
}
void sub_800C66F4(BatTask* t)
{
    if (t->fC == 0)
    {
        if (dword_800C8B34 == 0)
        {
            t->f8[2] = 0x10;
            t->f8[0] = 0x15;
            dword_800C8B34 = 1;
            t->f8[1] = 1;
            t->f8[3] = 2;
            return;
        }
    }
    else if (t->fC == 1)
    {
        if ((rand() & 1) || (*(unsigned short*)(t->f14 + 0x42) & 2))
        {
            goto act;
        }
        else
        {
            short x = sub_800334D8((Minion*)t->f10);
            short y = sub_800334CC((Minion*)t->f10);
            if (x < (short)(y / 3))
            {
            act:
                if (sub_800C6A8C(t))
                {
                    return;
                }
            }
        }
    }
    else
    {
        return;
    }
    t->f8[0] = 0;
    t->f8[3] = t->f18;
}

void sub_800C6824(BatTask* t)
{
    if (t->fC == 0)
    {
        if (dword_800C8B34 == 0)
        {
            t->f8[2] = 0x10;
            t->f8[0] = 0x15;
            dword_800C8B34 = 1;
            t->f8[1] = 1;
            t->f8[3] = 2;
            return;
        }
    }
    else if (t->fC == 1)
    {
        short x = sub_800334D8((Minion*)t->f10);
        short y = sub_800334CC((Minion*)t->f10);
        if (x < y / 4)
        {
            if (sub_800C6A8C(t))
            {
                return;
            }
        }
        if (sub_800C6BD0(t, 9))
        {
            return;
        }
    }
    else
    {
        return;
    }
    t->f8[0] = 0;
    t->f8[3] = t->f18;
}

void sub_800C6928(BatTask* t)
{
    if (t->fC == 0)
    {
        if (dword_800C8B34 == 0)
        {
            t->f8[2] = 0x10;
            t->f8[0] = 0x15;
            dword_800C8B34 = 1;
            t->f8[1] = 1;
            t->f8[3] = 2;
            return;
        }
    }
    else if (t->fC == 1)
    {
        short x = sub_800334D8((Minion*)t->f10);
        short y = sub_800334CC((Minion*)t->f10);
        if (x < y / 2)
        {
            if (sub_800C6A8C(t))
            {
                return;
            }
        }
        if (rand() & 1)
        {
            if (sub_800C6BD0(t, 6))
            {
                return;
            }
        }
    }
    else
    {
        return;
    }
    t->f8[0] = 0;
    t->f8[3] = t->f18;
}

void sub_800C6A40(BatTask* t)
{
    *t->f8 = 6;
    t->f8[1] = 0;
    t->f8[3] = t->f18;
}

int sub_800C6A68(BatTask* t)
{
    *t->f8 = 0;
    t->f8[3] = t->f18;
    return 1;
}

extern int sub_800C6D6C();
int sub_800C6A8C(BatTask* t)
{
    int r = sub_800C6D6C(t->f4, t->f10);
    if (r != 5)
    {
        t->f8[0] = 6;
        t->f8[1] = r;
        t->f8[3] = t->f18;
        return 1;
    }
    return 0;
}

void sub_800C6AFC(BatTask* t, int a, int b)
{
    t->f8[0] = a;
    t->f8[1] = b;
    t->f8[3] = t->f18;
}

void sub_800C6B24(BatTask* t, int a, int b)
{
    int* p;
    t->f8[0] = a;
    t->f8[1] = b;
    p = t->f8;
    p[3] = p[2];
}

int sub_800C6B50(BatTask* t, int a, int b)
{
    if (sub_800C6CFC(a, t->f0, t->f10) != 0)
    {
        t->f8[0] = 1;
        t->f8[1] = a;
        t->f8[3] = 1 << (b + 4);
        return 1;
    }
    return 0;
}

extern int sub_800C6CFC();
int sub_800C6BD0(BatTask* t, int a)
{
    if (sub_800C6CFC(a, t->f0, t->f10) != 0)
    {
        t->f8[0] = 1;
        t->f8[1] = a;
        t->f8[3] = t->f18;
        return 1;
    }
    return 0;
}

int sub_800C6C44(BatTask* t)
{
    *t->f8 = 0x12;
    return 1;
}

int sub_800C6C58(BatTask* t)
{
    *t->f8 = 7;
    t->f8[3] = t->f18;
    return 1;
}

void sub_800C6C7C(int* out)
{
    int bits = sub_800A248C();
    int i;
    for (i = 0; i < 3; i++)
    {
        int m = 1 << (i + 4);
        if (bits & m)
        {
            out[i] = sub_800A2B60(i);
        }
        else
        {
            out[i] = 0;
        }
    }
}
int sub_800C6CFC(unsigned int a, unsigned int* b, short* c)
{
    if (TestMagicBit_8001AE2C(b, a) != 0)
    {
        if (magicData_8007C438[a].field_4 <= c[6])
        {
            return 1;
        }
    }
    return 0;
}

int sub_800C6D6C(unsigned char* a, short* b)
{
    int i;
    for (i = 0; i < 5; i++)
    {
        if (a[i * 4] & 1)
        {
            short h = b[6];
            if (!(h < sub_80031A04(a, i)))
            {
                return i;
            }
        }
    }
    return i;
}

int sub_800C6DF8(BatTask* t, int a)
{
    Minion* out[3];
    int i;
    sub_800C6C7C(out);
    for (i = 0; i < 3; i++)
    {
        if (out[i])
        {
            short x = sub_800334D8(out[i]);
            short y = sub_800334CC(out[i]);
            if (x <= y / 4)
            {
                if (sub_800C6B50(t, a, i))
                {
                    return 1;
                }
            }
        }
    }
    return 0;
}

int sub_800C6EC8(BatTask* t, int m)
{
    return (*(int*)t->f14 & m) != 0;
}

int sub_800C6EE4(BatTask* t)
{
    return t->f14[0x2d] > t->f14[0x2f];
}

extern EventNode* dword_8008D468;
extern unsigned char dword_800C9E4B;
extern unsigned char dword_800C9E70;
extern void sub_800C71A0();
extern void BattleMenuTask_800C8A08();
int StartBattleMenu_800C6EFC()
{
    int i;
    int m;
    int n = 0;
    EventEntry* e = AllocEventEntry_80043AF8(dword_8008D468);
    if (e)
    {
        e->cb_8 = (EventEntryFn)BattleMenuTask_800C8A08;
        e->flags = (e->flags | 1) & 0xFFFF7FFF;
        if (dword_800C9C7C == 0)
        {
            dword_800C9E49 = 0;
        }
        else
        {
            dword_800C9E49 = 1;
        }
        dword_800C9E58[0] = 0;
        dword_800C9E58[1] = 0;
        dword_800C9E58[3] = 0;
        dword_800C9E58[2] = 1 << dword_800C9C7C;
        dword_800C9E78 = sub_800C0A9C();
        dword_800C9E4B = GetCapturedMinionsFromBitfield_8003BA58(dword_800C9E78);
        dword_800C9E4C = sub_800A248C();
        dword_800C9E4A = GetCapturedMinionsFromBitfield_8003BA58(dword_800C9E4C);
        for (i = 0; i < 3; i++)
        {
            m = 1 << (i + 4);
            if (dword_800C9E4C & m)
            {
                dword_800C9E80[n] = i + 4;
                dword_800C9E72[n] = m;
                n++;
            }
        }
        dword_800C9E50 = 0;
        dword_800C9E40 = 0;
        dword_800C9E48 = 0;
        dword_800C9E68 = 4;
        dword_800C9E70 = 0;
        sub_800C7088();
        sub_800C71A0();
        sub_800C71C8();
        dword_800C9E38 = -1;
    }
    return (int)e;
}

extern int sub_800AD308(int a);
extern int CountMagicBits_8001AE54(char* h);
void sub_800C7088()
{
    if (dword_800C9E49 == 0)
    {
        if (sub_800AD308(0) + 1 >= 5)
        {
            dword_800C9308->count_4 = sub_800AD308(0) + 1;
        }
        dword_800C9308->cursor_8 = 0;
        dword_800C92D8->count_4 = 6;
        dword_800C92D8->cursor_8 = 0;
    }
    else
    {
        if (CountMagicBits_8001AE54(sub_80010824(3, dword_800C9C7C - 1)) >= 5)
        {
            dword_800C92F0->count_4 = CountMagicBits_8001AE54(sub_80010824(3, dword_800C9C7C - 1));
        }
        dword_800C92F0->cursor_8 = 0;
        dword_800C92E4->cursor_8 = 0;
        dword_800C92D8->count_4 = 5;
        dword_800C92D8->cursor_8 = 0;
    }
    if ((unsigned char)dword_800C9D56 > dword_800C9E4A - 1)
    {
        dword_800C9D56 = 0;
    }
    dword_800C9314->f0 = dword_800C9E4A;
    dword_800C9314->count_4 = dword_800C9E4A;
    dword_800C9314->cursor_8 = (unsigned char)dword_800C9D56;
}

extern int dword_800C9628[];
extern int dword_800C9640;
void sub_800C71A0()
{
    dword_800C9640 = dword_800C9628[dword_800C9E49];
}

extern char dword_800C9378[];
extern char dword_800C9384[];
extern char dword_800C9388[];
extern char dword_800C938C[];
extern char dword_800C93A4[];
extern char dword_800C93D4[];
extern char* dword_800C93B8[];
extern unsigned short dword_800C946C;
extern unsigned short dword_800C94A4;
extern unsigned short dword_800C9514;
extern char* dword_800C9E6C;
void sub_800C71C8()
{
    if (dword_800C9E49 == 0)
    {
        if (sub_800C0A9C() == 0)
        {
            dword_800C93B8[0] = dword_800C9378;
            dword_800C946C |= 2;
        }
        if (sub_800C7334() == 0)
        {
            dword_800C93B8[2] = dword_800C9384;
            dword_800C94A4 |= 2;
        }
        else if (sub_800AD8E4() == 0)
        {
            dword_800C93B8[2] = dword_800C9388;
            dword_800C94A4 |= 2;
        }
        if (sub_800C72B8() == 0)
        {
            dword_800C93B8[6] = dword_800C938C;
            dword_800C9514 |= 2;
        }
        dword_800C9E6C = dword_800C93A4;
    }
    else
    {
        dword_800C9E6C = dword_800C93D4;
    }
}

int sub_800C72B8()
{
    int i;
    int m;
    for (i = 0; i < 3; i++)
    {
        m = dword_800C9E4C & (1 << (i + 4));
        if (m != 0)
        {
            if (sub_800A28FC(i) == 0)
            {
                return 0;
            }
        }
    }
    return 1;
}
int sub_800C7334()
{
    int i;
    int m;
    for (i = 0; i < 3; i++)
    {
        m = dword_800C9E4C & (1 << (i + 4));
        if (m != 0)
        {
            if (sub_800BF980(sub_800A2BE4(i)) == 1)
            {
                return 0;
            }
        }
    }
    return 1;
}
extern char* dword_800C9338[];
char* sub_800C73B8(unsigned char a)
{
    if (a == 4)
    {
        if (dword_800C9E68 & 1)
        {
            return dword_800C932C;
        }
        if (dword_800C9E68 & 4)
        {
            return dword_800C9314;
        }
        return dword_800C9320;
    }
    return dword_800C9338[a];
}
void sub_800C7424(unsigned char a)
{
    sub_800BFC10();
    if (a == 4)
    {
        if (dword_800C9E68 & 1)
        {
            if (dword_800C9E68 & 4)
            {
                dword_800C9DFC = 1;
                dword_800C9174[0] = GetTime30Hz_8002C64C();
                dword_800C9174[1] = GetTime30Hz_8002C64C();
                dword_800C9174[2] = GetTime30Hz_8002C64C();
            }
            if (dword_800C9E68 & 2)
            {
                dword_800C9DFD = 1;
                dword_800C9170 = GetTime30Hz_8002C64C();
            }
        }
        else if (dword_800C9E68 & 4)
        {
            short i;
            dword_800C9DFC = 1;
            i = GetMenuCursorIndex_8003DA54(dword_800C9314);
            dword_800C9174[dword_800C9E80[i] - 4] = GetTime30Hz_8002C64C();
        }
        else
        {
            dword_800C9DFD = 1;
            dword_800C9170 = GetTime30Hz_8002C64C();
        }
    }
}

INCLUDE_OVERLAY_ASM(battle, sub_800C7530);

extern unsigned char dword_800C9648[];
unsigned char sub_800C78D0()
{
    return dword_800C9648[dword_800C9E49 + (short)GetMenuCursorIndex_8003DA54(dword_800C92D8) * 2];
}

#if 0 // Not matched: b and r swap registers (v1/a0); tried declaration order, int b, re-reading the global, early returns
int sub_800C791C()
{
    unsigned char b = dword_800C9E68;
    int r = 0;
    if (b & 1)
    {
        if (b & 4)
        {
            r = dword_800C9E4C;
        }
        if (b & 2)
        {
            r |= 1;
            r |= dword_800C9E78;
        }
    }
    else if (b & 4)
    {
        short i = GetMenuCursorIndex_8003DA54(dword_800C9314);
        r = dword_800C9E72[i];
    }
    else
    {
        r = 1 << *(int*)&dword_800C9E54;
    }
    return r;
}
#endif
INCLUDE_OVERLAY_ASM(battle, sub_800C791C);
int sub_800C79B8()
{
    return sub_800AD288((short)GetMenuCursorIndex_8003DA54(dword_800C9308), 0);
}

extern int GetMenuCursorIndex_8003DA54(void*);
void sub_800C79EC()
{
    sub_80031BDC((short)GetMenuCursorIndex_8003DA54(dword_800C92E4));
}

extern unsigned char dword_800C9C7C;
int sub_800C7A1C()
{
    char* h = sub_80010824(3, dword_800C9C7C - 1);
    return FindNthMagicBit_8001AEC0(h, (short)GetMenuCursorIndex_8003DA54(dword_800C92F0));
}

INCLUDE_OVERLAY_ASM(battle, sub_800C7A6C);

struct BatState
{
    int f0;
    int f4;
    int f8;
    int fC;
};
extern struct BatState dword_800C9630;
extern short dword_800C92E0;
void sub_800C7CE8(unsigned char a)
{
    unsigned int n;
    if (a == 0)
    {
        dword_800C9630.f0 = 2;
    }
    else
    {
        dword_800C9630.f0 = 4;
    }
    dword_800C9630.f4 = GetTime30Hz_8002C64C();
    n = dword_800C9630.f8;
    if (n < 8)
    {
        dword_800C9630.f8 = n + 1;
    }
    dword_800C9630.fC = dword_800C92E0;
}
extern unsigned char dword_800C9E54;
extern unsigned char dword_800C9C99;
void sub_800C7D54(unsigned char a)
{
    if (a != 4)
    {
        dword_800C9C99 = dword_800C9C7C;
    }
    else if (dword_800C9E68 & 5)
    {
        dword_800C9C99 = dword_800C9C7C;
    }
    else
    {
        dword_800C9C99 = dword_800C9E54;
    }
}
typedef struct BatWin_a
{
    short x;
    short y;
    short w;
    short h;
    short c;
    short d;
    int p;
} BatWin_a;

typedef struct BatMenuItem_a
{
    int* text;
    int f4;
} BatMenuItem_a;

extern int dword_800C96C8[][4];
extern int dword_800C9978[][4];
extern char dword_800C9B58[];
extern unsigned short dword_800C9E5C;
extern unsigned short dword_800C968C[][2];
extern int dword_800C9674[];
extern int IsCircleHeldP1_8003D480(void);
extern int GetMenuCursorIndex_8003DA54();
extern void sub_8002C670(void* a0, int a1, void* a2, int a3, int a4);
extern int sub_8002D250(void* a0, int a1, int a2, int a3);
extern void DrawMenuWindows_8002A5A4(void* a0);
extern void sub_8002C728(void* a0);
extern void sub_8002CE28(void* a0, int a1);
extern int sub_80031A04(int a0, int a1);
extern void sub_8002CAC8(void* a0, void* a1);
extern int FindNthMagicBit_8001AEC0();
extern void DrawButtonHelpBar_8002B004(int a0, int a1, int a2);
extern void sub_800C8828(int a);
extern char* dword_800C9E44;
extern short dword_800C9180;
extern short dword_800C9182;
void BattleMenuDraw_800C7DA8()
{
    int flags = 0;
    int k = 0;
    int c;
    short sel[2];
    dword_800C9180 = 0;
    dword_800C9182 = 0;
    if (IsCircleHeldP1_8003D480() == 1 && dword_800C9E48 != 1)
    {
        if (dword_800C9E50 == 0)
        {
            k = 1;
            sub_800C8828(*((BatMenuItem_a*)dword_800C9E6C)[(short)GetMenuCursorIndex_8003DA54(dword_800C92D8)].text);
        }
        else if (dword_800C9E50 == 1)
        {
            if (sub_800C79B8() != 0xFF)
            {
                DrawLargeTextBox_8002AF10((int)dword_800C96C8[sub_800C79B8()], 0, 0xF);
                k = 1;
            }
        }
        else if (dword_800C9E50 == 2)
        {
            Minion* m = GetMinion_80010598(3, dword_800C9C7C - 1);
            sub_8002C670(m, 0, dword_800C9B58, (short)GetMenuCursorIndex_8003DA54(dword_800C92E4), 0xF);
            k = 1;
        }
        else if (dword_800C9E50 == 3)
        {
            if (sub_800C7A1C() < 0x1E)
            {
                DrawLargeTextBox_8002AF10((int)dword_800C9978[sub_800C7A1C()], 0, 0xF);
                k = 1;
            }
        }
    }
    if (k != 0)
    {
        k = 1;
    }
    else
    {
        k = dword_800C9E48;
    }
    sel[0] = dword_800C9E5C;
    sel[1] = dword_800C9C7C;
    if (!(dword_800C968C[dword_800C9E50][k] & 0x10))
    {
        if (dword_800C9E68 & 1)
        {
            c = -1;
        }
        else
        {
            c = (short)GetMenuCursorIndex_8003DA54(dword_800C9E44);
        }
        if (sub_800C78D0() == 4)
        {
            if (dword_800C9E68 & 2)
            {
                *(int*)&dword_800C9E54 = sub_8002D250(sel, 0, c, 0xF);
                flags |= 1;
            }
        }
        else if (sub_800C78D0() == 6)
        {
        }
        else if (sub_800C78D0() == 7)
        {
            if (dword_800C9E68 & 2)
            {
                *(int*)&dword_800C9E54 = sub_8002D250(sel, 1, c, 0xF);
                flags |= 1;
            }
        }
        else if (sub_800C78D0() == 2)
        {
            *(int*)&dword_800C9E54 = sub_8002D250(sel, 2, c, 0xF);
            flags |= 1;
        }
        else if (sub_800C78D0() == 8)
        {
            *(int*)&dword_800C9E54 = sub_8002D250(sel, 3, c, 0xF);
            flags |= 1;
        }
    }
    if (dword_800C968C[dword_800C9E50][k] & 2)
    {
        sub_800BC838(0x8000);
    }
    else
    {
        sub_800BC850(0x8000);
    }
    if (dword_800C968C[dword_800C9E50][k] & 1)
    {
        sub_800BC838(0x10000);
    }
    else
    {
        sub_800BC850(0x10000);
    }
    if (!(dword_800C968C[dword_800C9E50][k] & 4) && !(flags & 1))
    {
        DrawMenuWindows_8002A5A4(&dword_800C9630);
    }
    if (!(dword_800C968C[dword_800C9E50][k] & 0x20) && !(flags & 2))
    {
        BatWin_a w;
        w.w = 2;
        w.h = 0xF;
        w.c = -1;
        w.p = 0;
        w.d = 0;
        w.x = dword_800C9308->cursor_8;
        w.y = dword_800C9308->scroll_A;
        sub_8002C728(&w);
    }
    if (!(dword_800C968C[dword_800C9E50][k] & 0x40) && !(flags & 4))
    {
        BatWin_a w;
        w.w = 2;
        w.h = 0xF;
        w.c = -1;
        w.x = dword_800C92E4->cursor_8;
        w.y = dword_800C92E4->scroll_A;
        w.p = (int)GetMinion_80010598(3, dword_800C9C7C - 1);
        w.d = 0;
        sub_8002CE28(&w, 0);
        dword_800C9182 = -sub_80031A04(w.p + 0xDE, sub_80031BDC((short)GetMenuCursorIndex_8003DA54(dword_800C92E4)));
    }
    if (!(dword_800C968C[dword_800C9E50][k] & 0x80) && !(flags & 8))
    {
        BatWin_a w;
        short sz[2];
        w.w = 2;
        w.h = 0xF;
        w.c = -1;
        w.x = dword_800C92F0->cursor_8;
        w.y = dword_800C92F0->scroll_A;
        w.p = (int)GetMinion_80010598(3, dword_800C9C7C - 1);
        sz[0] = 0x60;
        w.d = 0;
        sz[1] = 0x45;
        sub_8002CAC8(&w, sz);
        dword_800C9182 = -GetMagicMpCost_8001AC58(FindNthMagicBit_8001AEC0(w.p + 0xF4, (short)GetMenuCursorIndex_8003DA54(dword_800C92F0)));
    }
    DrawButtonHelpBar_8002B004(dword_800C9674[dword_800C9E50], 0, 0xF);
}

INCLUDE_OVERLAY_ASM(battle, sub_800C83B0);

extern unsigned char dword_800C9E72[];
void sub_800C8694(unsigned char a)
{
    if (a == 4 && (dword_800C9E68 & 5) == 4)
    {
        dword_800C9E3C = dword_800C9E72[(short)GetMenuCursorIndex_8003DA54(dword_800C9314)];
    }
    else
    {
        dword_800C9E3C = dword_800C9E4C;
    }
}

extern int dword_800C9E3C;
void sub_800C8710()
{
    if (dword_800C9E38 != dword_800C9E3C)
    {
        dword_800C9E38 = dword_800C9E3C;
        sub_80037AE0((unsigned short)dword_800C9E3C);
        sub_800BC468(dword_800C9E3C, 1 << dword_800C9C7C);
    }
}

void sub_800C8768()
{
    if (IsConfirmPressedP1_8003D380(0))
    {
        if (sub_800C7530())
        {
            PlaySfx_80031494(0x7E);
            sub_800C7A6C();
        }
        else
        {
            PlaySfx_80031494(0x7C);
            if (dword_800C9E7C)
            {
                dword_800C9E51 = 0x96;
                dword_800C9E48 = 1;
            }
        }
    }
    else if (IsCancelPressedP1_8003D41C(0))
    {
        if (dword_800C9E50)
        {
            unsigned char c;
            PlaySfx_80031494(0x7D);
            c = dword_800C9E40;
            dword_800C9E40 = 0;
            dword_800C9E50 = c;
        }
    }
}

#if 0 // Not matched: arg setup order only (original computes &s first and &pos last); tried prototypes, separate arrays, &a, statement order
extern void DrawTextLinesWindow_8002AE38(void* a0, void* a1, int a2, void* a3, int a4);
void sub_800C8828(int a)
{
    short rect[4];
    short p[4];
    short pos[2];
    int s[1];
    rect[0] = 0x19;
    rect[1] = 0x8A;
    rect[2] = MeasureTextWidth_8003E4C8() + 4;
    rect[3] = 0x12;
    s[0] = a;
    p[0] = rect[0];
    p[1] = rect[1];
    pos[0] = rect[0] + 2;
    pos[1] = rect[1] + 4;
    DrawTextLinesWindow_8002AE38(s, pos, 0xF, rect, 1);
}
#endif
INCLUDE_OVERLAY_ASM(battle, sub_800C8828);
void sub_800C88AC(int a)
{
    int s[4];
    s[0] = a;
    s[1] = 0;
    s[2] = 0;
    s[3] = 0;
    DrawLargeTextBox_8002AF10((int)s, 0, 0xF);
}

extern unsigned char dword_800C9E51;
extern unsigned char dword_800C9E48;
extern unsigned char dword_800C9E50;
extern int dword_800C9E7C;
void sub_800C88E4()
{
    if (padPressed_8009194C)
    {
        dword_800C9E51 = 0;
    }
    if (dword_800C9E51 == 0)
    {
        dword_800C9E48 = 0;
    }
    else
    {
        dword_800C9E51--;
    }
    if (dword_800C9E7C)
    {
        if (dword_800C9E50 == 0)
        {
            sub_800C8828(dword_800C9E7C);
        }
        else
        {
            sub_800C88AC(dword_800C9E7C);
        }
    }
}

extern unsigned int dword_800C9E64;
void sub_800C8970()
{
    int v;
    dword_800C9C88[0] = dword_800C9E58[0];
    dword_800C9C88[1] = dword_800C9E58[1];
    dword_800C9C88[2] = dword_800C9E58[2];
    v = dword_800C9E58[0];
    if (v == 7 || v == 0x12)
    {
        dword_800C9C88[3] = dword_800C9E4C;
    }
    else if (v == 8)
    {
        dword_800C9C88[3] = 0;
    }
    else
    {
        dword_800C9C88[3] = dword_800C9E58[3];
    }
    dword_800C9C98 = LowestSetBit_80014358(dword_800C9E64);
}

extern char* dword_800C9E44;
extern void (*dword_800C966C[])(EventEntry* t, int a);
extern short dword_800C9180;
extern short dword_800C9182;
extern void UpdateMenuCursor_8003D794();
extern void sub_800C83B0();
void BattleMenuTask_800C8A08(EventEntry* t, int a)
{
    dword_800C9E44 = sub_800C73B8(dword_800C9E50);
    sub_800C7424(dword_800C9E50);
    UpdateMenuCursor_8003D794(dword_800C9E44, 0);
    sub_800C7CE8(dword_800C9E50);
    BattleMenuDraw_800C7DA8();
    dword_800C9E64 = sub_800C791C();
    sub_800C7D54(dword_800C9E50);
    sub_800C83B0();
    sub_800C8694(dword_800C9E50);
    sub_800C8710();
    dword_800C966C[dword_800C9E48](t, a);
    if (dword_800C9E50 == 5)
    {
        dword_800C9D56 = dword_800C9314->cursor_8;
        sub_800BFC10();
        sub_800C8970();
        dword_800C9180 = 0;
        dword_800C9182 = 0;
        t->flags = (t->flags & ~1) | 0x8000;
    }
}

INCLUDE_OVERLAY_ASM(battle, dword_800C8B2C);
