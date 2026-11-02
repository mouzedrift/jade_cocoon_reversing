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

INCLUDE_DATA(dword_8008713C);
INCLUDE_DATA(dword_80087140);
INCLUDE_DATA(dword_80087144);
INCLUDE_DATA(dword_8009AAE0);
INCLUDE_DATA(dword_8009AAE4);
INCLUDE_DATA(dword_8009AAE8);
INCLUDE_DATA(dword_8009AAEC);
INCLUDE_DATA(dword_8009AAF0);
INCLUDE_DATA(dword_8009AAF4);
INCLUDE_DATA(dword_8009AAF8);
INCLUDE_DATA(dword_8009AB00);
INCLUDE_DATA(byte_8009AB10);
INCLUDE_DATA(dword_8009AB30);
INCLUDE_DATA(dword_8009AB34);
INCLUDE_DATA(dword_8009AB38);
INCLUDE_DATA(dword_8009AB3C);
INCLUDE_DATA(dword_8009AB40);
INCLUDE_DATA(dword_8009AB48);
INCLUDE_DATA(dword_8009AB4C);
INCLUDE_DATA(dword_8009AB50);
INCLUDE_DATA(dword_8009AB60);
INCLUDE_DATA(dword_8009AB70);
INCLUDE_DATA(dword_8009AB80);
INCLUDE_DATA(dword_8009AB88);
INCLUDE_DATA(dword_8009ABB0);
INCLUDE_DATA(dword_8009ABB4);
INCLUDE_DATA(word_8009ABB8);
INCLUDE_DATA(dword_8009AD90);
INCLUDE_DATA(dword_8009ADE0);
INCLUDE_DATA(dword_8009ADE4);
INCLUDE_DATA(dword_8009ADE8);
INCLUDE_DATA(dword_8009ADEC);
INCLUDE_DATA(dword_8009ADF0);
INCLUDE_DATA(dword_8009ADF4);
INCLUDE_DATA(dword_8009ADF8);
INCLUDE_DATA(dword_8009ADFC);

#define ABS_8004B0A8(x) ((x) < 0 ? -(x) : (x))
// Matched
void sub_8004B0A8(VECTOR* v, MATRIX* m)
{
    VECTOR t;
    VECTOR u;
    VECTOR n0;
    VECTOR n1;
    VECTOR n2;
    int ax;
    int ay;
    int az;
    sub_8003B684((int*)v);
    VectorNormal(v, &n0);
    m->m[0][0] = n0.vx;
    m->m[1][0] = n0.vy;
    m->m[2][0] = n0.vz;
    ay = ABS_8004B0A8(n0.vy);
    ax = ABS_8004B0A8(n0.vx);
    if (ax < ay)
    {
        az = ABS_8004B0A8(n0.vz);
        if (az < ax)
        {
            t.vx = n0.vy;
            t.vy = -n0.vx;
            if (n0.vz)
            {
                t.vz = -(n0.vx * t.vx + n0.vy * t.vy) / n0.vz;
            }
            else
            {
                t.vz = 0;
            }
        }
        else
        {
            if (n0.vy)
            {
                t.vz = n0.vy;
                t.vy = -n0.vz;
            }
            else
            {
                t.vz = 0;
                t.vy = n0.vz;
            }
            if (n0.vx)
            {
                t.vx = -(n0.vz * t.vz + n0.vy * t.vy) / n0.vx;
            }
            else
            {
                t.vx = 0;
            }
        }
    }
    else
    {
        az = ABS_8004B0A8(n0.vz);
        if (az < ay)
        {
            t.vx = n0.vy;
            t.vy = -n0.vx;
            if (n0.vz)
            {
                t.vz = -(n0.vx * t.vx + n0.vy * t.vy) / n0.vz;
            }
            else
            {
                t.vz = 0;
            }
        }
        else
        {
            if (n0.vz)
            {
                t.vx = n0.vz;
                t.vz = -n0.vx;
            }
            else
            {
                t.vx = 0;
                t.vz = n0.vx;
            }
            if (n0.vy)
            {
                t.vy = -(n0.vx * t.vx + n0.vz * t.vz) / n0.vy;
            }
            else
            {
                t.vy = 0;
            }
        }
    }
    sub_8003B684((int*)&t);
    VectorNormal(&t, &n1);
    m->m[0][1] = n1.vx;
    m->m[1][1] = n1.vy;
    m->m[2][1] = n1.vz;
    OuterProduct12(&n0, &n1, &u);
    sub_8003B684((int*)&u);
    VectorNormal(&u, &n2);
    m->m[0][2] = n2.vx;
    m->m[1][2] = n2.vy;
    m->m[2][2] = n2.vz;
}
INCLUDE_ASM(sub_8004B320);
INCLUDE_ASM(sub_8004B590);
INCLUDE_ASM(sub_8004B844);
INCLUDE_ASM(sub_8004BB9C);
INCLUDE_ASM(sub_8004BFA8);
INCLUDE_ASM(sub_8004C21C);
INCLUDE_ASM(sub_8004C4F0);
INCLUDE_ASM(sub_8004C7BC);
INCLUDE_ASM(sub_8004D0E8);
extern void sub_80044D0C(int a0, int a1, int a2, int a3, int a4, int a5, int a6, int a7);

// Matched
void sub_8004D1EC(int a0, int a1, int a2, int a3, int a4, int a5, int a6)
{
    sub_80044D0C(a0, a1, a2, a3, a4, a5, a6, 0);
}
typedef struct
{
    char pad_0[0x14];
    unsigned short* field_14;
} struct_tbl14;

// Matched
void sub_8004D224(unsigned short* out, struct_tbl14* s, int idx)
{
    if (idx == 0)
    {
        out[0] = 0;
        out[1] = 0;
        out[2] = 0;
        return;
    }
    out[0] = s->field_14[idx * 3];
    out[1] = s->field_14[idx * 3 + 1];
    out[2] = s->field_14[idx * 3 + 2];
}
INCLUDE_ASM(sub_8004D288);
INCLUDE_ASM(sub_8004D3D8);
INCLUDE_ASM(sub_8004D5CC);
INCLUDE_ASM(sub_8004D7A8);
