// BATTLE.BIN
#include "common.h"
#include "funcs.h"
#include "globals.h"

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
extern int sub_800C6EFC();
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
extern unsigned char dword_800C9C8C;
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
extern void sub_800BE058();
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
    sub_80020898();
    if (dword_80091C74 >= 0)
    {
        sub_800AC708(dword_80091C74, 1);
    }
    eventDispatchHalt_8008B540 = 1;
    t->next_8 = sub_800BA848;
}

INCLUDE_OVERLAY_ASM(battle, sub_800BA848);

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

#if 0
void sub_800BABC4()
{
    int i;
    int mask;
    BatEnt_a* p = dword_800B1238;
    for (i = 0; i < 3; i++)
    {
        mask = 1 << (i + 4);
        if (sub_800A248C() & mask)
        {
            sub_800A2BE4(i);
        }
        p->b = -1;
        p->a = 0;
        p->d = 0;
        p->c = 0;
        p->e = 7;
        p++;
    }
}
#endif
INCLUDE_OVERLAY_ASM(battle, sub_800BABC4);

INCLUDE_OVERLAY_ASM(battle, sub_800BAC4C);

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
        u->fc = sub_800C6EFC();
        t->next_8 = sub_800BB940;
    }
}

#if 0
void sub_800BB940(BatTask_a* t, BatObj_a* u)
{
    int* q;
    if ((*(int*)u->fc & 0x8001) != 1)
    {
        sub_800BC850(0x2000);
        q = &dword_800ADE78;
        if (*q == 1)
        {
            if ((q[4] = sub_800B4318(dword_800C9C88, q)) >= 0)
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
#endif
INCLUDE_OVERLAY_ASM(battle, sub_800BB940);

void sub_800BBA24(BatTask_a* t, BatObj_a* u)
{
    u->fc = sub_800BC28C(t);
    u->next_8 = sub_800BBA70;
    t->next_8 = sub_800BC144;
}

#if 0 // near miss: u and the hoisted constant 1 swap saved registers (s2/s3)
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

#if 0
void sub_800BBBF4(BatTask_a* t, BatObj_a* u)
{
    dword_800C9C88[0] = 3;
    dword_800C9C88[3] = 0;
    if (!dword_800C9C98)
    {
        sub_800BBDB4(t, u);
    }
    else
    {
        PlaySeqSlot_80031160(0x11, 1);
        u->fc = sub_800BC28C();
        u->next_8 = sub_800BBC84;
        t->next_8 = sub_800BC144;
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

#if 0
void sub_800BBEFC(BatTask_a* t, BatObj_a* u)
{
    u->fc = sub_800BC28C(t);
    u->next_8 = sub_800BBF64;
    dword_800C9C88[3] = 0;
    dword_800C9C98 = dword_800C9C8C + 4;
    t->next_8 = sub_800BC144;
}
#endif
INCLUDE_OVERLAY_ASM(battle, sub_800BBEFC);

#if 0
void sub_800BBF64(BatTask_a* t, BatObj_a* u)
{
    dword_800C9C88[0] = 0x15;
    dword_800C9C7C = dword_800C9C98;
    dword_800C9C88[2] = 1 << dword_800C9C98;
    sub_800A2AE8(dword_800C9C88);
    u->fc = sub_800BC28C();
    u->next_8 = (void (*)())u->f4;
    t->next_8 = sub_800BC144;
    sub_800BF770(dword_800C9C68, dword_800C9C7C);
}
#endif
INCLUDE_OVERLAY_ASM(battle, sub_800BBF64);

#if 0
void sub_800BBFFC(BatTask_a* t, BatObj_a* u)
{
    u->fc = sub_800BC28C(t);
    u->next_8 = sub_800BC05C;
    dword_800C9C98 = dword_800C9C8C + 4;
    t->next_8 = sub_800BC144;
}
#endif
INCLUDE_OVERLAY_ASM(battle, sub_800BBFFC);

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

#if 0
void sub_800BC4D4(int a, int b)
{
    int r = sub_800BC570(a);
    if (r == 1)
    {
        switch (sub_800BC7DC(a))
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
#endif
INCLUDE_OVERLAY_ASM(battle, sub_800BC4D4);

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

#if 0
int sub_800BC6CC(int a)
{
    int r = 0;
    int m;
    if (sub_800BC784(a))
    {
        int k = sub_800BC7DC(a);
        if (k == 1)
        {
            m = sub_800BC7DC(dword_800C9C82);
            if (m == 0)
            {
                goto zero;
            }
            if (m == k)
            {
                r = (int)sub_800C0F9C();
            }
        }
        else if (k == 0)
        {
        zero:
            r = (int)levantPos_8008BD18;
        }
        else if (k == 2)
        {
            r = sub_800A2C28(a - 4);
        }
    }
    return r;
}
#endif
INCLUDE_OVERLAY_ASM(battle, sub_800BC6CC);

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

#if 0
int sub_800BC7DC(int x)
{
    if (x == 0)
    {
        return 0;
    }
    if ((unsigned int)(x - 1) < 3)
    {
        return 1;
    }
    if ((unsigned int)(x - 4) < 3)
    {
        return 2;
    }
    return 3;
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

void sub_800BC8E8()
{
    IsEffectFileLoaded_80020EBC(dword_80095468);
}

INCLUDE_OVERLAY_ASM(battle, sub_800BC90C);

INCLUDE_OVERLAY_ASM(battle, sub_800BDA28);

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

#if 0
void sub_800BDC3C(BatTask_a* t)
{
    int k;
    if ((short)sub_800BE364() < dword_800C9D94 && sub_800BEA94() == 1)
    {
        k = dword_800C9D90;
        dword_800C9D90 = k - 1;
        if (k != 0)
        {
            do
            {
                sub_800A2924(dword_800C9DD0[dword_800C9D90]);
                k = dword_800C9D90;
                dword_800C9D90 = k - 1;
            } while (k != 0);
        }
        t->f0 = (t->f0 & ~1) | 0x8000;
        dword_800B1228 &= ~0x1000;
    }
    else
    {
        sub_800BE3C0();
        dword_800C9D94++;
    }
}
#endif
INCLUDE_OVERLAY_ASM(battle, sub_800BDC3C);

#if 0
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
        m = 1 << i;
        if (sub_800A248C() & m)
        {
            if (sub_800A2550(i - 4) == 0)
            {
                return 0;
            }
        }
    }
    return IsEffectTaskIdle_800148D4() != 0;
}
#endif
INCLUDE_OVERLAY_ASM(battle, sub_800BDD3C);

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

INCLUDE_OVERLAY_ASM(battle, sub_800BE058);

INCLUDE_OVERLAY_ASM(battle, sub_800BE14C);

#if 0
void sub_800BE2C8()
{
    int m = sub_800BE364();
    unsigned char i;
    short d = m - dword_800C9D98[0];
    dword_800C9DBC = d;
    dword_800C9D98[1] += d;
    for (i = 0; i < 7; i++)
    {
        short e = m - dword_800C9DA0[i].a;
        dword_800C9DC0[i] = e;
        dword_800C9DA0[i].b += e;
    }
}
#endif
INCLUDE_OVERLAY_ASM(battle, sub_800BE2C8);

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

INCLUDE_OVERLAY_ASM(battle, sub_800BE834);

#if 0
int sub_800BEA94()
{
    if (*(int*)&saveData_8008B570 & 0x20)
    {
        return 1;
    }
    if (sub_800BF47C() == 1)
    {
        return 0;
    }
    if (sub_800BC820(4) == 1)
    {
        if (sub_800BEB50() && sub_800BEB68())
        {
            return 1;
        }
        return 0;
    }
    if (dword_800C912C[(unsigned char)dword_800C8B38[dword_800C9C88[0]]] == 0)
    {
        return sub_800BEB50();
    }
    return sub_800BEB68();
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

#if 0
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
        q[6] = a;
        q[5] = e;
        p->cb_8 = (EventEntryFn)sub_800BF4D0;
    }
}
#endif
INCLUDE_OVERLAY_ASM(battle, sub_800BF3DC);

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

INCLUDE_OVERLAY_ASM(battle, sub_800BF4D0);

#if 0
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
        break;
    case 0:
        break;
    case 2:
        p[0] = 0;
        p[4] = 1000;
        p[5] = 500;
        p[6] = 0x14D;
        break;
    }
}
#endif
INCLUDE_OVERLAY_ASM(battle, sub_800BF648);

#if 0
int sub_800BF6BC(unsigned short* a, int b)
{
    int r = -1;
    unsigned int i;
    do
    {
        for (i = 0; i < 7; i++)
        {
            if (i >= 4 || i == b)
            {
                a[i] += sub_800BF784(i);
                if ((short)a[i] >= 1000)
                {
                    a[i] = 0;
                    r = i;
                    break;
                }
            }
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

INCLUDE_OVERLAY_ASM(battle, sub_800BF7C4);

#if 0
int sub_800BF980(int x)
{
    int r = 0;
    if (x >= 0x29)
    {
        if (x < 0x39)
        {
            r = 1;
        }
        else if (x < 0xD3 && x > 0xC8)
        {
            r = 1;
        }
    }
    return r;
}
#endif
INCLUDE_OVERLAY_ASM(battle, sub_800BF980);

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

#if 0
void sub_800BF9F0(int a)
{
    unsigned int x = a;
    unsigned int* p = allMinionsBitfields_8008BD84;
    if (x < 0xE0)
    {
        p[x >> 5] |= 1 << (x & 0x1F);
    }
}
#endif
INCLUDE_OVERLAY_ASM(battle, sub_800BF9F0);

int sub_800BFA34(int x)
{
    int y = x & 0x3F8;
    return (x & ~0x3F8) | (y << 1);
}

#if 0
int sub_800BFA4C(unsigned int a, unsigned int b)
{
    int r;
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
    return (a & 0x4000) ? 0x19 : 0x14;
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

INCLUDE_OVERLAY_ASM(battle, sub_800BFC40);

INCLUDE_OVERLAY_ASM(battle, sub_800BFDEC);

INCLUDE_OVERLAY_ASM(battle, sub_800C0074);

#if 0
void sub_800C01D8()
{
    EventEntry* e = AllocEventEntry_80043AF8(dword_8008D4B0);
    if (e)
    {
        short* q;
        e->flags = (e->flags | 1) & 0xFFFF7FFF;
        q = e->buffer;
        q[2] = 0x6E;
        q[3] = 0xAC;
        q[4] = 0x64;
        q[5] = 0x29;
        *(int*)q = 0;
        e->cb_8 = (EventEntryFn)sub_800C0254;
    }
}
#endif
INCLUDE_OVERLAY_ASM(battle, sub_800C01D8);

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

INCLUDE_OVERLAY_ASM(battle, sub_800C0BF0);

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

#if 0
BatCol_a sub_800C0DDC(int* p, int c)
{
    BatCol_a buf;
    int mask;
    memset(&buf, 0, 4);
    if (p[0] != 0x14 && (p[2] & (mask = 1 << (dword_800C918C + 1))))
    {
        sub_80018A4C(&buf, dword_800C9190.obj, p, 0, c);
    }
    return buf;
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

INCLUDE_OVERLAY_ASM(battle, sub_800C1654);

INCLUDE_OVERLAY_ASM(battle, sub_800C17EC);

INCLUDE_OVERLAY_ASM(battle, sub_800C1A5C);

INCLUDE_OVERLAY_ASM(battle, sub_800C1B2C);

INCLUDE_OVERLAY_ASM(battle, sub_800C1C5C);

INCLUDE_OVERLAY_ASM(battle, sub_800C1DA4);

INCLUDE_OVERLAY_ASM(battle, sub_800C1FFC);

INCLUDE_OVERLAY_ASM(battle, sub_800C2170);

INCLUDE_OVERLAY_ASM(battle, sub_800C23D0);

INCLUDE_OVERLAY_ASM(battle, sub_800C273C);

INCLUDE_OVERLAY_ASM(battle, sub_800C2914);

INCLUDE_OVERLAY_ASM(battle, sub_800C2CD8);

INCLUDE_OVERLAY_ASM(battle, sub_800C2E28);

INCLUDE_OVERLAY_ASM(battle, sub_800C2FC8);

INCLUDE_OVERLAY_ASM(battle, sub_800C32DC);

INCLUDE_OVERLAY_ASM(battle, sub_800C33E4);

INCLUDE_OVERLAY_ASM(battle, sub_800C371C);

INCLUDE_OVERLAY_ASM(battle, sub_800C3B50);

INCLUDE_OVERLAY_ASM(battle, sub_800C3D34);

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
INCLUDE_OVERLAY_ASM(battle, sub_800C45A8);

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

INCLUDE_OVERLAY_ASM(battle, sub_800C4A40);

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

INCLUDE_OVERLAY_ASM(battle, sub_800C4EA8);

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

INCLUDE_OVERLAY_ASM(battle, sub_800C50B0);

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

INCLUDE_OVERLAY_ASM(battle, sub_800C58BC);

INCLUDE_OVERLAY_ASM(battle, sub_800C59A0);

INCLUDE_OVERLAY_ASM(battle, sub_800C5A7C);

INCLUDE_OVERLAY_ASM(battle, sub_800C5BC0);

INCLUDE_OVERLAY_ASM(battle, sub_800C5D04);

INCLUDE_OVERLAY_ASM(battle, sub_800C5EB8);

INCLUDE_OVERLAY_ASM(battle, sub_800C6038);

INCLUDE_OVERLAY_ASM(battle, sub_800C61FC);

#if 0
void sub_800C66B4(char* buf, unsigned int b)
{
    int i;
    if (b == 0xC)
    {
        for (i = 3; i >= 0; i--)
        {
            buf[0x20 + i] = 0x30;
        }
    }
    else if (b < 0xC)
    {
        buf[0x20 + b] = 0x18;
    }
}
#endif
INCLUDE_OVERLAY_ASM(battle, sub_800C66B4);INCLUDE_OVERLAY_ASM(battle, sub_800C66F4);

INCLUDE_OVERLAY_ASM(battle, sub_800C6824);

INCLUDE_OVERLAY_ASM(battle, sub_800C6928);

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

INCLUDE_OVERLAY_ASM(battle, sub_800C6EFC);

INCLUDE_OVERLAY_ASM(battle, sub_800C7088);

extern int dword_800C9628[];
extern unsigned char dword_800C9E49;
extern int dword_800C9640;
void sub_800C71A0()
{
    dword_800C9640 = dword_800C9628[dword_800C9E49];
}

INCLUDE_OVERLAY_ASM(battle, sub_800C71C8);

extern int dword_800C9E4C;
#if 0
int sub_800C72B8()
{
    int i;
    for (i = 0; i < 3; i++)
    {
        if (dword_800C9E4C & (1 << (i + 4)))
        {
            if (sub_800A28FC(i) == 0)
            {
                return 0;
            }
        }
    }
    return 1;
}
#endif
INCLUDE_OVERLAY_ASM(battle, sub_800C72B8);
#if 0
int sub_800C7334()
{
    int i;
    for (i = 0; i < 3; i++)
    {
        if (dword_800C9E4C & (1 << (i + 4)))
        {
            if (sub_800BF980(sub_800A2BE4(i)) != 1)
            {
                return 0;
            }
        }
    }
    return 1;
}
#endif
INCLUDE_OVERLAY_ASM(battle, sub_800C7334);
extern char dword_800C932C[];
extern char dword_800C9314[];
extern char dword_800C9320[];
extern char* dword_800C9338[];
extern unsigned char dword_800C9E68;
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
INCLUDE_OVERLAY_ASM(battle, sub_800C7424);

INCLUDE_OVERLAY_ASM(battle, sub_800C7530);

extern char dword_800C92D8[];
extern unsigned char dword_800C9648[];
unsigned char sub_800C78D0()
{
    return dword_800C9648[dword_800C9E49 + (short)GetMenuCursorIndex_8003DA54(dword_800C92D8) * 2];
}

extern int dword_800C9E78;
extern unsigned char dword_800C9E72[];
#if 0
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
extern char dword_800C9308[];
void sub_800C79B8()
{
    sub_800AD288((short)GetMenuCursorIndex_8003DA54(dword_800C9308), 0);
}

extern int GetMenuCursorIndex_8003DA54(void*);
extern char dword_800C92E4[];
void sub_800C79EC()
{
    sub_80031BDC((short)GetMenuCursorIndex_8003DA54(dword_800C92E4));
}

extern char dword_800C92F0[];
extern unsigned char dword_800C9C7C;
void sub_800C7A1C()
{
    char* h = sub_80010824(3, dword_800C9C7C - 1);
    FindNthMagicBit_8001AEC0(h, (short)GetMenuCursorIndex_8003DA54(dword_800C92F0));
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
#if 0
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
        dword_800C9630.fC = dword_800C92E0;
    }
}
#endif
INCLUDE_OVERLAY_ASM(battle, sub_800C7CE8);
extern unsigned char dword_800C9E54;
extern unsigned char dword_800C9C99;
#if 0
void sub_800C7D54(unsigned char a)
{
    unsigned char v;
    if (a == 4)
    {
        if (dword_800C9E68 & 5)
        {
            v = dword_800C9C7C;
        }
        else
        {
            v = dword_800C9E54;
        }
    }
    else
    {
        v = dword_800C9C7C;
    }
    dword_800C9C99 = v;
}
#endif
INCLUDE_OVERLAY_ASM(battle, sub_800C7D54);INCLUDE_OVERLAY_ASM(battle, sub_800C7DA8);

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

extern int dword_800C9E38;
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

extern unsigned char dword_800C9E40;
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

#if 0
void sub_800C8828(int a)
{
    short rect[4];
    short p[8];
    int s[1];
    rect[0] = 0x19;
    rect[1] = 0x8A;
    rect[2] = MeasureTextWidth_8003E4C8() + 4;
    rect[3] = 0x12;
    s[0] = a;
    p[0] = rect[0];
    p[1] = rect[1];
    p[4] = rect[0] + 2;
    p[5] = rect[1] + 4;
    DrawTextLinesWindow_8002AE38(s, &p[4], 0xF, rect, 1);
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

extern unsigned short padPressed_8009194C;
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

extern int dword_800C9E58[];
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

INCLUDE_OVERLAY_ASM(battle, sub_800C8A08);

INCLUDE_OVERLAY_ASM(battle, dword_800C8B2C);
