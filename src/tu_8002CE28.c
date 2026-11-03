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
#include "minion_menu.h"


typedef struct
{
    unsigned short flags;
    short pad_2;
    int f4;
    int f8;
    int fC;
    short x;
    short y;
    char pad_14[8];
} MenuItem_1C;
typedef struct
{
    int field_0;
    int field_4;
    int field_8;
    int field_C;
    MenuItem_1C** field_10;
    int field_14;
} struct_A5A4;
extern void DrawMenuWindows_8002A5A4(struct_A5A4* p);
extern int sub_80033C98(struct_minion_ref* p);
int sub_8002D1A4(int a, short b);
extern int abilityNames_800834E4[];
extern int abilityBonusNames_80083580[];
extern MenuItem_1C* off_80082D98[];
// Matched
void sub_8002CE28(struct_minion_ref* a0, unsigned short* a1)
{
    struct_A5A4 s;
    unsigned short pos[2];
    short saved;
    short w;
    short i;
    int v20;
    int v19;
    unsigned char* m;
    MenuItem_1C** e;
    MenuItem_1C** e2;
    int y;
    saved = a0->field_0;
    w = 8;
    if (a1)
    {
        pos[0] = a1[0];
        pos[1] = a1[1];
    }
    else
    {
        pos[0] = 0x38;
        pos[1] = 0x2C;
    }
    for (i = 0; i < 5; i++)
    {
        v20 = abilityNames_800834E4[0];
        v19 = abilityBonusNames_80083580[0];
        m = (unsigned char*)a0->field_C_minion + i * 4;
        if (m[0xDE] & 1)
        {
            if (m[0xDF])
            {
                v20 = abilityNames_800834E4[m[0xDF]];
            }
            if (m[0xE0])
            {
                v19 = abilityBonusNames_80083580[m[0xE0]];
            }
            e = &off_80082D98[i];
            (*e)[0].flags &= ~2;
            (*e)[1].flags &= ~2;
            (*e)[2].flags &= ~2;
            a0->field_0 = i;
            if ((short)sub_80033C98(a0))
            {
                (*e)[0].flags |= 2;
                (*e)[1].flags |= 2;
                (*e)[2].flags |= 2;
            }
            else
            {
                (*e)[0].flags &= ~2;
                (*e)[1].flags &= ~2;
                (*e)[2].flags &= ~2;
            }
        }
        else
        {
            off_80082D98[i][0].flags |= 2;
            off_80082D98[i][1].flags |= 2;
            off_80082D98[i][2].flags |= 2;
        }
        y = sub_8002D1A4(((unsigned char*)sub_800318C8(((unsigned char*)a0->field_C_minion + (i << 2))[0xDF]))[8], i);
        e2 = &off_80082D98[i];
        (*e2)[0].f4 = y;
        (*e2)[1].f4 = v20;
        (*e2)[2].f4 = v19;
        (*e2)[0].f8 = (int)&uiTiySprts_8008D620;
        (*e2)[0].fC = (int)&uiTiyTPages_8008D3F4;
        (*e2)[0].x = pos[0];
        y = i * 22;
        (*e2)[0].y = pos[1] + y;
        (*e2)[1].x = pos[0] + 0x26;
        (*e2)[1].y = pos[1] + y;
        (*e2)[2].x = pos[0] + 0x83;
        (*e2)[2].y = pos[1] + y;
    }
    s.field_0 = a0->field_4;
    s.field_4 = frameCount_8008D3FC;
    s.field_8 = w;
    s.field_C = saved;
    s.field_10 = off_80082D98;
    s.field_14 = a0->field_6;
    DrawMenuWindows_8002A5A4(&s);
    SetFontClutOffset_8003F900(2, 0);
}
extern unsigned char dword_800827F0[];
extern unsigned char* off_8008280C[];
// Matched
int sub_8002D1A4(int a, short b)
{
    int r = 0;
    switch ((short)a)
    {
    case 0:
        break;
    default:
        r = 4;
        break;
    case 3:
        r = 1;
        break;
    case 1:
        r = 2;
        break;
    case 2:
        r = 3;
        break;
    }
    a = r;
    if (a >= 4)
    {
        return dword_800827F0[b];
    }
    return off_8008280C[b][a];
}
typedef struct
{
    unsigned short flags;
    unsigned short type;
    int text;
    int f8;
    int fC;
    short x;
    short y;
    short w;
    short h;
    short mx;
    short my;
} MenuItem_D250;
extern int sub_80033DF4(short* p);
extern int sub_80034068(short* p);
// Matched
int sub_8002D250(short* p, int mode, int sel, int ot)
{
    MenuItem_D250 list0[4] = {
        {8, 4, 0, 0, 0, 0x2E, 0x98, 0x3C, 0xC, 2, 2},
        {8, 0, 0, 0, 0, 0x26, 0x98, 6, 0xC, 2, 2},
        {8, 0, 0, 0, 0, 0x6C, 0x98, 6, 0xC, 2, 2},
        {1, 0, 0, 0, 0, -1, -1, -1, -1, -1, -1},
    };
    MenuItem_D250 list1[2] = {
        {8, 4, 0, 0, 0, 0x2E, 0xA6, 0x3C, 0xC, 2, 2},
        {1, 0, 0, 0, 0, -1, -1, -1, -1, -1, -1},
    };
    MenuItem_D250 list2[2] = {
        {8, 4, 0, 0, 0, 0x2E, 0xB3, 0x3C, 0xC, 2, 2},
        {1, 0, 0, 0, 0, -1, -1, -1, -1, -1, -1},
    };
    MenuItem_D250 list3[2] = {
        {8, 4, 0, 0, 0, 0x2E, 0xC0, 0x3C, 0xC, 2, 2},
        {1, 0, 0, 0, 0, -1, -1, -1, -1, -1, -1},
    };
    MenuItem_D250* lists[5] = {0};
    MenuItem_D250* subs[3] = {0};
    int k = 0;
    struct_A5A4 s = {2, 0, 8, 0, 0, 0};
    int n;
    int cur;
    int i;
    int r;
    int v;
    int q;
    int y;
    MenuItem_D250* m;
    n = CountMinions_80010548(3);
    cur = sub_8002D780();
    s.field_4 = GetTime30Hz_8002C64C();
    s.field_C = sel;
    s.field_10 = (MenuItem_1C**)lists;
    s.field_14 = ot;
    subs[0] = list1;
    subs[1] = list2;
    subs[2] = list3;
    if (mode == 0 || mode == 3)
    {
        q = sub_80014390(0);
        lists[k] = list0;
        lists[k][0].text = q + 0x10;
        p[2] = 0;
        if (mode == 0)
        {
            v = sub_80033DF4(p);
        }
        else
        {
            v = 0;
        }
        if (v == 0 || v == 1)
        {
            lists[k][0].flags &= ~2;
            lists[k][1].flags &= ~2;
            lists[k][2].flags &= ~2;
        }
        else
        {
            lists[k][0].flags |= 2;
            lists[k][1].flags |= 2;
            lists[k][2].flags |= 2;
        }
        k++;
    }
    y = 0;
    for (i = 0; i < n; i++)
    {
        r = sub_8002D738(i, p[1], mode);
        if (r == 1)
        {
            p[2] = i + 1;
            q = sub_80014390(((unsigned char*)p)[4]);
            v = 0;
            m = subs[i];
            lists[k] = m;
            m->text = q + 0x10;
            lists[k]->y = 0xA6 + y * 13;
            if (mode == 0)
            {
                v = sub_80033DF4(p);
            }
            else if (mode == 1)
            {
                v = sub_80034068(p);
            }
            else if ((unsigned int)(mode - 2) < 2)
            {
                if (sub_80033548((int*)q, 0x400))
                {
                    v = 4;
                }
            }
            if (v == 0 || v == 2)
            {
                lists[k]->flags &= ~2;
            }
            else
            {
                lists[k]->flags |= 2;
            }
            k++;
            y++;
        }
    }
    DrawMenuWindows_8002A5A4(&s);
    SetFontClutOffset_8003F900(1, 0);
    switch (mode)
    {
    case 0:
        if (sel < 0)
        {
            return cur | 1;
        }
        return sel;
    case 1:
        return p[1];
    case 2:
        return sel + 1;
    case 3:
        if (sel < 0)
        {
            return (cur | 1) & ~(1 << p[1]);
        }
        if (sel < p[1])
        {
            return sel;
        }
        return sel + 1;
    }
    return 0;
}
