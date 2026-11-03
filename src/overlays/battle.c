// BATTLE.BIN, source file 1 of 3
#include "battle.h"

INCLUDE_OVERLAY_ASM(battle, dword_800B66C0);

typedef struct BatStart_a
{
    int f0;
    int timer_4;
    int* flags_8;
    int c_C;
} BatStart_a;
typedef struct BatSel_a
{
    char pad_0[0x18];
    int c_18;
} BatSel_a;
extern BatSel_a* sub_800A1E3C();
extern void sub_800BA444();
extern void sub_800BA52C();
extern void sub_800BA564();
extern int sub_800BC820(unsigned int m);
extern void sub_800A8984(int a);
extern void sub_8001AAA8(int a);
extern void StopSoundSeqs_80030D68(void* a);
extern void StopSeqSlot_80031334(int a);
extern void SsSepSetDecrescendo(int, int, int, int);

#if 0
// Not matched (5 words): the original stores u->c_C before dword_800ADE78 = 0 and puts that store in the
// delay slot of the sub_80037828 call; this C gets the two stores the other way round
void sub_800BA254(BatTask_a* t, BatStart_a* u)
{
    short* p;
    BatSel_a* r;
    if ((*u->flags_8 & 0x8001) == 1)
    {
        return;
    }
    if (IsEffectTaskIdle_800148D4() != 1)
    {
        return;
    }
    r = sub_800A1E3C();
    u->c_C = r->c_18;
    dword_800ADE78 = 0;
    sub_80037828(2, 0, 0);
    switch (dword_800B1230)
    {
    case 0:
        StopSoundSeqs_80030D68(dword_80091D40);
        p = dword_80091CE0;
        if (p[2] >= 0)
        {
            SsSepSetDecrescendo(p[6], p[2], 0x7F, 0x78);
            p[2] = -1;
        }
        StopSeqSlot_80031334(0);
        PlaySeqSlot_80031160(1, 1);
        if (dword_800C9C82 != 0)
        {
            sub_800A8984(0);
        }
        else
        {
            sub_800A8984(1);
        }
        u->timer_4 = 0x3C;
        t->next_8 = sub_800BA564;
        break;
    case 1:
        sub_800A8984(0);
        u->timer_4 = 0;
        t->next_8 = sub_800BA564;
        break;
    case 2:
        sub_800A8984(0);
        if (sub_800BC820(0x20000) == 0)
        {
            FadeOutSeqSlot_800313C8(0);
        }
        else
        {
            p = dword_80091CE0;
            if (p[2] >= 0)
            {
                SsSepSetDecrescendo(p[6], p[2], 0x7F, 0x78);
                p[2] = -1;
            }
        }
        t->next_8 = sub_800BA52C;
        break;
    case 3:
        sub_800A8984(0);
        sub_8001AAA8(0x3C);
        t->next_8 = sub_800BA444;
        break;
    case 4:
    case 5:
        sub_800A8984(0);
        u->timer_4 = 0x12;
        if (sub_800BC820(0x20000) == 0)
        {
            FadeOutSeqSlot_800313C8(0);
        }
        else
        {
            p = dword_80091CE0;
            if (p[2] >= 0)
            {
                SsSepSetDecrescendo(p[6], p[2], 0x7F, 0x78);
                p[2] = -1;
            }
        }
        t->next_8 = sub_800BA52C;
        break;
    }
}
#endif

INCLUDE_OVERLAY_ASM(battle, sub_800BA254);
INCLUDE_OVERLAY_ASM(battle, jpt_800B66C4);

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
            dword_800C9C88.kind_0 = 3;
            dword_800C9C88.arg_4 = 0;
            dword_800C9C88.mask_8 = 1;
            dword_800C9C88.targets_C = 0;
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
            dword_800C9C88.kind_0 = 3;
            dword_800C9C88.arg_4 = 0;
            dword_800C9C88.mask_8 = 0x10;
            dword_800C9C88.targets_C = 0;
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
            dword_800C9C88.kind_0 = 3;
            dword_800C9C88.arg_4 = 0;
            dword_800C9C88.targets_C = 0;
            dword_800C9C88.mask_8 = 1 << dword_800C9C7C;
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
    dword_800C9C88.kind_0 = r;
    dword_800C9C88.arg_4 = 0;
    dword_800C9C88.targets_C = 0;
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
        dword_800C9C88.kind_0 = 0xB;
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
    if (dword_800C9C88.kind_0 == 0x14)
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
    dword_800C9C88.kind_0 = 0x14;
    dword_800C9C88.arg_4 = 0;
    dword_800C9C88.targets_C = 0;
    dword_800C9C88.mask_8 = 1 << dword_800C9C7C;
    sub_800BB794();
}

void sub_800BB794()
{
    int i;
    for (i = 0; i < 7; i++)
    {
        dword_800C9CC8[i].kind_0 = 0x14;
        dword_800C9CC8[i].arg_4 = 0;
        dword_800C9CC8[i].mask_8 = 1 << i;
        dword_800C9CC8[i].targets_C = 0;
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
            sub_800B42A8(&dword_800C9C88, &dword_800ADE78);
        }
        else
        {
            sub_800A2618(&dword_800C9C88, dword_800C9C7C - 4);
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
            if (((&dword_800ADE78)[4] = sub_800B4318(&dword_800C9C88, &dword_800ADE78)) >= 0)
            {
                sub_800BC838(0x2000);
                t->next_8 = sub_800BAE74;
                return;
            }
        }
        t->next_8 = (void (*)())sub_800BC174();
        u->f4 = (int)sub_800BAE74;
        if (dword_800C9C88.kind_0 == 2)
        {
            dword_800B122C |= dword_800C9C88.targets_C;
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
    BatCmd_a* s;
    if (sub_800BC1A8(dword_800C9C88.targets_C) == 1)
    {
        mask = dword_800C9C88.targets_C;
        sub_800BC838(0x1000);
        sub_800BB74C();
        sub_800BB7D4();
        s = dword_800C9CC8;
        for (i = 0; i < 7; i++)
        {
            if (mask & (1 << i))
            {
                int f = *(int*)sub_80014390(i & 0xFF);
                if (f & 0x200)
                {
                    s[i].kind_0 = 0x13;
                }
                else if (f & 0x10000)
                {
                    s[i].kind_0 = 0xE;
                }
                else if (f & 2)
                {
                    s[i].kind_0 = 0x10;
                }
                else if (f & 0x8000)
                {
                    s[i].kind_0 = 0x12;
                }
                s[i].arg_4 = 0;
                s[i].mask_8 = 1 << i;
                s[i].targets_C = 0;
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

#if 0 // Not matched: the lbu of dword_800C9C98 is scheduled above the store to dword_800C9C88.targets_C (original keeps source order); tried early return, pointer local, swapped branches
void sub_800BBBF4(BatTask_a* t, BatObj_a* u)
{
    dword_800C9C88.kind_0 = 3;
    dword_800C9C88.targets_C = 0;
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
    sub_800C0AEC(dword_800C9C98 - 1, levantPos_8008BD18.pos_0, levantPos_8008BD18.angle_E);
}

#if 0 // Not matched: needs the second copy of u (s3, from 'v'); remaining: u->fc store / dword_800ADE78 load order and the shared lui of sub_800BAE74 in the branch delay slot
extern int sub_800C0BF0();
extern void sub_800C0F1C();
void sub_800BBCC8(BatTask_a* t, BatObj_a* u)
{
    BatObj_a* v = u;
    if (sub_800C0BF0(t) == 1)
    {
        dword_800C9C88.kind_0 = 2;
        dword_800C9C88.targets_C = 0;
        dword_800C9C99 = dword_800C9C98;
        dword_800C9C7C = dword_800C9C98;
        dword_800C9C82 = dword_800C9C98;
        dword_800C9C88.mask_8 = 1 << dword_800C9C98;
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
    dword_800C9C88.mask_8 = 1 << dword_800C9C98;
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
    dword_800C9C88.targets_C = 0;
    dword_800C9C98 = dword_800C9C88.arg_4 + 4;
    t->next_8 = sub_800BC144;
}

#if 0 // Not matched: instruction scheduling only (s0/s1 save order, C68 address placement); tried assignment-expression, pointer local, byte temp
void sub_800BBF64(BatTask_a* t, BatObj_a* u)
{
    dword_800C9C88.kind_0 = 0x15;
    dword_800C9C7C = dword_800C9C98;
    dword_800C9C88.mask_8 = 1 << dword_800C9C7C;
    sub_800A2AE8(&dword_800C9C88);
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
    dword_800C9C98 = dword_800C9C88.arg_4 + 4;
    t->next_8 = sub_800BC144;
}

#if 0
void sub_800BC05C(BatTask_a* t, BatObj_a* u)
{
    dword_800C9C88.kind_0 = 0x16;
    dword_800C9C7C = dword_800C9C98;
    dword_800C9C88.mask_8 = 1 << dword_800C9C98;
    sub_800A2AE8(&dword_800C9C88);
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
    return dword_800C8B54[(unsigned char)dword_800C8B38[dword_800C9C88.kind_0]];
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
                r = (int)levantPos_8008BD18.pos_0;
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
