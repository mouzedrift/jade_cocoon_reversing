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

extern unsigned char** off_80087064[];
extern unsigned char* off_80087050[];
extern int dword_80086FB0[][3];
extern void sub_80033394(unsigned char* out, unsigned char* c0, unsigned char* c1, unsigned int t, int period, int half);
// Matched
void sub_8004226C(int a, RECT* r, int c, int d)
{
    unsigned char* out = (unsigned char*)r;
    unsigned char c0[4];
    unsigned char c1[4];
    int cr;
    int cg;
    int cb;

    out[0] = off_80087064[(short)a][d][0];
    out[1] = off_80087064[(short)a][d][1];
    out[2] = off_80087064[(short)a][d][2];
    if ((short)a == 1)
    {
        cr = out[0] * dword_80086FB0[d][0] / 100;
        cg = out[1] * dword_80086FB0[d][1] / 100;
        cb = out[2] * dword_80086FB0[d][2] / 100;
        if (cr > 0xFF)
        {
            cr = 0xFF;
        }
        if (cg > 0xFF)
        {
            cg = 0xFF;
        }
        if (cb > 0xFF)
        {
            cb = 0xFF;
        }
        if (cr < 0)
        {
            cr = 0;
        }
        if (cg < 0)
        {
            cg = 0;
        }
        if (cb < 0)
        {
            cb = 0;
        }
        c0[0] = cr;
        c0[1] = cg;
        c0[2] = cb;
        c1[0] = off_80087050[d][0];
        c1[1] = off_80087050[d][1];
        c1[2] = off_80087050[d][2];
        sub_80033394(out, c0, c1, c, 40, 10);
    }
}
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
// Matched
void sub_8004251C(RECT* r, unsigned char (*rgb)[4], unsigned char abr, unsigned long* ot)
{
    POLY_G4 p;
    DR_TPAGE dt;

    SetPolyG4(&p);
    if (abr)
    {
        setSemiTrans(&p, 1);
    }
    setRGB0(&p, rgb[0][0], rgb[0][1], rgb[0][2]);
    setRGB1(&p, rgb[1][0], rgb[1][1], rgb[1][2]);
    setRGB2(&p, rgb[2][0], rgb[2][1], rgb[2][2]);
    setRGB3(&p, rgb[3][0], rgb[3][1], rgb[3][2]);
    setXY4(&p, r->x, r->y, r->x + r->w, r->y, r->x, r->y + r->h, r->x + r->w, r->y + r->h);
    AddPrimCopy_80040298(ot, &p, 9);
    if (abr)
    {
        SetDrawTPage(&dt, 0, 1, GetTPage(0, abr - 1, 0, 0));
        ((u_long*)primAllocPtr_800960A8[bDoubleBuffer_8008D428])[0] = dt.tag;
        ((u_long*)primAllocPtr_800960A8[bDoubleBuffer_8008D428])[1] = dt.code[0];
        addPrim(ot, primAllocPtr_800960A8[bDoubleBuffer_8008D428]);
        primAllocPtr_800960A8[bDoubleBuffer_8008D428] += 8;
    }
}
extern void sub_80042870(DVECTOR* a, DVECTOR* b, unsigned char* rgb, void* ot);
// Matched
void sub_80042750(RECT* r, unsigned char* rgb, void* ot)
{
    LINE_F4 l;
    DVECTOR a;
    DVECTOR b;
    setLineF4(&l);
    setRGB0(&l, rgb[0], rgb[1], rgb[2]);
    setXY4(&l, r->x, r->y, r->x + r->w, r->y, r->x + r->w, r->y + r->h, r->x, r->y + r->h);
    AddPrimCopy_80040298(ot, &l, 7);
    a.vx = l.x0;
    a.vy = l.y0;
    b.vx = l.x3;
    b.vy = l.y3;
    sub_80042870(&a, &b, rgb, ot);
}
// Matched
void sub_80042870(DVECTOR* a, DVECTOR* b, unsigned char* rgb, void* ot)
{
    LINE_F2 l;
    DR_TPAGE dt;
    setLineF2(&l);
    setRGB0(&l, rgb[0], rgb[1], rgb[2]);
    setXY2(&l, a->vx, a->vy, b->vx, b->vy);
    AddPrimCopy_80040298(ot, &l, 4);
    SetDrawTPage(&dt, 0, 1, GetTPage(0, 0, 0, 0));
    ((u_long*)primAllocPtr_800960A8[bDoubleBuffer_8008D428])[0] = dt.tag;
    ((u_long*)primAllocPtr_800960A8[bDoubleBuffer_8008D428])[1] = dt.code[0];
    addPrim(ot, primAllocPtr_800960A8[bDoubleBuffer_8008D428]);
    primAllocPtr_800960A8[bDoubleBuffer_8008D428] += 8;
}
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
extern unsigned char* off_80087028[];
// Matched
void sub_800429F8(int a0, int a1)
{
    short* p = (short*)a0;
    short* g = dword_8008D434;
    unsigned char rgb[4][4];
    RECT r;
    short i;

    if (p[2] >= g[0x63C / 2] + g[0x678 / 2] && p[3] >= g[0x63E / 2] + g[0x67A / 2])
    {
        r.x = p[0] + 3;
        r.y = p[1] + 2;
        r.w = p[2] - 6;
        r.h = p[3] - 4;
        for (i = 0; i < 4; i++)
        {
            rgb[i][0] = off_80087028[(short)saveData_8008B570.uiColor_20][0];
            rgb[i][1] = off_80087028[(short)saveData_8008B570.uiColor_20][1];
            rgb[i][2] = off_80087028[(short)saveData_8008B570.uiColor_20][2];
        }
        sub_8004251C(&r, rgb, 1, pOT_8008D454 + (short)a1);
    }
}
extern POLY_FT4* dword_8008D430;
extern DR_TPAGE* dword_8008D440;
#define EVT_SPRT ((SPRT*)dword_8008D434)
#if 0
// Not matched: register allocation (g/the sprite base gets $t7 instead of $s2, shifting the temporaries of the rect setup)
void sub_80042B38(int a0, int a1)
{
    short* p = (short*)a0;
    RECT r[8];

    if (p[2] >= EVT_SPRT[79].w + EVT_SPRT[82].w && p[3] >= EVT_SPRT[79].h + EVT_SPRT[82].h)
    {
        r[0].w = EVT_SPRT[79].w;
        r[0].h = EVT_SPRT[79].h;
        r[1].w = EVT_SPRT[82].w;
        r[1].h = EVT_SPRT[82].h;
        r[2].w = EVT_SPRT[80].w;
        r[2].h = EVT_SPRT[80].h;
        r[3].w = EVT_SPRT[81].w;
        r[3].h = EVT_SPRT[81].h;
        r[4].w = EVT_SPRT[86].w;
        r[4].h = EVT_SPRT[86].h;
        r[5].w = EVT_SPRT[83].w;
        r[5].h = EVT_SPRT[83].h;
        r[6].w = EVT_SPRT[84].w;
        r[6].h = EVT_SPRT[84].h;
        r[7].w = EVT_SPRT[85].w;
        r[7].h = EVT_SPRT[85].h;

        r[0].x = p[0];
        r[0].y = p[1];
        r[4].x = r[0].x + r[0].w;
        r[4].y = p[1];
        r[4].w = p[2] - (r[0].w + r[1].w);
        r[1].x = r[4].x + r[4].w;
        r[1].y = p[1];
        r[6].x = p[0];
        r[6].y = r[0].y + r[0].h;
        r[6].w = r[6].w - 1;
        r[6].h = p[3] - (r[0].h + r[2].h);
        r[7].x = p[0] + p[2] - r[7].w;
        r[7].y = r[1].y + r[1].h;
        r[7].w = r[7].w - 1;
        r[7].h = r[6].h;
        r[2].x = p[0];
        r[2].y = r[6].y + r[6].h;
        r[5].x = r[2].x + r[2].w;
        r[5].y = p[1] + p[3] - r[5].h;
        r[5].w = r[4].w;
        r[3].x = r[5].x + r[5].w;
        r[3].y = r[2].y;

        EVT_SPRT[79].x0 = r[0].x;
        EVT_SPRT[79].y0 = r[0].y;
        AddPrimCopy_80040298(pOT_8008D454 + (short)a1, &EVT_SPRT[79], 5);
        AddPrimCopy_80040298(pOT_8008D454 + (short)a1, &dword_8008D440[79], 2);
        EVT_SPRT[82].x0 = r[1].x;
        EVT_SPRT[82].y0 = r[1].y;
        AddPrimCopy_80040298(pOT_8008D454 + (short)a1, &EVT_SPRT[82], 5);
        AddPrimCopy_80040298(pOT_8008D454 + (short)a1, &dword_8008D440[82], 2);
        EVT_SPRT[80].x0 = r[2].x;
        EVT_SPRT[80].y0 = r[2].y;
        AddPrimCopy_80040298(pOT_8008D454 + (short)a1, &EVT_SPRT[80], 5);
        AddPrimCopy_80040298(pOT_8008D454 + (short)a1, &dword_8008D440[80], 2);
        EVT_SPRT[81].x0 = r[3].x;
        EVT_SPRT[81].y0 = r[3].y;
        AddPrimCopy_80040298(pOT_8008D454 + (short)a1, &EVT_SPRT[81], 5);
        AddPrimCopy_80040298(pOT_8008D454 + (short)a1, &dword_8008D440[81], 2);
        setXYWH(&dword_8008D430[86], r[4].x, r[4].y, r[4].w, r[4].h);
        AddPrimCopy_80040298(pOT_8008D454 + (short)a1, &dword_8008D430[86], 10);
        setXYWH(&dword_8008D430[83], r[5].x, r[5].y, r[5].w, r[5].h);
        AddPrimCopy_80040298(pOT_8008D454 + (short)a1, &dword_8008D430[83], 10);
        setXYWH(&dword_8008D430[84], r[6].x, r[6].y, r[6].w, r[6].h);
        AddPrimCopy_80040298(pOT_8008D454 + (short)a1, &dword_8008D430[84], 10);
        setXYWH(&dword_8008D430[85], r[7].x, r[7].y, r[7].w, r[7].h);
        AddPrimCopy_80040298(pOT_8008D454 + (short)a1, &dword_8008D430[85], 10);
    }
}
#endif
INCLUDE_ASM(sub_80042B38);
extern int sub_8003C0A4(int a);
extern int XaStartRead_800434C4(int a);
extern int xaStartPos_80096108;
extern int xaEndPos_8009610C;
extern void XaIdleTask_800430E8();
extern void XaMonitorTask_800432EC();

// Matched
void XaInitTask_80043054(struct_obj_D* p, int* q)
{
    SsSetSerialAttr(0, 0, 1);
    xaRequestPending_80096118 = -1;
    q[0] = 0;
    ((short*)q)[4] = 0;
    p->field_8 = XaIdleTask_800430E8;
}
// Matched
void XaStop_800430B0(void)
{
    SsSetSerialVol(0, 0, 0);
    DsControlB(9, 0, 0);
}
extern int sub_80053EB0(void);
extern void XaWaitFilterTask_800431C4();
void XaSetup_800433FC(int* o);
// Matched
void XaIdleTask_800430E8(struct_obj_D* p, int* q0)
{
    int* q = q0;
    int r;
    int s;
    if (q[0] & 1)
    {
        q[0] &= ~1;
        xaRequestPending_80096118 = -1;
    }
    if ((int)xaRequestPending_80096118 >= 0 && (r = sub_80053EB0()) == 1 && (s = sub_8003C0A4(r)) == r)
    {
        XaSetup_800433FC(q);
        xaRequestPending_80096118 = -1;
        ((short*)q)[4] = s;
        q[0] &= ~1;
        p->field_8 = XaWaitFilterTask_800431C4;
    }
}
// Matched
void XaWaitFilterTask_800431C4(struct_obj_D* p, int* q)
{
    char buf[8];
    if (sub_80053B9C(q[1], buf) == 2)
    {
        p->field_8 = XaStartReadTask_80043204;
    }
}
// Matched
void XaStartReadTask_80043204(struct_obj_D* p, int* q)
{
    if (XaStartRead_800434C4(xaStartPos_80096108))
    {
        q[1] = DsControlF(0x11, 0);
        ((short*)q)[4] = 2;
        p->field_8 = XaMonitorTask_800432EC;
    }
}
// Matched
void XaFadeOutTask_80043264(struct_obj_D* p, short* q)
{
    short v = q[5] - 14;
    q[5] = v;
    if (v < 0)
    {
        q[4] = 0;
        p->field_8 = XaIdleTask_800430E8;
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
void XaMonitorTask_800432EC(struct_obj_D* p, int* q)
{
    u_char result[8];
    DslLOC loc;
    if (sub_80053B9C(q[1], result) == 2 && q[1])
    {
        loc.minute = result[5];
        loc.second = result[6];
        loc.sector = result[7];
        if (DsPosToInt(&loc) > xaEndPos_8009610C || (int)xaRequestPending_80096118 >= 0)
        {
            ((short*)q)[5] = 0x70;
            p->field_8 = XaFadeOutTask_80043264;
            return;
        }
        SsSetSerialVol(0, 0x70, 0x70);
        q[1] = DsControlF(0x11, 0);
    }
    if (xaTimer_8008D450 < -1000 || (q[0] & 1))
    {
        ((short*)q)[5] = 0x70;
        q[0] &= ~1;
        p->field_8 = XaFadeOutTask_80043264;
    }
}
extern int sub_80053608(u_char com, u_char* param, DslCB cbsync, int count); /* DsCommand */
// Matched
void XaSetup_800433FC(int* o)
{
    Data001File f;
    u_char result[8];
    u_char param[4];
    int r;
    DATA_GetFile_8003C7CC(&f, 0x439);
    param[0] = 1;
    param[1] = xaRequest_80096110.channel_2;
    do
    {
        r = sub_80053608(0xD, param, 0, -1);
        o[1] = r;
    } while (r == 0);
    xaStartPos_80096108 = DsPosToInt(&f.field_0_position);
    xaStartPos_80096108 += xaRequest_80096110.startSector_4 * 32;
    xaEndPos_8009610C = xaStartPos_80096108 + xaRequest_80096110.length_6 * 32;
    xaTimer_8008D450 = xaRequest_80096110.length_6 * 1920 / 150;
}
extern int sub_8005384C(unsigned char a, void* b, unsigned char c, int d, int e);
// Matched
int XaStartRead_800434C4(int a)
{
    unsigned char loc[4];
    int r;
    int c = 0xC9;
    int d = 0x1B;
    DsIntToPos(a, loc);
    do
    {
        r = sub_8005384C(c, loc, d, 0, -1);
    } while (r == 0);
    return r;
}
// Matched
int XaRequestStop_80043524(void)
{
    int* p;
    if ((int)xaRequestPending_80096118 >= 0)
    {
        return 0;
    }
    p = dword_8008B560[0x24 / 4];
    *p |= 1;
    return 1;
}
// Matched
void XaRequestPlay_80043564(short a0, short a1, short a2)
{
    xaRequestPending_80096118 = 0;
    xaRequest_80096110.channel_2 = a0;
    xaRequest_80096110.startSector_4 = a1;
    xaRequest_80096110.length_6 = a2;
}
// Matched
int XaIsIdle_80043584(void)
{
    return ((short*)dword_8008B560[0x24 / 4])[4] == 0;
}
// Matched
unsigned int XaNoRequestPending_800435A4(void)
{
    return xaRequestPending_80096118 >> 31;
}
typedef struct
{
    unsigned int count;
    unsigned int flags;
    int size;
    EventNode** out;
    EventEntryFn cb_8;
    EventEntryFn cb_C;
} EventDesc;
#if 0
// Not matched: only next/next2 get swapped registers ($s6/$s7)
EventNode* CreateEventList_800435B4(EventDesc** list)
{
    EventDesc** p;
    EventDesc* d;
    EventNode* next;
    EventNode* head;
    int idx;
    char* buf;
    EventNode* n;
    EventNode* next2;
    EventNode* prev;
    EventNode* last;
    unsigned int i;
    unsigned int flags;

    buf = NULL;
    idx = 0;
    for (p = list; *p != NULL; p++)
    {
        d = *p;
        idx += d->count;
    }
    head = malloc3_dbg((idx + 1) * sizeof(EventNode), aDWorkPsusEvent, 0xDC);
    prev = NULL;
    n = head;
    next = head + 1;
    head->field_0 = (int)prev;
    next2 = head + 2;
    last = head;
    head->next = next;
    head->entry.size = 0;
    head->entry.buffer = NULL;
    head->entry.flags = 0;
    head->entry.field_4 = 0;
    head->field_8 = 0;
    head->count = 0;
    head->entry.cb_8 = NULL;
    head->entry.cb_C = NULL;
    for (idx = 0, p = list; *p != NULL; p++)
    {
        d = *p;
        if (d->out != NULL)
        {
            *d->out = n;
        }
        if (d->size != 0)
        {
            buf = malloc3_dbg(d->size * d->count, aDWorkPsusEvent, 0xF1);
        }
        for (i = 0; i < d->count; i++)
        {
            n->field_0 = (int)prev;
            n->next = next;
            n->entry.size = 0;
            n->entry.buffer = NULL;
            n->entry.flags = 0;
            n->entry.field_4 = 0;
            n->field_8 = 0;
            n->count = 0;
            n->entry.cb_8 = NULL;
            n->entry.cb_C = NULL;
            if (d->size != 0)
            {
                n->entry.buffer = buf;
                n->entry.size = d->size;
                buf += d->size;
            }
            n->entry.cb_8 = d->cb_8;
            n->entry.cb_C = d->cb_C;
            flags = d->flags;
            n->field_8 = idx++;
            n->entry.flags = flags;
            n->count = d->count;
            n->entry.field_4 = i;
            prev = last = n;
            n = next;
            next = next2;
            next2++;
        }
    }
    last->next = NULL;
    return head;
}
#endif
INCLUDE_ASM(CreateEventList_800435B4);
// Matched
void* EventEntryAllocBuffer_800437E8(int* a0, int size)
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
int EventEntryFreeBuffer_80043840(int* a0)
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
void RunEventList_80043898(EventNode* n)
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
void RunEventListUntilAbort_80043958(EventNode* n)
{
    if (eventDispatchHalt_8008B540 == 0)
    {
        do
        {
            if ((n->entry.flags & 0x8001) == 1)
            {
                n->entry.cb_8(&n->entry, n->entry.buffer);
            }
            n = n->next;
        } while (n && eventDispatchHalt_8008B540 == 0);
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
int FreeEventList_80043A5C(EventNode* head)
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
