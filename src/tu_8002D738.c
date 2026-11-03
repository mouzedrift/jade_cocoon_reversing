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

INCLUDE_DATA(dword_80074320);
INCLUDE_DATA(dword_80074360);
INCLUDE_DATA(dword_80074374);
INCLUDE_DATA(dword_80074380);
INCLUDE_DATA(dword_80074398);
INCLUDE_DATA(dword_800743B4);
INCLUDE_DATA(dword_800743CC);

// Matched
int sub_8002D738(int a0, int a1, int a2)
{
    if (a2 == 0 || a2 == 2)
    {
        return 1;
    }
    if (a2 == 3 && a0 + 1 != a1)
    {
        return 1;
    }
    if (a2 == 1 && a0 + 1 == a1)
    {
        return 1;
    }
    return 0;
}
// Matched
int sub_8002D780(void)
{
    int n = CountMinions_80010548(3);
    int i;
    int mask = 0;
    for (i = 0; i < n; i++)
    {
        mask |= 1 << (i + 1);
    }
    return mask;
}
typedef struct
{
    unsigned short x;
    unsigned short y;
} Pos16;
typedef struct
{
    int rect;
    int time;
    short field_8;
    short ot;
} struct_D7D0;
extern CVECTOR dword_800743CC;
extern Pos16* off_80082DCC[7];
extern Pos16 aHroto[12];
extern Pos16 aNrutu[12];
extern void sub_80033864(Minion* m, unsigned char* out);
extern short sub_8002F424(unsigned char* p);
extern void sub_8002FAA0(int a0, unsigned short* pos, unsigned char* name, int a3);
extern void sub_8002B1B0(short a, int b, int c);
extern void DrawUiWindow_8002A384(struct_D7D0* p);
extern void DrawLine_80042870(DVECTOR* a, DVECTOR* b, unsigned char* rgb, void* ot);
#if 0
// Not matched (4 words): writing pos.y through pp once gets the m/pp/table saved registers right (19 words with pos.y),
// but that store then goes through $s4 instead of $sp; the (short)w sll goes to a0 instead of v0 (int / u_short /
// u_char w, ternary: no)
void sub_8002D7D0(Minion* m, int ot, Pos16* base)
{
    RECT rect;
    Pos16 pos;
    Pos16 p1;
    Pos16 p2;
    CVECTOR color;
    unsigned char buf[4];
    struct_D7D0 s;
    unsigned char* name;
    Pos16* pp;
    short w;
    int i;
    int k;
    color = dword_800743CC;
    pp = &pos;
    for (i = 0; i < 7; i++)
    {
        pos.x = off_80082DCC[i]->x + base->x;
        pos.y = off_80082DCC[i]->y + base->y;
        rect.x = pos.x;
        rect.y = pos.y;
        rect.w = 0x40;
        rect.h = 0xF;
        if (i == 0)
        {
            name = m->status_84.name_10;
        }
        else
        {
            name = sub_80033830(m, i - 1);
        }
        pos.x = off_80082DCC[i]->x + base->x + 3;
        pp->y = off_80082DCC[i]->y + base->y + 4;
        sub_8002FAA0(0, (unsigned short*)pp, name, ot);
        pos.x = (unsigned short)(base->x + 4) + off_80082DCC[i]->x;
        pos.y = (unsigned short)(base->y + 0x10) + off_80082DCC[i]->y;
        if (i == 0)
        {
            sub_80033864(m, buf);
            w = sub_8002F424(buf);
        }
        else
        {
            w = sub_80033848(m, i - 1);

        }
        sub_8002B1B0(w, (int)pp, ot);
        s.field_8 = 0;
        s.rect = (int)&rect;
        s.ot = ot;
        s.time = frameCount_8008D3FC;
        DrawUiWindow_8002A384(&s);
    }
    for (k = 0; k < 12; k++)
    {
        p1.x = aHroto[k].x + base->x;
        p1.y = aHroto[k].y + base->y;
        p2.x = aNrutu[k].x + base->x;
        p2.y = aNrutu[k].y + base->y;
        DrawLine_80042870((DVECTOR*)&p1, (DVECTOR*)&p2, (unsigned char*)&color, &pOT_8008D454[ot]);
    }
}
#endif
INCLUDE_ASM(sub_8002D7D0);
