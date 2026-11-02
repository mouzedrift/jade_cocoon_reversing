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

INCLUDE_DATA(dword_80098690);
INCLUDE_DATA(dword_800986A0);
INCLUDE_DATA(dword_800987D8);
INCLUDE_DATA(dword_8009AAD8);

// Matched
EventEntry* sub_80043AF8(EventNode* n)
{
    int i;
    int count = n->count;
    for (i = 0; i < count; i++)
    {
        EventEntry* e = &n->entry;
        if (!(e->flags & 1))
        {
            return e;
        }
        n = n->next;
    }
    return 0;
}
// Matched
void sub_80043B40(int* p)
{
    int n = p[3];
    int i;
    for (i = 0; i < n; i++)
    {
        if (p[4] & 1)
        {
            p[4] = (p[4] & ~1) | 0x8000;
        }
        p = (int*)p[1];
    }
}
INCLUDE_ASM(sub_80043B8C);
INCLUDE_ASM(sub_80043DE0);
INCLUDE_ASM(sub_80044010);
INCLUDE_ASM(sub_80044D0C);
INCLUDE_ASM(sub_800451BC);
INCLUDE_ASM(sub_80045534);
INCLUDE_ASM(sub_800459E4);
INCLUDE_ASM(sub_80045E48);
INCLUDE_ASM(sub_80046248);
/* 4096-entry sine table at 0x80084540 (inside the asc_80084350 data chunk) */
extern short asc_80084350[];
#define SIN_TABLE (asc_80084350 + 0xF8)
// Matched
void sub_8004668C(SVECTOR* r, MATRIX* m)
{
    int cx = SIN_TABLE[(r->vx + 0x400) & 0xFFF];
    int cz = SIN_TABLE[(r->vz + 0x400) & 0xFFF];
    int sx = SIN_TABLE[r->vx & 0xFFF];
    int sz = SIN_TABLE[r->vz & 0xFFF];
    int cy = SIN_TABLE[(r->vy + 0x400) & 0xFFF];
    int sy = SIN_TABLE[r->vy & 0xFFF];
    int a;
    int b;
    m->m[2][1] = sx;
    b = (cz * sx) >> 12;
    a = (sz * sx) >> 12;
    m->m[0][0] = ((cz * cy) >> 12) - ((a * sy) >> 12);
    m->m[1][0] = ((sz * cy) >> 12) + ((b * sy) >> 12);
    m->m[2][0] = -(cx * sy) >> 12;
    m->m[0][1] = -(sz * cx) >> 12;
    m->m[1][1] = (cz * cx) >> 12;
    m->m[0][2] = ((cz * sy) >> 12) + ((a * cy) >> 12);
    m->m[2][2] = (cx * cy) >> 12;
    m->m[1][2] = ((sz * sy) >> 12) - ((b * cy) >> 12);
}
INCLUDE_ASM(sub_80046874);
INCLUDE_ASM(sub_80046A58);
INCLUDE_ASM(sub_80047E28);
INCLUDE_ASM(sub_8004A4FC);
INCLUDE_ASM(sub_8004AD44);
