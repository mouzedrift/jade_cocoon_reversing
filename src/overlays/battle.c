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

extern int sub_800B4200(int* p);
extern int sub_800B41D0(int* p);
extern int* sub_800B41A8(int* p);
extern int* dword_800C9C78;
extern void sub_800BB100();
extern void sub_800BB314();
void sub_800BAE74(BatTask_a* t, BatObj_a* u)
{
    BatObj_a* v = u;
    int* q;
    int f;
    sub_800BC850(0x8000);
    sub_800BC850(0x10000);
    if (dword_800ADE78 == 1)
    {
        if ((&dword_800ADE78)[4] >= 0)
        {
            dword_800C9C7C = 10;
            u->fc = sub_800B4200(&dword_800ADE78);
            t->next_8 = sub_800BB100;
            return;
        }
        if (sub_800BC820(0x2000) == 1)
        {
            sub_800BC838(0x100);
            sub_800BB1B0(t, u);
            t->next_8 = sub_800BB1B0;
            return;
        }
        (&dword_800ADE78)[3]++;
        if (sub_800B41D0(&dword_800ADE78) == 1)
        {
            sub_800BC838(0x100);
            sub_800BB1B0(t, u);
            t->next_8 = sub_800BB1B0;
            return;
        }
        q = sub_800B41A8(&dword_800ADE78);
        f = *q;
        dword_800C9C78 = q;
        if (f == 0)
        {
            dword_800C9C7C = dword_800C9C82;
        }
        else
        {
            dword_800C9C7C = *dword_800C9C78;
        }
        if (dword_800C9C7C == 10)
        {
            int* p = &dword_800ADE78;
            p[4] = dword_800C9C78[5];
            v->fc = sub_800B4200(p);
            t->next_8 = sub_800BB100;
            return;
        }
    }
    else
    {
        if (sub_800BAE10())
        {
            sub_800BB1B0(t, u);
            t->next_8 = sub_800BB1B0;
            return;
        }
        if (sub_800BC820(8) == 1)
        {
            sub_800BC850(8);
            dword_800C9C7C = 0;
            dword_800C9C88[0] = 3;
            dword_800C9C88[1] = 0;
            dword_800C9C88[2] = 1;
            dword_800C9C88[3] = 0;
            sub_800BC838(0x8000);
            t->next_8 = sub_800BBE00;
            u->next_8 = (void (*)())(u->f4 = (int)sub_800BAE74);
            return;
        }
        if (sub_800BC820(2) == 1)
        {
            sub_800BC850(2);
            dword_800C9C98 = 4;
            dword_800C9C7C = 4;
            dword_800C9C88[0] = 3;
            dword_800C9C88[1] = 0;
            dword_800C9C88[2] = 0x10;
            dword_800C9C88[3] = 0;
            sub_800BC838(0x10000);
            t->next_8 = sub_800BC05C;
            v->next_8 = (void (*)())(v->f4 = (int)sub_800BAE74);
            return;
        }
        dword_800C9C7C = 7;
    }
    t->next_8 = sub_800BB314;
}

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

extern void sub_800BB74C();
extern void sub_800BB7D4();
extern void sub_800BB860();
#if 0 // Not matched: only u and flags swap saved registers (s5/s6); reducing flags refs flips them; tried decl order, types, split ifs, tail variable
void sub_800BB380(BatTask_a* t, BatObj_a* u)
{
    BatMin_a* m;
    int flags;
    int kind;
    int r;
    unsigned int f;
    sub_800BB74C();
    sub_800BB7D4();
    m = (BatMin_a*)sub_80014390(dword_800C9C7C);
    flags = m->f0;
    kind = sub_800BC7DC(dword_800C9C7C);
    sub_800BF7C4((unsigned char*)m, &dword_800C9C7E, &dword_800C9C80);
    if (dword_800C9C7E != 0)
    {
        if (dword_800C9C80 != 0)
        {
            dword_800C9CBC[dword_800C9C7C] = 3;
        }
        else
        {
            dword_800C9CBC[dword_800C9C7C] = 1;
        }
    }
    else if (dword_800C9C80 != 0)
    {
        dword_800C9CBC[dword_800C9C7C] = 2;
    }
    f = m->f0;
    r = sub_800BFA4C(f, flags);
    dword_800C9C88[0] = r;
    dword_800C9C88[1] = 0;
    dword_800C9C88[3] = 0;
    if (r == 0x13)
    {
        switch ((unsigned int)kind)
        {
        case 0:
            sub_800BC838(4);
            dword_800C9D80 = 0x1C;
            break;
        case 1:
            sub_800BC838(8);
            dword_800C9D80 = 0x6F;
            break;
        case 2:
            sub_800BC838(0x40);
            if (sub_800BF9B4(sub_800A2BE4(dword_800C9C7C - 4)) == 1)
            {
                sub_800BC838(0x100000);
                dword_800C9D80 = 0x1C;
            }
            else
            {
                sub_800BC850(0x100000);
                dword_800C9D80 = 0x6F;
            }
            if (sub_800A2AB4() == 2)
            {
                sub_800BC838(2);
            }
            break;
        }
        sub_800BC838(0x1000);
        t->next_8 = (void (*)())sub_800BC174();
        u->f4 = (int)(u->next_8 = sub_800BAE74);
        return;
    }
    if (m->h8 - dword_800C9C7E <= 0)
    {
        dword_800C9C88[0] = 0xB;
        dword_800C9C7E = m->h8;
        switch ((unsigned int)kind)
        {
        case 0:
            sub_800BC838(4);
            dword_800C9D80 = 0x1C;
            break;
        case 1:
            sub_800BC838(8);
            dword_800C9D80 = 0x6F;
            break;
        case 2:
            sub_800BC838(0x40);
            if (sub_800BF9B4(sub_800A2BE4(dword_800C9C7C - 4)) == 1)
            {
                sub_800BC838(0x100000);
                dword_800C9D80 = 0x1C;
            }
            else
            {
                sub_800BC850(0x100000);
                dword_800C9D80 = 0x6F;
            }
            if (sub_800A2AB4() == 2)
            {
                sub_800BC838(2);
            }
            break;
        }
        sub_800BC838(0x1000);
        t->next_8 = (void (*)())sub_800BC174();
        u->f4 = (int)(u->next_8 = sub_800BAE74);
        return;
    }
    if (((f & 0x10000) && (flags & 0x10000)) || ((f & 2) && (flags & 2)))
    {
        t->next_8 = sub_800BAE74;
        return;
    }
    if (dword_800C9C88[0] == 0x14)
    {
        t->next_8 = sub_800BB860;
        return;
    }
    sub_800BC838(0x1000);
    t->next_8 = (void (*)())sub_800BC174();
    if (f & 0x200)
    {
        u->f4 = (int)(u->next_8 = sub_800BAE74);
    }
    else if (f & 0x10002)
    {
        u->f4 = (int)(u->next_8 = sub_800BAE74);
    }
    else
    {
        u->f4 = (int)(u->next_8 = sub_800BB860);
    }
}
#endif
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

INCLUDE_OVERLAY_ASM(battle, sub_800BC90C);

extern void sub_800BEBB8();
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
        sub_800BEBB8();
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

INCLUDE_OVERLAY_ASM(battle, sub_800BE3C0);

extern void sub_800BF3DC(int a, int b, int c, int d, int e);
extern void sub_800BF3AC();
extern void sub_80037BFC(int a);
extern void StartPadVibration_80036528(int a, int b);
extern unsigned char dword_800C9134[];
void sub_800BE834(int idx, int b)
{
    switch (dword_800C9CBC[idx])
    {
    case 0:
        break;
    case 1:
        sub_800BF3DC(idx, 0, dword_800C9D38[idx], b, 0);
        if (dword_800C9D38[idx] > 0)
        {
            sub_80037BFC(0x1E);
            if (idx == 0)
            {
                StartPadVibration_80036528(0, 0);
            }
            else
            {
                StartPadVibration_80036528(0, 2);
            }
        }
        break;
    case 2:
        sub_800BF3DC(idx, 1, dword_800C9D48[idx], b, 0);
        if (dword_800C9D48[idx] > 0)
        {
            sub_80037BFC(0x1E);
            if (idx == 0)
            {
                StartPadVibration_80036528(0, 0);
            }
            else
            {
                StartPadVibration_80036528(0, 2);
            }
        }
        break;
    case 3:
        sub_800BF3DC(idx, 0, dword_800C9D38[idx], b, 0);
        sub_800BF3DC(idx, 1, dword_800C9D48[idx], b, 0xC);
        if (dword_800C9D38[idx] > 0 || dword_800C9D48[idx] > 0)
        {
            sub_80037BFC(0x1E);
            if (idx == 0)
            {
                StartPadVibration_80036528(0, 0);
            }
            else
            {
                StartPadVibration_80036528(0, 2);
            }
        }
        break;
    case 4:
        sub_800BF3DC(idx, 2, 0, b, 0);
        sub_800BF3DC(idx, 0, dword_800C9D38[idx], b, 0xC);
        sub_800BF3AC();
        sub_80037BFC(0x1E);
        if (idx == 0)
        {
            StartPadVibration_80036528(0, 1);
        }
        else
        {
            StartPadVibration_80036528(0, 2);
        }
        break;
    case 5:
        StartPadVibration_80036528(0, 0x26);
        break;
    case 6:
        break;
    case 7:
        StartPadVibration_80036528(0, dword_800C9134[((BatSlot_a*)dword_800C9CC8)[idx].b]);
        break;
    }
}
INCLUDE_OVERLAY_ASM(battle, dword_800B6794);

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

INCLUDE_OVERLAY_ASM(battle, sub_800BEBB8);

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

INCLUDE_OVERLAY_ASM(battle, dword_800B6848);

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

extern unsigned int dword_800C9E00;
void sub_800BFDEC()
{
    int m;
    int n;
    int diff;
    int i;
    int k;
    int one;
    int bit;
    BatXY_a* pp;
    m = sub_800A248C();
    if (m != 0 && sub_800A2AB4() != 0)
    {
        m = 0x10;
    }
    n = GetCapturedMinionsFromBitfield_8003BA58(m);
    if (dword_800C9E24 != m)
    {
        diff = (dword_800C9E24 | m) ^ m;
        dword_800C9E24 = m;
        one = 1;
        dword_800C9DF8 |= one;
        dword_800C9E00 = 0;
        for (i = 0; i < 3; i++)
        {
            if (diff & (one << (i + 4)))
            {
                if (sub_800A2AB4() != 2)
                {
                    dword_800C9E08[i]->flags &= ~1;
                    dword_800C9E08[i]->flags |= 0x8000;
                }
                else
                {
                    sub_800BC838(0x10000);
                }
            }
            if (m & (one << (i + 4)))
            {
                dword_800C9E18[i].x = ((short*)dword_800C9E28[i])[4];
                dword_800C9E18[i].y = ((short*)dword_800C9E28[i])[5];
            }
        }
    }
    if (dword_800C9DF8 & 1)
    {
        if (dword_800C9E00 < 4)
        {
            dword_800C9E00++;
            k = 0;
            for (i = 0, bit = 1; i < 3; i++)
            {
                if (m & (bit << (i + 4)))
                {
                    pp = (BatXY_a*)((char*)dword_800C9140 + ((n - 1) * 12 + k * 4));
                    ((short*)dword_800C9E28[i])[4] += (pp->x - ((short*)dword_800C9E28[i])[4]) * dword_800C9E00 >> 2;
                    ((short*)dword_800C9E28[i])[5] += (pp->y - ((short*)dword_800C9E28[i])[5]) * dword_800C9E00 >> 2;
                    k++;
                }
            }
        }
        else
        {
            dword_800C9DF8 &= ~1;
        }
    }
}

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

extern int sub_800C0904(unsigned char* p);
void sub_800C064C(unsigned char* m, int* o, int c)
{
    unsigned char ids[8];
    int counts[3];
    int self;
    int t;
    self = *(unsigned short*)sub_80019C70(m[2]);
    o[0] = sub_800338DC(m + 0x4C, ids, counts);
    o[1] = *(unsigned short*)sub_80019C70(ids[0]);
    o[2] = *(unsigned short*)sub_80019C70(ids[1]);
    o[3] = *(unsigned short*)sub_80019C70(ids[2]);
    o[4] = counts[0];
    o[5] = counts[1];
    o[6] = counts[2];
    if (o[1] == o[2])
    {
        if (o[2] == o[3])
        {
            o[4] += o[5];
            o[4] += o[6];
            o[5] = 0;
            o[6] = 0;
            o[0] = 1;
        }
        else
        {
            o[4] += o[5];
            o[2] = o[3];
            o[5] = o[6];
            o[0] = 2;
            o[6] = 0;
        }
    }
    else if (o[1] == o[3])
    {
        o[4] += o[6];
        o[6] = 0;
        o[0] = 2;
    }
    else if (o[2] == o[3])
    {
        o[5] += o[6];
        o[6] = 0;
        o[0] = 2;
    }
    o[11] = 0;
    if (o[1] != self)
    {
        if (o[2] == self)
        {
            o[2] = o[1];
            o[1] = self;
            t = o[5];
            o[5] = o[4];
            o[4] = t;
        }
        else if (o[3] == self)
        {
            o[3] = o[1];
            o[1] = self;
            t = o[6];
            o[6] = o[4];
            o[4] = t;
        }
        else if (o[0] < 2)
        {
            o[2] = o[1];
            o[1] = self;
            o[5] = o[4];
            o[4] = 0;
            o[0] = 2;
        }
        else
        {
            o[3] = o[1];
            o[1] = self;
            o[6] = o[4];
            o[4] = 0;
            o[0] = 3;
        }
    }
    o[7] = sub_80019A80(m[0xC8]);
    o[8] = o[0] - 1;
    o[10] = *(unsigned short*)sub_80019C70(m[3]);
    o[12] = c;
    o[9] = sub_800C0904(m + 0xC2);
    if (o[9] == -1000)
    {
        o[9] = ((unsigned char*)sub_80019C70(m[3]))[2] * 2;
    }
    else
    {
        o[9] -= ((unsigned char*)sub_80019C70(m[3]))[3] * 2;
        if (o[9] < 0)
        {
            o[9] += 360;
        }
    }
}

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

typedef struct BatSpark_a
{
    int frame_0;
    int f4;
    short speed_8;
    short padA;
    int padC;
    int pos_10[3];
    int base_1C[3];
    int vel_28[3];
    short rot_34[4];
    int* anim_3C;
    int* target_40;
    int* offset_44;
} BatSpark_a;
extern int dword_800795D4;
extern int* sub_80044010();
void sub_800C17EC(EventEntry* t, BatSpark_a* u)
{
    int s[3];
    int* d;
    int i;
    char* e;
    int* a = u->target_40;
    int* b = u->offset_44;
    u->vel_28[0] = u->vel_28[0] * 31 / 32 + ((a[0] + b[0] - u->pos_10[0]) << 5);
    u->vel_28[1] = u->vel_28[1] * 31 / 32 + ((a[1] + b[1] - u->pos_10[1]) << 5);
    u->vel_28[2] = u->vel_28[2] * 31 / 32 + ((a[2] + b[2] - u->pos_10[2]) << 5);
    s[0] = u->vel_28[0] / 1024;
    s[1] = u->vel_28[1] / 1024;
    s[2] = u->vel_28[2] / 1024;
    u->pos_10[0] += s[0];
    u->pos_10[1] += s[1];
    u->pos_10[2] += s[2];
    d = u->anim_3C;
    if (u->frame_0 / 4096 < d[0])
    {
        for (i = 0; i < ((unsigned char*)d[1])[u->frame_0 / 4096]; i++)
        {
            e = ((char**)d[2])[u->frame_0 / 4096] + i * 0x1C;
            sub_80044010(&d[3], u->pos_10, u->rot_34, e, e + 4, e + 8, e + 0xC, &dword_800795D4, e + 0x18, 0, 0x30, pOT_8008D690);
        }
        u->frame_0 += u->speed_8;
    }
    else
    {
        t->flags = (t->flags & ~1) | 0x8000;
    }
}

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

void sub_800C1DA4(EventEntry* t, BatSpark_a* u)
{
    int s[3];
    int* d;
    int i;
    char* e;
    int* sd;
    u->vel_28[0] = u->vel_28[0] * 15 / 16;
    u->vel_28[1] = u->vel_28[1] * 15 / 16 + 0x200;
    u->vel_28[2] = u->vel_28[2] * 15 / 16;
    s[0] = u->vel_28[0] / 1024;
    s[1] = u->vel_28[1] / 1024;
    s[2] = u->vel_28[2] / 1024;
    u->pos_10[0] += s[0];
    u->pos_10[1] += s[1];
    u->pos_10[2] += s[2];
    sd = (int*)&saveData_8008B570;
    if (u->pos_10[1] > sd[0x7AC / 4])
    {
        u->vel_28[1] = -u->vel_28[1];
        u->pos_10[1] = sd[0x7AC / 4];
    }
    d = u->anim_3C;
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

void sub_800C2170(EventEntry* t, BatSpark_a* u)
{
    int* d;
    int i;
    char* e;
    u->rot_34[1] += 0x40;
    u->vel_28[0] = u->vel_28[0] * 12 / 13;
    u->vel_28[1] = u->vel_28[1] * 12 / 13 - 0x400;
    u->vel_28[2] = u->vel_28[2] * 12 / 13;
    {
        int s[3];
        s[0] = u->vel_28[0] / 1024;
        s[1] = u->vel_28[1] / 1024;
        s[2] = u->vel_28[2] / 1024;
        u->pos_10[0] += s[0];
        u->pos_10[1] += s[1];
        u->pos_10[2] += s[2];
    }
    d = u->anim_3C;
    if (u->frame_0 / 4096 < d[0])
    {
        for (i = 0; i < ((unsigned char*)d[1])[u->frame_0 / 4096]; i++)
        {
            short c[3];
            e = ((char**)d[2])[u->frame_0 / 4096] + i * 0x1C;
            c[0] = u->pos_10[0];
            c[1] = u->pos_10[1];
            c[2] = u->pos_10[2];
            sub_80044010(&d[3], u->base_1C, u->rot_34, e, e + 4, e + 8, e + 0xC, c, e + 0x18, 0, 0x30, pOT_8008D690);
        }
        u->frame_0 += u->speed_8;
    }
    else
    {
        t->flags = (t->flags & ~1) | 0x8000;
    }
}

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
extern void PlaySfx_80031494(int id);
extern int sub_80020F00(void* p, int a, int b);
extern void sub_800C273C();
#if 0 // Not matched: only u and the hoisted sinTable base swap saved registers (s5/s6); tried decl order, explicit table pointer, early return, temp for the first lookup
void sub_800C23D0(EventEntry* t, BatSpark_a* u)
{
    int i;
    int a;
    int k;
    int n;
    EventEntry* e;
    BatShard_a* b;
    if (++u->frame_0 >= 30)
    {
        PlaySfx_80031494(0x4F);
        sub_800C1A5C(u->pos_10, (short*)&dword_800795D4, effectFile_80091BD0[0x20 / 4] + sub_80020F00(effectFile_80091BD0, 0, 0x21) * 52, 0x1000);
        for (i = 0; i < 24; i++)
        {
            e = AllocEventEntry_80043AF8(dword_8008D60C);
            if (e)
            {
                b = e->buffer;
                b->base_1C[0] = u->pos_10[0];
                b->base_1C[1] = u->pos_10[1];
                b->base_1C[2] = u->pos_10[2];
                b->frame_0 = 0;
                b->scale_C = (rand() & 0x7FF) + 0x800;
                b->pos_10[0] = 0;
                b->pos_10[1] = 0;
                b->pos_10[2] = 0;
                a = (i << 12) / 24;
                b->vel_28[0] = ((rand() & 0x1F) + 0x28) * sinTable_80084540[a & 0xFFF] / 4096;
                b->vel_28[2] = ((rand() & 0x1F) + 0x28) * sinTable_80084540[(a + 0x400) & 0xFFF] / 4096;
                k = rand() & 0x1FF;
                a = k + 0x200;
                b->vel_28[1] = -((rand() & 0x1F) + 0x28) * sinTable_80084540[a] / 4096;
                b->vel_28[0] = b->vel_28[0] * sinTable_80084540[k | 0x600] / 4096;
                b->vel_28[2] = b->vel_28[2] * sinTable_80084540[k | 0x600] / 4096;
                b->vel_28[0] <<= 10;
                b->vel_28[1] <<= 10;
                b->vel_28[2] <<= 10;
                b->rot_34[0] = rand() & 0x1000;
                b->rot_34[1] = rand() & 0x1000;
                b->rot_34[2] = rand() & 0x1000;
                b->rot_34[3] = (rand() & 0x1FF) + 0x100;
                n = sub_80020F00(effectFile_80091BD0, 1, 0x19);
                e->flags = (e->flags | 1) & 0xFFFF7FFF;
                {
                    int* ent = (int*)(effectFile_80091BD0[0x28 / 4] + n * 28);
                    b->anim_3C = (int*)(ent[1] + (i % 8) * 84);
                }
                e->cb_8 = (EventEntryFn)sub_800C273C;
            }
        }
        t->flags = (t->flags & ~1) | 0x8000;
    }
}
#endif
INCLUDE_OVERLAY_ASM(battle, sub_800C23D0);

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

extern void sub_800C2CD8();
extern void sub_800C23D0();
typedef struct BatSrc_a
{
    char pad0[0x1C];
    int* pos_1C;
} BatSrc_a;
extern void VectorToAngles_8003B5D4(int* v, short* rot);
void sub_800C2914(BatSrc_a* p, int id)
{
    EventEntry* e;
    BatShard_a* b;
    int i;
    int a;
    int n;
    int s[3];
    e = AllocEventEntry_80043AF8(dword_8008D60C);
    if (e)
    {
        b = e->buffer;
        b->pos_10[0] = p->pos_1C[0];
        b->pos_10[1] = p->pos_1C[1];
        b->pos_10[2] = p->pos_1C[2];
        b->frame_0 = 0;
        n = sub_80020F00(effectFile_80091BD0, 1, id);
        e->flags = (e->flags | 1) & 0xFFFF7FFF;
        b->anim_3C = (int*)(effectFile_80091BD0[0x28 / 4] + n * 28);
        e->cb_8 = (EventEntryFn)sub_800C23D0;
    }
    for (i = 0; i < 8; i++)
    {
        e = AllocEventEntry_80043AF8(dword_8008D60C);
        if (e)
        {
            b = e->buffer;
            b->base_1C[0] = p->pos_1C[0];
            b->base_1C[1] = p->pos_1C[1];
            b->base_1C[2] = p->pos_1C[2];
            b->frame_0 = 0;
            b->scale_C = (rand() & 0x7FF) + 0x800;
            a = i << 9;
            b->pos_10[0] = sinTable_80084540[a & 0xFFF] * 300 / 4096;
            b->pos_10[2] = sinTable_80084540[(a + 0x400) & 0xFFF] * 300 / 4096;
            a = rand() & 0x3FF;
            b->pos_10[1] = -(sinTable_80084540[a] * 300) / 4096;
            b->pos_10[0] = b->pos_10[0] * sinTable_80084540[(a + 0x400) & 0xFFF] / 4096;
            b->pos_10[2] = b->pos_10[2] * sinTable_80084540[(a + 0x400) & 0xFFF] / 4096;
            b->pos_10[0] <<= 10;
            b->pos_10[1] <<= 10;
            b->pos_10[2] <<= 10;
            b->vel_28[0] = -b->pos_10[0] / 4;
            b->vel_28[1] = -b->pos_10[1] / 4;
            b->vel_28[2] = -b->pos_10[2] / 4;
            s[0] = b->vel_28[0] / 1024;
            s[1] = b->vel_28[1] / 1024;
            s[2] = b->vel_28[2] / 1024;
            VectorToAngles_8003B5D4(s, b->rot_34);
            b->rot_34[2] = rand() & 0x1000;
            n = sub_80020F00(effectFile_80091BD0, 1, id);
            e->flags = (e->flags | 1) & 0xFFFF7FFF;
            b->anim_3C = (int*)(effectFile_80091BD0[0x28 / 4] + n * 28);
            e->cb_8 = (EventEntryFn)sub_800C2CD8;
        }
    }
}

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

typedef struct BatVec_a
{
    int x;
    int y;
    int z;
} BatVec_a;
typedef struct BatTrail_a
{
    int frame_0;
    int count_4;
    short speed_8;
    char padA[0x3A];
    int pos_44[3];
    BatVec_a trail_50[4];
    short rot_80[4];
    int* anim_88;
    int* model_8C;
} BatTrail_a;
extern void sub_80044D0C();
extern void sub_800459E4();
extern char dword_800C91A4[];
void sub_800C2FC8(EventEntry* t, BatTrail_a* u)
{
    int* d = u->anim_88;
    int i;
    int* r;
    char* e;
    if (u->frame_0 / 4096 < d[0])
    {
        r = 0;
        for (i = 0; i < ((unsigned char*)d[1])[u->frame_0 / 4096]; i++)
        {
            e = ((char**)d[2])[u->frame_0 / 4096] + i * 0x1C;
            r = sub_80044010(&d[3], u->pos_44, u->rot_80, e, e + 4, e + 8, e + 0xC, e + 0x10, e + 0x18, 0, 0x30, pOT_8008D690);
        }
        u->trail_50[0].x = u->pos_44[0] + r[0];
        u->trail_50[0].y = u->pos_44[1] + r[1];
        u->trail_50[0].z = u->pos_44[2] + r[2];
        if (u->count_4 == 0)
        {
            u->trail_50[3].x = u->trail_50[0].x;
            u->trail_50[3].y = u->trail_50[0].y;
            u->trail_50[3].z = u->trail_50[0].z;
            u->trail_50[2].x = u->trail_50[0].x;
            u->trail_50[2].y = u->trail_50[0].y;
            u->trail_50[2].z = u->trail_50[0].z;
            u->trail_50[1].x = u->trail_50[0].x;
            u->trail_50[1].y = u->trail_50[0].y;
            u->trail_50[1].z = u->trail_50[0].z;
        }
        u->frame_0 += u->speed_8;
        sub_80044D0C(u->model_8C[1], pOT_8008D690, &u->trail_50[0], u->rot_80, stru_8008D534, 0x30, 0, 0);
        sub_80044D0C(u->model_8C[1] + 0x54, pOT_8008D690, &u->trail_50[1], u->rot_80, stru_8008D534, 0x30, 0, 1);
        sub_80044D0C(u->model_8C[1] + 0xA8, pOT_8008D690, &u->trail_50[2], u->rot_80, stru_8008D534, 0x30, 0, 2);
        sub_80044D0C(u->model_8C[1] + 0xFC, pOT_8008D690, &u->trail_50[3], u->rot_80, stru_8008D534, 0x30, 0, 3);
        sub_800459E4(dword_800C91A4, u->model_8C + 2, pOT_8008D690, 0x30);
    }
    else
    {
        t->flags = (t->flags & ~1) | 0x8000;
    }
    if (++u->count_4 & 1)
    {
        u->trail_50[3].x = u->trail_50[2].x;
        u->trail_50[3].y = u->trail_50[2].y;
        u->trail_50[3].z = u->trail_50[2].z;
        u->trail_50[2].x = u->trail_50[1].x;
        u->trail_50[2].y = u->trail_50[1].y;
        u->trail_50[2].z = u->trail_50[1].z;
        u->trail_50[1].x = u->trail_50[0].x;
        u->trail_50[1].y = u->trail_50[0].y;
        u->trail_50[1].z = u->trail_50[0].z;
    }
}

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

typedef struct BatKey_a
{
    short model_0;
    short alpha_2;
    int x_4;
    int y_8;
    int z_C;
    short rot_10[3];
    short pad16;
    int f18[3];
    int mode_24;
} BatKey_a;
typedef struct BatClip_a
{
    int f0;
    char* models_4;
    int f8;
    int fC;
    int count_10;
    int frames_14;
    BatKey_a* keys_18;
} BatClip_a;
typedef struct BatAnim_a
{
    int frame_0;
    char pad4[0x40];
    int pos_44[3];
    char pad50[0x32];
    short rot_82;
    char pad84[4];
    BatClip_a* clip_88;
} BatAnim_a;
extern void sub_80045E48();
#if 0 // Not matched: only u and c swap saved registers (s1/s2); tried decl/init order, early return, tail shapes, pointer arithmetic
void sub_800C33E4(EventEntry* t, BatAnim_a* u)
{
    BatClip_a* c = u->clip_88;
    int any;
    int i;
    BatKey_a* k;
    int v[3];
    short r[3];
    any = 0;
    if (u->frame_0 < c->frames_14)
    {
        for (i = 0; i < c->count_10; i++)
        {
            k = &c->keys_18[i + u->frame_0 * c->count_10];
            if (k->model_0 >= 0)
            {
                r[0] = k->rot_10[0];
                r[1] = k->rot_10[1];
                r[2] = k->rot_10[2];
                r[1] += u->rot_82;
                v[0] = u->pos_44[0] + k->x_4 * sinTable_80084540[(u->rot_82 + 0x400) & 0xFFF] / 4096 + k->z_C * sinTable_80084540[u->rot_82 & 0xFFF] / 4096;
                v[1] = u->pos_44[1] + k->y_8;
                v[2] = u->pos_44[2] - k->x_4 * sinTable_80084540[u->rot_82 & 0xFFF] / 4096 + k->z_C * sinTable_80084540[(u->rot_82 + 0x400) & 0xFFF] / 4096;
                sub_80044D0C(c->models_4 + k->model_0 * 84, pOT_8008D690, v, r, stru_8008D534, (0x1000 - k->alpha_2) << 16 | 0x80 | k->mode_24, k->f18, i);
                if (*(int*)(c->models_4 + k->model_0 * 84 + 0x48))
                {
                    any = 1;
                }
            }
        }
        u->frame_0++;
        if (any)
        {
            if (c->f8)
            {
                sub_800459E4(dword_800C91A4, &c->f8, pOT_8008D690, 0x30);
            }
        }
        else if (c->f8)
        {
            sub_80045E48(&c->f8, pOT_8008D690, 0x30);
        }
    }
    else
    {
        t->flags = (t->flags & ~1) | 0x8000;
    }
}
#endif
INCLUDE_OVERLAY_ASM(battle, sub_800C33E4);

INCLUDE_OVERLAY_ASM(battle, sub_800C371C);

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

typedef struct BatOrb_a
{
    int frame_0;
    char pad4[0xA];
    short fx_E;
    char pad10[0x28];
    int vel_38[3];
    int pos_44[3];
} BatOrb_a;
extern char* dword_8008B4A4;
extern int DistanceSquared3D_8003B80C(int* a, int* b);
void sub_800C3DF8(EventEntry* t, BatOrb_a* u)
{
    int v[3];
    int* q;
    BatOrb_a* w;
    w = u;
    sub_800C1A5C(u->pos_44, (short*)&dword_800795D4, effectFile_80091BD0[0x20 / 4] + u->fx_E * 52, 0x1000);
    q = *(int**)(dword_8008B4A4 + 0x24);
    v[0] = q[0x5E4 / 4];
    v[1] = q[0x5E8 / 4];
    v[2] = q[0x5EC / 4];
    v[0] += ((int*)levantPos_8008BD18)[0];
    v[1] += ((int*)levantPos_8008BD18)[1];
    v[2] += ((int*)levantPos_8008BD18)[2];
    if (DistanceSquared3D_8003B80C(v, u->pos_44) >= 0x57E5)
    {
        u->vel_38[0] += ((v[0] - u->pos_44[0]) << 10) / 70;
        u->vel_38[1] += ((v[1] - u->pos_44[1]) << 10) / 70;
        u->vel_38[2] += ((v[2] - u->pos_44[2]) << 10) / 70;
        u->vel_38[0] = u->vel_38[0] * 31 / 32;
        u->vel_38[1] = u->vel_38[1] * 31 / 32;
        u->vel_38[2] = u->vel_38[2] * 31 / 32;
        u->pos_44[0] += u->vel_38[0] / 1024;
        u->pos_44[1] += u->vel_38[1] / 1024;
        u->pos_44[2] += u->vel_38[2] / 1024;
    }
    else
    {
        ((void (*)())sub_800C1C5C)(v, &dword_800795D4, effectFile_80091BD0[0x20 / 4] + w->fx_E * 52, 0x1000);
        t->flags = (t->flags & ~1) | 0x8000;
    }
}

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

extern int sub_800C473C();
void sub_800C46FC()
{
    sub_800C473C();
}

void sub_800C471C()
{
    sub_800C473C();
}

extern int sub_800C6BD0();
extern int sub_800C6EC8();
extern int sub_800C6DF8();
extern int sub_800C6A8C();
extern int sub_800C6A68();
int sub_800C473C(BatTask* t)
{
    unsigned char* s = (unsigned char*)t->f10;
    int r;
    int i;
    if ((sub_800BC868() == 0 || sub_800BC868() == -1) && (r = sub_800C6BD0(t, 0x16)))
    {
        return r;
    }
    if ((sub_800BC868() == 1 || sub_800BC868() == -1) && (r = sub_800C6BD0(t, 0x15)))
    {
        return r;
    }
    if ((sub_800BC868() == 2 || sub_800BC868() == -1) && (r = sub_800C6BD0(t, 0x18)))
    {
        return r;
    }
    if ((sub_800BC868() == 3 || sub_800BC868() == -1) && (r = sub_800C6BD0(t, 0x17)))
    {
        return r;
    }
    if (sub_800C6EC8(t, 0x3F8) == 0 && rand() % 10 < 7 && (r = sub_800C6BD0(t, 0x13)))
    {
        return r;
    }
    if (sub_800C6EC8(t, 2) == 0 && rand() % 10 < 7 && (r = sub_800C6BD0(t, 0x12)))
    {
        return r;
    }
    if (sub_800C6EC8(t, 1) == 0 && rand() % 10 < 7 && (r = sub_800C6BD0(t, 0x11)))
    {
        return r;
    }
    if ((rand() & 1) && (r = sub_800C6BD0(t, 0x14)))
    {
        return r;
    }
    if ((r = sub_800C6DF8(t, 0xD)))
    {
        return r;
    }
    if (s[0x2D] > s[0x2F])
    {
        if (rand() % 10 < 8 && (r = sub_800C6A8C(t)))
        {
            return r;
        }
    }
    else
    {
        for (i = 0; i < 12; i++)
        {
            if ((r = sub_800C6BD0(t, i)))
            {
                return r;
            }
        }
    }
    return sub_800C6A68(t);
}

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

INCLUDE_OVERLAY_ASM(battle, sub_800C61FC);

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

typedef struct BatUseQ_a
{
    short f0;
    short f2;
    short f4;
    short f6;
    short f8;
    short fA;
    int minion_C;
} BatUseQ_a;
typedef struct BatTgtQ_a
{
    short f0;
    short f2;
    short f4;
    short f6;
} BatTgtQ_a;
extern char* dword_800C9E44;
extern char* dword_800C9E6C;
extern int dword_800C9E5C;
extern int dword_800C93A0;
extern int dword_800C9380;
extern int dword_800C939C;
extern int dword_800C9398;
extern int dword_800C9390;
extern int dword_800C937C;
extern int GetMenuCursorIndex_8003DA54(void*);
extern int CheckItemUsable_80033AFC(BatUseQ_a* q);
extern int CheckMagicCastable_80033C08(BatUseQ_a* q);
extern int sub_80033C98(BatUseQ_a* q);
extern int sub_80033DF4(BatTgtQ_a* q);
extern int sub_80034068(BatTgtQ_a* q);
extern unsigned char sub_800C78D0();
int sub_800C7530()
{
    BatUseQ_a q;
    BatTgtQ_a b;
    short idx;
    int* p;
    idx = GetMenuCursorIndex_8003DA54(dword_800C9E44);
    q.f0 = ((short*)dword_800C9E44)[4];
    q.f2 = ((short*)dword_800C9E44)[5];
    q.fA = 0;
    dword_800C9E7C = 0;
    switch (dword_800C9E50)
    {
    case 0:
        p = *(int**)(dword_800C9E6C + idx * 8 + 4);
        if (p == 0)
        {
            return 1;
        }
        dword_800C9E7C = *p;
        return 0;
    case 1:
        switch (CheckItemUsable_80033AFC(&q))
        {
        case 0:
            return 1;
        case 1:
            return 0;
        case 2:
        case 4:
            dword_800C9E7C = dword_800C93A0;
            return 0;
        case 3:
        case 5:
        case 6:
        case 7:
        default:
            return 1;
        }
    case 2:
        q.minion_C = (int)GetMinion_80010598(3, dword_800C9C7C - 1);
        switch (sub_80033C98(&q))
        {
        case 0:
        case 1:
        case 2:
        case 3:
        case 4:
        case 6:
        default:
            return 1;
        case 5:
            dword_800C9E7C = dword_800C9380;
            return 0;
        case 7:
            return 0;
        }
    case 3:
        q.minion_C = (int)GetMinion_80010598(3, dword_800C9C7C - 1);
        switch (CheckMagicCastable_80033C08(&q))
        {
        case 0:
        case 1:
        case 2:
        case 3:
        case 4:
        case 7:
        default:
            return 1;
        case 5:
            dword_800C9E7C = dword_800C9380;
            return 0;
        case 6:
            return 0;
        }
    case 4:
        b.f0 = dword_800C9E5C;
        b.f2 = dword_800C9C7C;
        b.f4 = *(unsigned short*)&dword_800C9E54;
        b.f6 = 0;
        if (sub_800C78D0() == 4)
        {
            switch (sub_80033DF4(&b))
            {
            case 0:
                return 1;
            case 1:
                dword_800C9E7C = dword_800C939C;
                return 0;
            case 2:
                dword_800C9E7C = dword_800C9398;
                return 0;
            case 3:
                dword_800C9E7C = dword_800C9390;
                return 0;
            case 4:
                break;
            default:
                return 1;
            }
        }
        else if (sub_800C78D0() == 6)
        {
            switch (((int (*)(BatTgtQ_a*))sub_80034124)(&b))
            {
            case 0:
                return 1;
            case 1:
                dword_800C9E7C = dword_800C939C;
                return 0;
            case 2:
                return 0;
            case 3:
                dword_800C9E7C = dword_800C9390;
                return 0;
            case 4:
                break;
            default:
                return 1;
            }
        }
        else if (sub_800C78D0() == 7)
        {
            switch (sub_80034068(&b))
            {
            case 0:
                return 1;
            case 1:
                dword_800C9E7C = dword_800C939C;
                return 0;
            case 2:
                return 0;
            case 3:
                dword_800C9E7C = dword_800C9390;
                return 0;
            case 4:
                break;
            default:
                return 1;
            }
        }
        else if (sub_800C78D0() == 2 || sub_800C78D0() == 8)
        {
            if (sub_80033548((int*)sub_80014390(dword_800C9E54), 0x400) == 0)
            {
                return 1;
            }
        }
        else
        {
            return 1;
        }
        dword_800C9E7C = dword_800C937C;
        return 0;
    case 5:
    default:
        return 1;
    }
}
INCLUDE_OVERLAY_ASM(battle, dword_800BA238);

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
void sub_800C79B8()
{
    sub_800AD288((short)GetMenuCursorIndex_8003DA54(dword_800C9308), 0);
}

extern int GetMenuCursorIndex_8003DA54(void*);
void sub_800C79EC()
{
    sub_80031BDC((short)GetMenuCursorIndex_8003DA54(dword_800C92E4));
}

extern unsigned char dword_800C9C7C;
void sub_800C7A1C()
{
    char* h = sub_80010824(3, dword_800C9C7C - 1);
    FindNthMagicBit_8001AEC0(h, (short)GetMenuCursorIndex_8003DA54(dword_800C92F0));
}

extern unsigned char dword_800C9660[];
extern unsigned char dword_800C9654[];
extern int dword_800C96A4[];
extern unsigned int dword_800C9E64;
extern int sub_8001CE8C(int a);
extern int sub_80031B30(int a);
extern int sub_80031B0C(int a, int b);
extern int FindNthMagicBit_8001AEC0(char* h, int n);
extern int sub_8001ACE4(int a);
void sub_800C7A6C()
{
    int h;
    char* m;
    dword_800C9E40 = dword_800C9E50;
    switch (dword_800C9E50)
    {
    case 0:
        dword_800C9E68 = dword_800C9660[sub_800C78D0()];
        dword_800C9E50 = dword_800C9654[sub_800C78D0()];
        dword_800C9E58[0] = dword_800C96A4[sub_800C78D0()];
        break;
    case 1:
        dword_800C9E68 = sub_8001CE8C(((int (*)())sub_800C79B8)());
        dword_800C9E50 = 4;
        dword_800C9E5C = ((int (*)())sub_800C79B8)();
        break;
    case 2:
        h = sub_80031B30(dword_800C9C7C);
        dword_800C9E68 = sub_80031B0C(h, sub_80031BDC((short)GetMenuCursorIndex_8003DA54(dword_800C92E4)));
        dword_800C9E50 = 4;
        dword_800C9E5C = ((int (*)())sub_800C79EC)();
        break;
    case 3:
        m = sub_80010824(3, dword_800C9C7C - 1);
        dword_800C9E68 = sub_8001ACE4(FindNthMagicBit_8001AEC0(m, (short)GetMenuCursorIndex_8003DA54(dword_800C92F0)));
        dword_800C9E50 = 4;
        dword_800C9E5C = ((int (*)())sub_800C7A1C)();
        break;
    case 4:
        dword_800C9E50 = 5;
        dword_800C9E64 = sub_800C791C();
        break;
    case 5:
        break;
    }
    if (dword_800C9E50 == 4)
    {
        if (sub_800C78D0() == 4)
        {
            dword_800C9320[0].f2 = dword_800C9E4B + 1;
            dword_800C9320[0].count_4 = dword_800C9E4B + 1;
        }
        else if (sub_800C78D0() == 2)
        {
            dword_800C9320[0].f2 = dword_800C9E4B;
            dword_800C9320[0].count_4 = dword_800C9E4B;
        }
        else if (sub_800C78D0() == 7)
        {
            dword_800C9320[0].f2 = 1;
            dword_800C9320[0].count_4 = 1;
        }
        else if (sub_800C78D0() == 8)
        {
            dword_800C9320[0].f2 = dword_800C9E4B;
            dword_800C9320[0].count_4 = dword_800C9E4B;
        }
        dword_800C9320[0].cursor_8 = 0;
        dword_800C9320[0].scroll_A = 0;
    }
}

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
INCLUDE_OVERLAY_ASM(battle, sub_800C7DA8);

typedef struct BatAct_a
{
    int f0;
    int f4;
    int targets_8;
    int mask_C;
} BatAct_a;
typedef struct BatDmg_a
{
    int f0;
    int f4;
    int f8;
    int dx_C;
    int dy_10;
    int dx_14;
    int dy_18;
    int dx_1C;
    int dy_20;
    short h24;
    short h26;
} BatDmg_a;
typedef struct BatRange_a
{
    char pad0[8];
    short lo_8;
    short hi_A;
    short lo_C;
    short hi_E;
} BatRange_a;
extern short dword_800C9180;
extern short dword_800C9182;
extern void sub_80012BB0(int a, BatRange_a* b, BatAct_a* c, BatDmg_a* d);
extern int sub_80013228(int a, BatRange_a* b, BatAct_a* c, BatDmg_a* d);
void sub_800C83B0()
{
    BatTgtQ_a b;
    BatAct_a a;
    BatDmg_a d;
    unsigned int i;
    int bit;
    int self;
    BatRange_a* m;
    a = *(BatAct_a*)dword_800C9E58;
    if (dword_800C9E50 == 4)
    {
        dword_800C9180 = 0;
        dword_800C9182 = 0;
        self = sub_80014390(dword_800C9C7C);
        for (i = 0; i < 4; i++)
        {
            bit = 1 << i;
            if ((((BatAct_a*)dword_800C9E58)->mask_C & bit) && i == dword_800C9C99)
            {
                m = (BatRange_a*)sub_80014390(i & 0xFF);
                d.h24 = (signed char)dword_800C9D82;
                d.h26 = (signed char)dword_800C9D83;
                a.mask_C = bit;
                sub_80012BB0(self, m, &a, &d);
                if (sub_80013228(self, m, &a, &d) == 0 && (((BatAct_a*)dword_800C9E58)->targets_8 & bit))
                {
                    dword_800C9180 -= d.dx_C;
                    dword_800C9182 -= d.dy_10;
                    dword_800C9180 -= d.dx_14;
                    dword_800C9182 -= d.dy_18;
                }
                dword_800C9180 -= d.dx_1C;
                dword_800C9182 -= d.dy_20;
                if (dword_800C9180 > m->hi_A - m->lo_8)
                {
                    dword_800C9180 = m->hi_A - m->lo_8;
                }
                if (dword_800C9182 > m->hi_E - m->lo_C)
                {
                    dword_800C9182 = m->hi_E - m->lo_C;
                }
            }
        }
        b.f0 = dword_800C9E5C;
        b.f2 = dword_800C9C7C;
        b.f4 = *(unsigned short*)&dword_800C9E54;
        b.f6 = 0;
        if (sub_800C78D0() == 4)
        {
            if (sub_80033DF4(&b))
            {
                dword_800C9180 = 0;
                dword_800C9182 = 0;
            }
        }
        else if (sub_800C78D0() == 6)
        {
            if (((int (*)(BatTgtQ_a*))sub_80034124)(&b))
            {
                dword_800C9180 = 0;
            }
        }
        else if (sub_800C78D0() == 7)
        {
            if (sub_80034068(&b))
            {
                dword_800C9180 = 0;
            }
        }
    }
}

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
    sub_800C7DA8();
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
