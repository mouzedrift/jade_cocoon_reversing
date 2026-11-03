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
#include "actor.h"
#include "unit.h"

INCLUDE_DATA(dword_80072310);
INCLUDE_DATA(dword_80072324);
INCLUDE_DATA(dword_80072354);
INCLUDE_DATA(dword_80072380);
INCLUDE_DATA(dword_800723AC);
INCLUDE_DATA(dword_800723FC);
INCLUDE_DATA(dword_80072410);
INCLUDE_DATA(dword_80072420);
INCLUDE_DATA(dword_80072440);
INCLUDE_DATA(dword_80072454);
INCLUDE_DATA(dword_80072464);
INCLUDE_DATA(dword_800724C4);
INCLUDE_DATA(dword_800724D4);
INCLUDE_DATA(dword_80072518);
INCLUDE_DATA(dword_80072534);
INCLUDE_DATA(dword_80072548);
INCLUDE_DATA(dword_80072558);
INCLUDE_DATA(dword_8007256C);
INCLUDE_DATA(dword_80072578);
INCLUDE_DATA(dword_80072584);
INCLUDE_DATA(dword_800725AC);
INCLUDE_DATA(dword_800725BC);
INCLUDE_DATA(dword_800725C8);
INCLUDE_DATA(dword_800725D4);
INCLUDE_DATA(dword_800725E0);
INCLUDE_DATA(dword_80072620);
INCLUDE_DATA(dword_80072640);
INCLUDE_DATA(dword_8007268C);
INCLUDE_DATA(dword_800726A4);
INCLUDE_DATA(dword_800726B8);
INCLUDE_DATA(dword_800726C8);
INCLUDE_DATA(dword_800726F8);
INCLUDE_DATA(dword_8007270C);
INCLUDE_DATA(dword_80072740);
INCLUDE_DATA(dword_80072764);
INCLUDE_DATA(dword_80072774);
INCLUDE_DATA(dword_80072794);
INCLUDE_DATA(dword_800727B8);
INCLUDE_DATA(dword_800727CC);
INCLUDE_DATA(dword_800727F0);
INCLUDE_DATA(dword_80072804);
INCLUDE_DATA(dword_80072818);
INCLUDE_DATA(dword_8007282C);
INCLUDE_DATA(dword_8007284C);
INCLUDE_DATA(dword_8007285C);
INCLUDE_DATA(dword_8007286C);
INCLUDE_DATA(dword_8007287C);
INCLUDE_DATA(dword_800728C0);
INCLUDE_DATA(dword_800728D4);
INCLUDE_DATA(dword_800728E8);
INCLUDE_DATA(dword_800728FC);
INCLUDE_DATA(dword_80072910);
INCLUDE_DATA(dword_80072954);
INCLUDE_DATA(dword_80072964);
INCLUDE_DATA(dword_800729A8);
INCLUDE_DATA(dword_800729BC);
INCLUDE_DATA(dword_80072A10);
INCLUDE_DATA(dword_80072A64);
INCLUDE_DATA(dword_80072AA8);
INCLUDE_DATA(dword_80072AC8);
INCLUDE_DATA(dword_80072AE4);
INCLUDE_DATA(dword_80072AF8);
INCLUDE_DATA(dword_80072B0C);
INCLUDE_DATA(dword_80072B20);
INCLUDE_DATA(dword_80072B34);
INCLUDE_DATA(dword_80072B68);
INCLUDE_DATA(dword_80072B78);
INCLUDE_DATA(dword_80072BA8);
INCLUDE_DATA(dword_80072BBC);
INCLUDE_DATA(dword_80072BCC);
INCLUDE_DATA(dword_80072BF0);
INCLUDE_DATA(dword_80072C04);
INCLUDE_DATA(dword_80072C18);
INCLUDE_DATA(dword_80072C2C);
INCLUDE_DATA(dword_80072C50);
INCLUDE_DATA(dword_80072C78);
INCLUDE_DATA(dword_80072C9C);
INCLUDE_DATA(dword_80072CB0);
INCLUDE_DATA(dword_80072CC8);
INCLUDE_DATA(dword_80072CD8);
INCLUDE_DATA(dword_80072CE8);
INCLUDE_DATA(dword_80072CF4);
INCLUDE_DATA(dword_80072D1C);
INCLUDE_DATA(dword_80072D54);
INCLUDE_DATA(dword_80072D90);
INCLUDE_DATA(dword_80072DA4);
INCLUDE_DATA(dword_80072DB4);
INCLUDE_DATA(dword_80072DEC);
INCLUDE_DATA(dword_80072E28);
INCLUDE_DATA(dword_80072E38);
INCLUDE_DATA(dword_80072E64);
INCLUDE_DATA(dword_80072EA8);
INCLUDE_DATA(dword_80072EC4);
INCLUDE_DATA(dword_80072EE4);
INCLUDE_DATA(dword_80072EF4);
INCLUDE_DATA(dword_80072F18);
INCLUDE_DATA(dword_80072F2C);
INCLUDE_DATA(dword_80072F40);
INCLUDE_DATA(dword_80072F64);
INCLUDE_DATA(dword_80072F88);
INCLUDE_DATA(dword_80072FAC);
INCLUDE_DATA(dword_80072FC0);
INCLUDE_DATA(dword_80072FD4);
INCLUDE_DATA(dword_80072FE8);
INCLUDE_DATA(dword_80073008);
INCLUDE_DATA(dword_80073028);
INCLUDE_DATA(dword_8007303C);
INCLUDE_DATA(dword_80073040); // kept here so tu_80019BF0's .rdata starts at 4 mod 8 (its switch tables use .align 3)

// Matched
int sub_80018E5C(Actor* a0, unsigned int a1)
{
    struct_4s* t = (struct_4s*)a0->hitTimes_108;
    int v = 0;
    switch (a1)
    {
    case 0:
    case 1:
    case 2:
    case 3:
    case 4:
    case 5:
    case 6:
    case 7:
    case 8:
    case 9:
        v = t[a1].field_0;
        break;
    case 10:
        v = sub_8001F03C((int)a0, (int)a0->script_D0, -1, 0x10);
        break;
    }
    return v;
}
// Matched
void sub_80018EBC(int a0, unsigned int* a1)
{
    unsigned int f = *a1;
    int* r = 0;
    if (f & 0x200)
    {
        r = (f & 1) ? dword_8007A14C : dword_8007A0EC;
    }
    else if (f & 0x100)
    {
        r = (f & 1) ? dword_8007A140 : dword_8007A0E0;
    }
    else if (f & 0x80)
    {
        r = (f & 1) ? dword_8007A134 : dword_8007A0D4;
    }
    else if (f & 0x40)
    {
        r = (f & 1) ? dword_8007A128 : dword_8007A0C8;
    }
    else if (f & 0x20)
    {
        r = (f & 1) ? dword_8007A11C : dword_8007A0BC;
    }
    else if (f & 0x10)
    {
        r = (f & 1) ? dword_8007A110 : dword_8007A0B0;
    }
    else if (f & 0x8)
    {
        r = (f & 1) ? sub_8007A104 : dword_8007A0A4;
    }
    else if (f & 1)
    {
        r = dword_8007A0F8;
    }
    SetActorTint_8001DAAC(a0, r);
}
extern void* minionSpeciesNames_8007A170[];
extern unsigned char dword_8007BA84[];
extern unsigned char dword_8007BA74[];
extern int dword_8007A67C[];
extern int dword_8007A68C[];
extern int dword_8007A69C[];
extern MinionBaseStats* sub_800B32A4(int a0);
extern unsigned char* sub_800B32F0(int a0);
extern void EncodeName_8003F7C8(void* a0, unsigned char* a1);
extern void sub_8001980C(unsigned char* p, MinionBaseStats* s);
extern void sub_800199A0(UnitStats* p);
extern void sub_80019A20(UnitStats* a0);
// Matched
void InitMinionData_8001900C(UnitStats* m, int* a1)
{
    MinionBaseStats st;
    void** name;
    int r;
    unsigned int id;
    unsigned int id2;
    int e;
    int i;
    int j;
    int k;
    int l;
    int n;
    int v;

    n = a1[0];
    m->species_5C = n;
    name = &minionSpeciesNames_8007A170[n];
    r = dword_8008D4DC;
    EncodeName_8003F7C8(*name, m->name_10);
    EncodeName_8003F7C8(*name, m->name_60);
    id = m->species_5C;
    if (id < 0x39)
    {
        st = minionBaseStats_8007A4B4[id];
        if (m->species_5C - 0x25 < 4)
        {
            st.attack += (r % 5) * 10 - 20;
            st.magicAttack += (r / 10 % 5) * 10 - 20;
            st.defense += (r / 100 % 5) * 10 - 20;
            st.magicDefense += (r / 1000 % 5) * 10 - 20;
            st.speed += (r / 10000 % 5) * 10 - 20;
            st.critical += (r / 100000 % 5) * 10 - 20;
        }
    }
    else if (id < 0xC9)
    {
        id = (id - 0x39) / 4;
        st = minionBaseStats_8007A4B4[id];
        e = (m->species_5C - 0x39) & 3;
        if (st.element != e)
        {
            st.element = e;
            switch (e)
            {
            case 0:
                st.attack += 10;
                st.magicAttack += 10;
                st.defense -= 10;
                st.magicDefense -= 10;
                break;
            case 1:
                st.defense -= 10;
                st.magicDefense -= 10;
                st.speed += 10;
                st.critical += 10;
                break;
            case 2:
                st.defense += 10;
                st.magicDefense += 10;
                st.speed -= 10;
                st.critical -= 10;
                break;
            case 3:
                st.attack -= 10;
                st.magicAttack += 10;
                st.defense -= 10;
                st.magicDefense += 10;
                break;
            }
        }
    }
    else
    {
        st = *sub_800B32A4(id - 0xC9);
    }
    sub_8001980C(m->stats_2C, &st);
    m->status_0 = 0;
    if (st.element != -1)
    {
        m->elementMask_42 = 1 << st.element;
        for (j = 0; j < 4; j++)
        {
            m->element_3E[j] = 0;
        }
        m->element_3E[st.element] = 0x20;
    }
    else
    {
        m->elementMask_42 = 0;
        for (l = 0; l < 4; l++)
        {
            m->element_3E[l] = 8;
        }
    }
    m->exp_4 = 0x4000000;
    m->level_44 = 0;
    m->field_1C[0] = 0xFF;
    m->field_1C[1] = 0xFF;
    m->field_1C[2] = 0xFF;
    m->field_1C[3] = 0xFF;
    m->field_45 = 0;
    id2 = m->species_5C;
    if (id2 < 0x39)
    {
        MemCopy_800403E8((unsigned int*)m->field_20, (unsigned int*)(dword_8007BA84 + id2 * 12), 12);
    }
    else if (id2 < 0xC9)
    {
        id2 = (id2 - 0x39) / 4;
        MemCopy_800403E8((unsigned int*)m->field_20, (unsigned int*)(dword_8007BA84 + id2 * 12), 12);
    }
    else
    {
        MemCopy_800403E8((unsigned int*)m->field_20, (unsigned int*)sub_800B32F0(id2 - 0xC9), 12);
    }
    if (m->species_5C - 0x25 < 4)
    {
        v = r;
        for (i = 4; i < 9; i++)
        {
            m->field_20[i] = (v % 9) * 4 + 8;
            v /= 10;
        }
    }
    if (st.element != -1)
    {
        id2 = m->species_5C;
        if (!(id2 - 0x2B < 0xE) && !(id2 - 0xC9 < 0xA))
        {
            MemCopy_800403E8((unsigned int*)m->field_20, (unsigned int*)(dword_8007BA74 + st.element * 4), 4);
        }
    }
    m->exp_4 += a1[1];
    sub_80012188(m);
    FillHpMp_80011C0C((EntityStatus*)m, (EntityStatus*)m);
    sub_800199A0(m);
    if (m->species_5C - 0x25 < 4)
    {
        m->skills_6C.e[r % 4][3] = 1;
        m->skills_6C.e[r % 4][2] = r % 3 + 2;
        k = r % 3 + 1;
        m->skills_6C.e[k][1] = r % 10 + 6;
        m->skills_6C.field_10[1] = 12;
    }
    sub_80019A20(m);
    if (m->species_5C - 0x25 < 4)
    {
        if (r / 11 % 3)
        {
            m->field_80 |= dword_8007A67C[st.element];
        }
        if (r / 70 & 1)
        {
            m->field_80 |= dword_8007A68C[st.element];
        }
        if (r / 500 & 1)
        {
            m->field_80 |= dword_8007A69C[st.element];
        }
    }
    sub_80019A80(*(char*)&m->level_44);
}
// Matched
void sub_8001980C(unsigned char* p, MinionBaseStats* s)
{
    int i;
    int j;
    int v;
    p[6] = (s->attack < 200) ? s->attack : 200;
    p[8] = (s->magicAttack < 200) ? s->magicAttack : 200;
    p[10] = (s->speed < 200) ? s->speed : 200;
    p[7] = (s->defense < 200) ? s->defense : 200;
    p[9] = (s->magicDefense < 200) ? s->magicDefense : 200;
    p[11] = (s->critical < 200) ? s->critical : 200;
    for (i = 0; i < 6; i++)
    {
        int r;
        unsigned char* q = p + i;
        v = (unsigned char)(q[6] / 10) + 10;
        if (v >= 0)
        {
            int t = v;
            if (t > 100)
            {
                t = 100;
            }
            r = t;
        }
        else
        {
            r = 0;
        }
        q[0] = r;
    }
    for (j = 0; j < 6; j++)
    {
        (p + j)[12] = rand() % 100;
    }
}
// Matched
void sub_800199A0(UnitStats* p)
{
    p->skills_6C = *(UnitSkills*)sub_80019C28(p->species_5C);
}
// Matched
void sub_80019A20(UnitStats* a0)
{
    unsigned int idx = a0->species_5C;
    if (idx < 0xC9)
    {
        a0->field_80 = dword_8007A6AC[idx];
    }
    else
    {
        a0->field_80 = *sub_800B3260(idx - 0x39);
    }
}
extern unsigned char dword_8007C2E4[];
// Matched
int sub_80019A80(int a0)
{
    int i;
    for (i = 0; i < 5; i++)
    {
        if (a0 < dword_8007C2E4[i])
        {
            break;
        }
    }
    i--;
    if (i == 5)
    {
        return 4;
    }
    return i;
}
// Matched
int sub_80019AD0(char* p)
{
    sub_80019A80(((UnitStats*)p)->level_44);
    return 4;
}
// Matched
void sub_80019AF4(unsigned int* arg0, unsigned int* arg1)
{
    MemCopy_800403E8(arg0, arg1, 12);
}
// Matched
void sub_80019B14(short* p, unsigned short* a1, unsigned short* a2)
{
    struct_int3 masks;
    int k;
    int i;
    masks = dword_8007303C;
    for (k = 0; k < 3; k++)
    {
        int set = 0;
        int clr = 0;
        if (a1[k] < 2)
        {
            clr = masks.m[k];
        }
        if (a2[k] == 0)
        {
            set = masks.m[k];
        }
        for (i = 0; i < 25; i++)
        {
            int bit = 1 << i;
            if (clr & bit)
            {
                p[i * 4 + 3] &= ~2;
            }
            if (set & bit)
            {
                p[i * 4 + 3] |= 0x10;
            }
        }
    }
}
