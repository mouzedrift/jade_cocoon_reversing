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

INCLUDE_DATA(aAssertionFaile_3);
INCLUDE_DATA(aEffectC);
INCLUDE_DATA(dword_800795A0);
INCLUDE_DATA(dword_800795D0);
INCLUDE_DATA(dword_800795D4);
INCLUDE_DATA(word_800795D8);
INCLUDE_DATA(dword_800795DC);
INCLUDE_DATA(dword_800795E0);
INCLUDE_DATA(dword_800795E4);
INCLUDE_DATA(dword_800795E8);
INCLUDE_DATA(dword_800795EC);
INCLUDE_DATA(dword_800795F0);

#if 0
// Not matched (7 words): result register and branch polarity
int sub_80013DB0(void)
{
    int r = rand();
    int v;
    if (r % 6)
    {
        v = 1;
    }
    else
    {
        v = 2;
    }
    return v;
}
#endif
INCLUDE_ASM(sub_80013DB0);
// Matched
int sub_80013E00(unsigned int idx, int add)
{
    int result = 0;
    if (idx < 0x15)
    {
        result = dword_80079348[idx] + add;
    }
    return result;
}
// Matched
int sub_80013E30(void)
{
    return rand() % 100;
}
// Matched
void sub_80013E80(void* p, int arg)
{
    sub_80033624(p, sub_80014390(arg & 0xFF));
}
// Matched
void sub_80013EB4(void* p, int a1, int a2)
{
    sub_80033624(p, (int)GetMinionStatus_800107A0(a2));
}
int sub_80014200(unsigned char* p);
// Matched
void sub_80013EE8(int* out, unsigned char* m, unsigned char* x, int mode)
{
    int a;
    int b;
    if (mode == 1)
    {
        out[0] = m[0x2C];
        out[2] = m[0x2E];
        out[4] = sub_80014114(10) + x[5];
        out[6] = CriticalRateTransform_80014164((unsigned char)(m[0x37] / 10));
        out[8] = 0;
        a = m[0x2D] * (m[0x2D] - 20) / 7;
        b = m[0x2F] * (m[0x2F] - 20) / 7;
        out[1] = (a < 0) ? 0 : ((a < 0x7FFF) ? a : 0x7FFF);
        out[3] = (b < 0) ? 0 : ((b < 0x7FFF) ? b : 0x7FFF);
        out[5] = sub_8001413C(10);
        out[7] = 0;
        out[9] = 100;
    }
    else
    {
        out[0] = m[0x2C];
        out[2] = m[0x2E];
        out[4] = sub_80014114(sub_80014200(m + 0x2C) / 10) + x[5];
        out[6] = CriticalRateTransform_80014164((unsigned char)(m[0x37] / 10));
        out[8] = 0;
        out[1] = m[0x2D];
        out[3] = m[0x2F];
        out[5] = sub_8001413C(sub_80014200(m + 0x2C) / 10);
        out[7] = 0;
        out[9] = sub_80014200(m + 0x2C);
    }
}
// Matched
int sub_80014114(int x)
{
    return (x * x) / 10;
}
// Matched
int sub_8001413C(int x)
{
    return (x * x) / 5;
}
// Matched
int CriticalRateTransform_80014164(int x)
{
    return (x * x * x) / 400;
}
// Matched
void sub_8001419C(unsigned char* p, short* out)
{
    int a = (p[7] + p[9]) >> 1;
    int x = p[10] * 47 / (p[10] + a);
    int y = p[8] * 47 / (p[8] + p[6]);
    out[0] = x;
    out[1] = y;
}
// Matched
int sub_80014200(unsigned char* p)
{
    int a = (p[7] + p[9]) >> 1;
    int v = p[10] * 200 / (p[10] + a);
    if (v > 0)
    {
        if (v > 200)
        {
            v = 200;
        }
    }
    else
    {
        v = 1;
    }
    return v;
}
// Matched
int sub_8001425C(unsigned char* p)
{
    int a = (p[7] + p[9]) >> 1;
    int v = a * 200 / (a + p[10]);
    if (v > 0)
    {
        if (v > 200)
        {
            v = 200;
        }
    }
    else
    {
        v = 1;
    }
    return v;
}
// Matched
int sub_800142B8(unsigned char* p)
{
    int v = p[8] * 200 / (p[8] + p[6]);
    if (v > 0)
    {
        if (v > 200)
        {
            v = 200;
        }
    }
    else
    {
        v = 1;
    }
    return v;
}
// Matched
int sub_80014308(unsigned char* p)
{
    int v = p[6] * 200 / (p[6] + p[8]);
    if (v > 0)
    {
        if (v > 200)
        {
            v = 200;
        }
    }
    else
    {
        v = 1;
    }
    return v;
}
// Matched
int sub_80014358(unsigned int mask)
{
    unsigned int i;
    for (i = 0; i < 32; i++)
    {
        if (mask & (1 << i))
        {
            return i;
        }
    }
    return 0;
}
#if 0
int sub_80014390(int arg0)
{
    return 0;
}
#endif
INCLUDE_ASM(sub_80014390);
// Matched
int sub_80014444(int a0)
{
    unsigned int v = a0 & 0xFF;
    int r = 0;
    if (v >= 8)
    {
        v = a0 - 8;
        r = sub_800A11D8(v & 0xFF);
    }
    else if (v != 0)
    {
        v = a0 - 1;
        r = (int)GetMinion_80010598(3, v & 0xFF);
    }
    return r;
}
#if 0
// Not matched (12 words): masked copy of a0 - 4 is kept in a register by CSE
int sub_8001449C(int a0)
{
    int r = 0;
    int v = a0 - 4;
    if ((unsigned char)v < 3)
    {
        int flags = sub_800A248C();
        int m = 1 << a0;
        if (flags & m)
        {
            r = sub_800A2B20((unsigned char)v);
        }
    }
    return r;
}

#endif
INCLUDE_ASM(sub_8001449C);
// Matched
void sub_8001450C(int* a0, struct_16* a1, int a2, int a3)
{
    unsigned int i;
    sub_80014574(a1, a2, a3);
    for (i = 0; i < a1->field_4; i++)
    {
        a0[i] = 0;
    }
}
// Matched
void sub_80014574(struct_16* p, int a1, int a2)
{
    p->field_0 = a1;
    p->field_4 = a2;
    p->field_8 = 0;
    p->field_C = 0;
}
// Matched
void sub_80014588(int* a0, struct_16* a1, unsigned int a2)
{
    unsigned int i;
    a0[a2 % a1->field_4] = a1->field_8;
    a1->field_C = 0;
    for (i = 0; i < a1->field_4; i++)
    {
        a1->field_C += a0[(a2 - i) % a1->field_4] * ((int*)a1->field_0)[i];
    }
    a1->field_C >>= 12;
}
typedef struct
{
    int pad0[10];
    int flags;
    int state;
    int pad30;
    int pad34;
    int idx;
    int timer;
} EffectState;
void sub_80014638(struct_obj_D* p, void* buf);
// Matched
void sub_80014618(struct_obj_D* p, int* q)
{
    q[0x28 / 4] = 2;
    q[0x3C / 4] = 0;
    q[0x2C / 4] = 0;
    p->field_8 = (void (*)(void))sub_80014638;
}
extern short dword_800795D0[];
extern short dword_800795F0[];
extern void sub_80020DDC(int a0, int* out, short* a2, short* a3, int a4, int a5);
int sub_800147FC(void);
// Matched
void sub_80014638(struct_obj_D* p, void* buf)
{
    EffectState* q = (EffectState*)buf;
    int r;
    int vlc;
    int img;
    if (q->timer > 0)
    {
        q->timer--;
    }
    switch ((unsigned int)q->state)
    {
    case 0:
        if (q->flags & 4)
        {
            q->flags &= ~2;
            q->flags &= ~4;
            if (q->idx >= 0x46)
            {
                q->idx = 0x12;
            }
            sub_80020DDC(dword_800795F0[q->idx * 2], dword_80091BD0, dword_800795D0, dword_800795D0, 0, 0);
            q->state = 1;
        }
        break;
    case 1:
        r = sub_80020EBC(dword_80091BD0);
        if (r == 1 && IsFileRequestQueueIdle_8003BF88() == r)
        {
            vlc = dword_80091BD0[0x34 / 4];
            img = dword_80091BD0[0x38 / 4];
            q->state = 2;
            mdecEffectVlcBuffer_8008D42C = (unsigned long*)vlc;
            decodedImageData_8008B4A0 = (unsigned long*)img;
        }
        break;
    case 2:
        if (q->flags & 1)
        {
            q->flags &= ~1;
            q->state = 3;
        }
        break;
    case 3:
        if (sub_800147FC() == 0 && q->timer == 0 && !(q->flags & 2))
        {
            sub_80020EE0(dword_80091BD0);
            unknownFlags_8008D678 &= ~0x800;
            q->state = 0;
            q->flags |= 2;
        }
        break;
    }
}
// Matched
int sub_800147FC(void)
{
    int i;
    int c;
    EventNode* head;
    EventNode* n;
    int count;
    EventNode* head2;
    EventNode* n2;
    int j;
    i = 0;
    head = dword_8008B4A8;
    c = i;
    count = head->count;
    for (n = head; i < count; i++)
    {
        if ((n->entry.flags & 0x8001) == 1)
        {
            c++;
        }
        n = n->next;
    }
    head2 = dword_8008D60C;
    j = 0;
    count = head2->count;
    for (n2 = head2; j < count; j++)
    {
        if ((n2->entry.flags & 0x8001) == 1)
        {
            c++;
        }
        n2 = n2->next;
    }
    return c;
}
// Matched
void sub_800148A0(void)
{
    sub_80020EE0(dword_80091BD0);
    unknownFlags_8008D678 &= ~0x800;
}
// Matched
int sub_800148D4(void)
{
    return ((int*)dword_8008D3F8[9])[0x2C / 4] == 0;
}
// Matched
void sub_800148F4(int a0)
{
    int* p = dword_8008D3F8[9];
    p[0x28 / 4] |= 4;
    p[0x38 / 4] = a0;
    if (p[0x2C / 4] != 0)
    {
        printf(aAssertionFaile_3, aEffectC, 0x124);
        exit(1);
    }
}
