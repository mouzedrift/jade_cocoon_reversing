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

extern short* dword_8008D434;

INCLUDE_DATA(aDWorkPsusEvent);
extern char aDWorkPsusEvent[];
#define malloc3_dbg ((void* (*)(int, const char*, int))malloc3_8003FC4C)
#define free3_dbg ((void (*)(void*, const char*, int))free3_8003FC6C)

extern short uiColor_8008B590;
extern void sub_8004226C(int a, RECT* r, int c, int d);
extern void sub_80041ED0(int a, RECT* r, int c, int d);

INCLUDE_ASM(sub_8004226C);
// Matched
void sub_80042460(int a0, unsigned char* p, int a2, int a3)
{
    RECT r;
    sub_8004226C(p[2], &r, a3, *(short*)p);
    sub_80041ED0(a0, &r, a2, p[3]);
}
// Matched
void sub_800424C0(int a0, short a1, int a2, int a3)
{
    RECT r;
    sub_8004226C(a1, &r, a3, uiColor_8008B590);
    sub_80041ED0(a0, &r, a2, 1);
}
INCLUDE_ASM(sub_8004251C);
INCLUDE_ASM(sub_80042750);
INCLUDE_ASM(sub_80042870);
// Matched
int sub_800429A8(short* p)
{
    short* g = dword_8008D434;
    if (p[2] >= g[0x63C / 2] + g[0x678 / 2] && p[3] >= g[0x63E / 2] + g[0x67A / 2])
    {
        return 1;
    }
    return 0;
}
#if 0
void sub_800429F8(int a0, int a1)
{
}
#endif
INCLUDE_ASM(sub_800429F8);
#if 0
void sub_80042B38(int a0, int a1)
{
}
#endif
INCLUDE_ASM(sub_80042B38);
extern int sub_8003C0A4(int a);
extern int sub_800434C4(int a);
extern int dword_80096108;
extern int dword_8009610C;
extern void sub_800430E8(void);
extern void sub_800432EC();

// Matched
void sub_80043054(struct_obj_D* p, int* q)
{
    SsSetSerialAttr(0, 0, 1);
    dword_80096118 = -1;
    q[0] = 0;
    ((short*)q)[4] = 0;
    p->field_8 = sub_800430E8;
}
// Matched
void sub_800430B0(void)
{
    SsSetSerialVol(0, 0, 0);
    DsControlB(9, 0, 0);
}
INCLUDE_ASM(sub_800430E8);
// Matched
void sub_800431C4(struct_obj_D* p, int* q)
{
    char buf[8];
    if (sub_80053B9C(q[1], buf) == 2)
    {
        p->field_8 = sub_80043204;
    }
}
// Matched
void sub_80043204(struct_obj_D* p, int* q)
{
    if (sub_800434C4(dword_80096108))
    {
        q[1] = DsControlF(0x11, 0);
        ((short*)q)[4] = 2;
        p->field_8 = sub_800432EC;
    }
}
// Matched
void sub_80043264(struct_obj_D* p, short* q)
{
    short v = q[5] - 14;
    q[5] = v;
    if (v < 0)
    {
        q[4] = 0;
        p->field_8 = sub_800430E8;
        SsSetSerialVol(0, 0, 0);
        DsControlB(9, 0, 0);
        sub_8003C0A4(0);
    }
    else
    {
        SsSetSerialVol(0, v, v);
    }
}
// Matched
void sub_800432EC(struct_obj_D* p, int* q)
{
    u_char result[8];
    DslLOC loc;
    if (sub_80053B9C(q[1], result) == 2 && q[1])
    {
        loc.minute = result[5];
        loc.second = result[6];
        loc.sector = result[7];
        if (DsPosToInt(&loc) > dword_8009610C || (int)dword_80096118 >= 0)
        {
            ((short*)q)[5] = 0x70;
            p->field_8 = sub_80043264;
            return;
        }
        SsSetSerialVol(0, 0x70, 0x70);
        q[1] = DsControlF(0x11, 0);
    }
    if (dword_8008D450 < -1000 || (q[0] & 1))
    {
        ((short*)q)[5] = 0x70;
        q[0] &= ~1;
        p->field_8 = sub_80043264;
    }
}
extern int sub_80053608(u_char com, u_char* param, DslCB cbsync, int count); /* DsCommand */
// Matched
void sub_800433FC(int* o)
{
    Data001File f;
    u_char result[8];
    u_char param[4];
    int r;
    DATA_GetFile_8003C7CC(&f, 0x439);
    param[0] = 1;
    param[1] = stru_80096110.field_2;
    do
    {
        r = sub_80053608(0xD, param, 0, -1);
        o[1] = r;
    } while (r == 0);
    dword_80096108 = DsPosToInt(&f.field_0_position);
    dword_80096108 += stru_80096110.field_4 * 32;
    dword_8009610C = dword_80096108 + stru_80096110.field_6 * 32;
    dword_8008D450 = stru_80096110.field_6 * 1920 / 150;
}
extern int sub_8005384C(u_char mode, DslLOC* pos, u_char com, DslCB func, int count); /* DsPacket */
// Matched
int sub_800434C4(int pos)
{
    DslLOC loc;
    int mode = 0xC9;
    int com = 0x1B;
    int r;
    DsIntToPos(pos, &loc);
    while ((r = sub_8005384C(mode, &loc, com, 0, -1)) == 0)
    {
    }
    return r;
}
// Matched
int sub_80043524(void)
{
    if ((int)dword_80096118 >= 0)
    {
        return 0;
    }
    dword_8008B560[0x24 / 4][0] |= 1;
    return 1;
}
// Matched
void sub_80043564(short a0, short a1, short a2)
{
    dword_80096118 = 0;
    stru_80096110.field_2 = a0;
    stru_80096110.field_4 = a1;
    stru_80096110.field_6 = a2;
}
// Matched
int sub_80043584(void)
{
    return ((short*)dword_8008B560[0x24 / 4])[4] == 0;
}
// Matched
unsigned int sub_800435A4(void)
{
    return dword_80096118 >> 31;
}
INCLUDE_ASM(sub_800435B4);
// Matched
void* sub_800437E8(int* a0, int size)
{
    void* p = malloc3_dbg(size, aDWorkPsusEvent, 0x2C);
    if (p == 0)
    {
        return 0;
    }
    a0[5] = (int)p;
    a0[4] = size;
    return p;
}
// Matched
int sub_80043840(int* a0)
{
    if (a0[5])
    {
        if (a0[1] == 0)
        {
            free3_dbg((void*)a0[5], aDWorkPsusEvent, 0x45);
        }
        a0[5] = 0;
        a0[4] = 0;
    }
    return 1;
}
// Matched
void sub_80043898(EventNode* n)
{
    do
    {
        if ((n->entry.flags & 0x8001) == 1)
        {
            n->entry.cb_8(&n->entry, n->entry.buffer);
        }
        n = n->next;
    } while (n);
}
// Matched
void sub_800438F8(EventNode* n)
{
    do
    {
        if ((n->entry.flags & 0x8004) == 4)
        {
            n->entry.cb_C(&n->entry, n->entry.buffer);
        }
        n = n->next;
    } while (n);
}
// Matched
void sub_80043958(EventNode* n)
{
    if (dword_8008B540 == 0)
    {
        do
        {
            if ((n->entry.flags & 0x8001) == 1)
            {
                n->entry.cb_8(&n->entry, n->entry.buffer);
            }
            n = n->next;
        } while (n && dword_8008B540 == 0);
    }
}
#if 0
// Not matched: gcc hoists out+0xc into a3
void sub_800439E0(unsigned int** arr, unsigned int* out)
{
    unsigned int* p;
    unsigned int i;
    out += 4;
    while (*arr)
    {
        p = *arr;
        for (i = 0; i < p[0]; i++)
        {
            out[2] = p[4];
            out[3] = p[5];
            out[0] = p[1];
        }
        arr++;
        out += 10;
    }
}
#endif
INCLUDE_ASM(sub_800439E0);
// Matched
int sub_80043A5C(EventNode* head)
{
    EventNode* n = head;
    do
    {
        EventEntry* e = &n->entry;
        if (e->buffer)
        {
            if (e->field_4 == 0)
            {
                free3_dbg(e->buffer, aDWorkPsusEvent, 0x45);
            }
            e->buffer = 0;
            e->size = 0;
        }
        n = n->next;
    } while (n);
    free3_dbg(head, aDWorkPsusEvent, 0x143);
    return 0;
}
