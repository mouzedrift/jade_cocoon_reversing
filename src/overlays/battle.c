// BATTLE.BIN
#include "common.h"
#include "funcs.h"
#include "globals.h"

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
extern int* dword_8008D4B0;
extern EventNode* dword_8008D63C;
extern EventNode* dword_8008D778;
extern int dword_800C9D74;
extern int dword_800C9D7C;
extern short word_8008D780;
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
extern char* dword_800C9190;
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
extern int sub_800A89F0(void*);
extern void sub_800BA624();
extern void sub_800BB894();
extern void sub_800BBCC8();
extern void sub_800BC144();
extern void sub_800BC850(unsigned int);
extern int sub_800BC28C();
extern void sub_800BE058();
extern void sub_800BFC10();
extern void sub_800BFC40();
extern void sub_800C01D8();
extern void sub_800C0440();
extern int sub_800C0BA0();
extern void sub_800C0AEC();
extern void sub_800BB794();
extern int sub_800C0F78(int);
extern void sub_8001C02C(void*);
extern void sub_8001DB00(char*, int, int);
extern void sub_80018E5C(char*, int);
extern void sub_80018EBC(char*, int);
extern void sub_8001E1DC(void*);

INCLUDE_OVERLAY_ASM(battle, dword_800B66C0);

INCLUDE_OVERLAY_ASM(battle, sub_800BA254);

INCLUDE_OVERLAY_ASM(battle, sub_800BA444);

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

INCLUDE_OVERLAY_ASM(battle, sub_800BA564);

INCLUDE_OVERLAY_ASM(battle, sub_800BA624);

INCLUDE_OVERLAY_ASM(battle, sub_800BA6A0);

INCLUDE_OVERLAY_ASM(battle, sub_800BA720);

INCLUDE_OVERLAY_ASM(battle, sub_800BA788);

INCLUDE_OVERLAY_ASM(battle, sub_800BA848);

INCLUDE_OVERLAY_ASM(battle, sub_800BA97C);

INCLUDE_OVERLAY_ASM(battle, sub_800BA9E4);

INCLUDE_OVERLAY_ASM(battle, sub_800BAAD8);

INCLUDE_OVERLAY_ASM(battle, sub_800BABC4);

INCLUDE_OVERLAY_ASM(battle, sub_800BAC4C);

INCLUDE_OVERLAY_ASM(battle, sub_800BAE10);

INCLUDE_OVERLAY_ASM(battle, sub_800BAE74);

INCLUDE_OVERLAY_ASM(battle, sub_800BB100);

INCLUDE_OVERLAY_ASM(battle, sub_800BB168);

INCLUDE_OVERLAY_ASM(battle, sub_800BB1B0);

INCLUDE_OVERLAY_ASM(battle, sub_800BB314);

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

INCLUDE_OVERLAY_ASM(battle, sub_800BB7D4);

void sub_800BB860(BatTask_a* t)
{
    sub_800BC850(0x80000);
    t->next_8 = sub_800BB894;
}

INCLUDE_OVERLAY_ASM(battle, sub_800BB894);

INCLUDE_OVERLAY_ASM(battle, sub_800BB940);

void sub_800BBA24(BatTask_a* t, BatObj_a* u)
{
    u->fc = sub_800BC28C(t);
    u->next_8 = sub_800BBA70;
    t->next_8 = sub_800BC144;
}

INCLUDE_OVERLAY_ASM(battle, sub_800BBA70);

void sub_800BBBA8(BatTask_a* t, BatObj_a* u)
{
    u->fc = sub_800BC28C(t);
    u->next_8 = sub_800BBCC8;
    t->next_8 = sub_800BC144;
}

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

INCLUDE_OVERLAY_ASM(battle, sub_800BBE00);

INCLUDE_OVERLAY_ASM(battle, sub_800BBE7C);

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

INCLUDE_OVERLAY_ASM(battle, sub_800BC1A8);

INCLUDE_OVERLAY_ASM(battle, sub_800BC28C);

void sub_800BC324(BatTask_a* t, int a)
{
    if (sub_8003BE30(dword_800C9D7C) == 0)
    {
        t->next_8 = sub_800BDA28;
        t->next_8(t, a);
    }
}

INCLUDE_OVERLAY_ASM(battle, sub_800BC378);

INCLUDE_OVERLAY_ASM(battle, sub_800BC468);

INCLUDE_OVERLAY_ASM(battle, sub_800BC4D4);

INCLUDE_OVERLAY_ASM(battle, sub_800BC570);

INCLUDE_OVERLAY_ASM(battle, sub_800BC5EC);

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

signed char sub_800BC868()
{
    return dword_800C9D84;
}

INCLUDE_OVERLAY_ASM(battle, sub_800BC878);

void sub_800BC8E8()
{
    sub_80020EBC(dword_80095468);
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

INCLUDE_OVERLAY_ASM(battle, sub_800BDBB0);

INCLUDE_OVERLAY_ASM(battle, sub_800BDC3C);

INCLUDE_OVERLAY_ASM(battle, sub_800BDD3C);

INCLUDE_OVERLAY_ASM(battle, sub_800BDE04);

INCLUDE_OVERLAY_ASM(battle, sub_800BDEBC);

void sub_800BDF74()
{
    sub_800BE058(dword_800C9D98, dword_800C9C88, 0, dword_800C9C7C);
}

INCLUDE_OVERLAY_ASM(battle, sub_800BDFAC);

INCLUDE_OVERLAY_ASM(battle, sub_800BE058);

INCLUDE_OVERLAY_ASM(battle, sub_800BE14C);

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
    word_8008D780 = 1;
    return 1;
}

INCLUDE_OVERLAY_ASM(battle, sub_800BEBB8);

INCLUDE_OVERLAY_ASM(battle, sub_800BF2E8);

void sub_800BF3AC()
{
    unsigned char buf[3];
    buf[0] = 0xFF;
    buf[1] = 0xFF;
    buf[2] = 0xFF;
    sub_8001C02C(buf);
}

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

INCLUDE_OVERLAY_ASM(battle, sub_800BF648);

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
    sub_80033624(buf, p);
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

INCLUDE_OVERLAY_ASM(battle, sub_800BF9B4);

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

INCLUDE_OVERLAY_ASM(battle, sub_800BFA4C);

INCLUDE_OVERLAY_ASM(battle, sub_800BFAF8);

void sub_800BFB80()
{
    sub_800BFC10();
    sub_800BFC40();
    sub_800C01D8();
    sub_800C0440();
}

void sub_800BFBB8()
{
    sub_80043B40(dword_8008B568);
    sub_80043B40(dword_8008B564);
    sub_80043B40(dword_8008D4B0);
    sub_80043B40((int*)dword_8008D63C);
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

INCLUDE_OVERLAY_ASM(battle, sub_800C01D8);

INCLUDE_OVERLAY_ASM(battle, sub_800C0254);

void sub_800C0440()
{
    EventEntry* e = sub_80043AF8(dword_8008D63C);
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

INCLUDE_OVERLAY_ASM(battle, sub_800C0904);

INCLUDE_OVERLAY_ASM(battle, sub_800C09D4);

void sub_800C0A94()
{
}

int sub_800C0A9C()
{
    int n = sub_80010548(3);
    int r = 0;
    int i;
    for (i = 0; i < n; i++)
    {
        r |= 1 << (i + 1);
    }
    return r;
}

INCLUDE_OVERLAY_ASM(battle, sub_800C0AEC);

int sub_800C0BA0()
{
    if (sub_800C0D50() >= 0)
    {
        sub_8001098C(0);
        sub_8001D600(dword_800C9190);
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

void sub_800C0D60()
{
    sub_8001E1C8((void*)dword_800C9190);
}

void sub_800C0D88()
{
    sub_8001E1DC(dword_800C9190);
}

void sub_800C0DB0(int a)
{
    sub_8001DB00(dword_800C9190, a, 0x55);
}

INCLUDE_OVERLAY_ASM(battle, sub_800C0DDC);

INCLUDE_OVERLAY_ASM(battle, sub_800C0E84);

void sub_800C0EE8(int a)
{
    sub_80018E5C(dword_800C9190, a);
}

int sub_800C0F14()
{
    return 0;
}

void sub_800C0F1C()
{
    sub_80018EBC(dword_800C9190, sub_800C0F78(dword_800C918C));
}

void sub_800C0F54(int a)
{
    sub_800106F8(3, a);
}

int sub_800C0F78(int a)
{
    sub_800107A0(3, a);
}

char* sub_800C0F9C()
{
    return dword_800C9190 + 0x38;
}

int sub_800C0FAC()
{
    return *(int*)(dword_800C9190 + 0x1C4);
}

INCLUDE_OVERLAY_ASM(battle, sub_800C0FC4);

INCLUDE_OVERLAY_ASM(battle, sub_800C100C);

INCLUDE_OVERLAY_ASM(battle, sub_800C103C);

INCLUDE_OVERLAY_ASM(battle, sub_800C106C);

INCLUDE_OVERLAY_ASM(battle, sub_800C10B8);

INCLUDE_OVERLAY_ASM(battle, sub_800C1140);

INCLUDE_OVERLAY_ASM(battle, sub_800C1190);

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

INCLUDE_OVERLAY_ASM(battle, sub_800C4090);

INCLUDE_OVERLAY_ASM(battle, sub_800C410C);

INCLUDE_OVERLAY_ASM(battle, sub_800C4118);

INCLUDE_OVERLAY_ASM(battle, sub_800C4328);

INCLUDE_OVERLAY_ASM(battle, sub_800C43D8);

INCLUDE_OVERLAY_ASM(battle, sub_800C4424);

INCLUDE_OVERLAY_ASM(battle, sub_800C4470);

INCLUDE_OVERLAY_ASM(battle, sub_800C4494);

INCLUDE_OVERLAY_ASM(battle, sub_800C44FC);

INCLUDE_OVERLAY_ASM(battle, sub_800C4548);

INCLUDE_OVERLAY_ASM(battle, sub_800C45A8);

INCLUDE_OVERLAY_ASM(battle, sub_800C46FC);

INCLUDE_OVERLAY_ASM(battle, sub_800C471C);

INCLUDE_OVERLAY_ASM(battle, sub_800C473C);

INCLUDE_OVERLAY_ASM(battle, sub_800C4A40);

INCLUDE_OVERLAY_ASM(battle, sub_800C4B34);

INCLUDE_OVERLAY_ASM(battle, sub_800C4BE4);

INCLUDE_OVERLAY_ASM(battle, sub_800C4C74);

INCLUDE_OVERLAY_ASM(battle, sub_800C4CBC);

INCLUDE_OVERLAY_ASM(battle, sub_800C4D38);

INCLUDE_OVERLAY_ASM(battle, sub_800C4DB8);

INCLUDE_OVERLAY_ASM(battle, sub_800C4E34);

INCLUDE_OVERLAY_ASM(battle, sub_800C4EA8);

INCLUDE_OVERLAY_ASM(battle, sub_800C4FA8);

INCLUDE_OVERLAY_ASM(battle, sub_800C4FE0);

INCLUDE_OVERLAY_ASM(battle, sub_800C5034);

INCLUDE_OVERLAY_ASM(battle, sub_800C507C);

INCLUDE_OVERLAY_ASM(battle, sub_800C50B0);

INCLUDE_OVERLAY_ASM(battle, sub_800C51D8);

INCLUDE_OVERLAY_ASM(battle, sub_800C5220);

INCLUDE_OVERLAY_ASM(battle, sub_800C5290);

INCLUDE_OVERLAY_ASM(battle, sub_800C5304);

INCLUDE_OVERLAY_ASM(battle, sub_800C53B0);

INCLUDE_OVERLAY_ASM(battle, sub_800C5424);

INCLUDE_OVERLAY_ASM(battle, sub_800C54A4);

INCLUDE_OVERLAY_ASM(battle, sub_800C5510);

INCLUDE_OVERLAY_ASM(battle, sub_800C5594);

INCLUDE_OVERLAY_ASM(battle, sub_800C5608);

INCLUDE_OVERLAY_ASM(battle, sub_800C5670);

INCLUDE_OVERLAY_ASM(battle, sub_800C56B8);

INCLUDE_OVERLAY_ASM(battle, sub_800C5700);

INCLUDE_OVERLAY_ASM(battle, sub_800C576C);

INCLUDE_OVERLAY_ASM(battle, sub_800C57D8);

INCLUDE_OVERLAY_ASM(battle, sub_800C580C);

INCLUDE_OVERLAY_ASM(battle, sub_800C5840);

INCLUDE_OVERLAY_ASM(battle, sub_800C5874);

INCLUDE_OVERLAY_ASM(battle, sub_800C58AC);

INCLUDE_OVERLAY_ASM(battle, sub_800C58BC);

INCLUDE_OVERLAY_ASM(battle, sub_800C59A0);

INCLUDE_OVERLAY_ASM(battle, sub_800C5A7C);

INCLUDE_OVERLAY_ASM(battle, sub_800C5BC0);

INCLUDE_OVERLAY_ASM(battle, sub_800C5D04);

INCLUDE_OVERLAY_ASM(battle, sub_800C5EB8);

INCLUDE_OVERLAY_ASM(battle, sub_800C6038);

INCLUDE_OVERLAY_ASM(battle, sub_800C61FC);

INCLUDE_OVERLAY_ASM(battle, sub_800C66B4);

INCLUDE_OVERLAY_ASM(battle, sub_800C66F4);

INCLUDE_OVERLAY_ASM(battle, sub_800C6824);

INCLUDE_OVERLAY_ASM(battle, sub_800C6928);

INCLUDE_OVERLAY_ASM(battle, sub_800C6A40);

INCLUDE_OVERLAY_ASM(battle, sub_800C6A68);

INCLUDE_OVERLAY_ASM(battle, sub_800C6A8C);

INCLUDE_OVERLAY_ASM(battle, sub_800C6AFC);

INCLUDE_OVERLAY_ASM(battle, sub_800C6B24);

INCLUDE_OVERLAY_ASM(battle, sub_800C6B50);

INCLUDE_OVERLAY_ASM(battle, sub_800C6BD0);

INCLUDE_OVERLAY_ASM(battle, sub_800C6C44);

INCLUDE_OVERLAY_ASM(battle, sub_800C6C58);

INCLUDE_OVERLAY_ASM(battle, sub_800C6C7C);

INCLUDE_OVERLAY_ASM(battle, sub_800C6CFC);

INCLUDE_OVERLAY_ASM(battle, sub_800C6D6C);

INCLUDE_OVERLAY_ASM(battle, sub_800C6DF8);

INCLUDE_OVERLAY_ASM(battle, sub_800C6EC8);

INCLUDE_OVERLAY_ASM(battle, sub_800C6EE4);

INCLUDE_OVERLAY_ASM(battle, sub_800C6EFC);

INCLUDE_OVERLAY_ASM(battle, sub_800C7088);

INCLUDE_OVERLAY_ASM(battle, sub_800C71A0);

INCLUDE_OVERLAY_ASM(battle, sub_800C71C8);

INCLUDE_OVERLAY_ASM(battle, sub_800C72B8);

INCLUDE_OVERLAY_ASM(battle, sub_800C7334);

INCLUDE_OVERLAY_ASM(battle, sub_800C73B8);

INCLUDE_OVERLAY_ASM(battle, sub_800C7424);

INCLUDE_OVERLAY_ASM(battle, sub_800C7530);

INCLUDE_OVERLAY_ASM(battle, sub_800C78D0);

INCLUDE_OVERLAY_ASM(battle, sub_800C791C);

INCLUDE_OVERLAY_ASM(battle, sub_800C79B8);

INCLUDE_OVERLAY_ASM(battle, sub_800C79EC);

INCLUDE_OVERLAY_ASM(battle, sub_800C7A1C);

INCLUDE_OVERLAY_ASM(battle, sub_800C7A6C);

INCLUDE_OVERLAY_ASM(battle, sub_800C7CE8);

INCLUDE_OVERLAY_ASM(battle, sub_800C7D54);

INCLUDE_OVERLAY_ASM(battle, sub_800C7DA8);

INCLUDE_OVERLAY_ASM(battle, sub_800C83B0);

INCLUDE_OVERLAY_ASM(battle, sub_800C8694);

INCLUDE_OVERLAY_ASM(battle, sub_800C8710);

INCLUDE_OVERLAY_ASM(battle, sub_800C8768);

INCLUDE_OVERLAY_ASM(battle, sub_800C8828);

INCLUDE_OVERLAY_ASM(battle, sub_800C88AC);

INCLUDE_OVERLAY_ASM(battle, sub_800C88E4);

INCLUDE_OVERLAY_ASM(battle, sub_800C8970);

INCLUDE_OVERLAY_ASM(battle, sub_800C8A08);

INCLUDE_OVERLAY_ASM(battle, dword_800C8B2C);
