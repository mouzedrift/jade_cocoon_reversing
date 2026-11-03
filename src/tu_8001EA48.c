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

// the block at 0x8008D4F0 (tu_80036528.c copies its first 0x68 bytes as Block104)
typedef struct
{
    VECTOR pos;
    int field_10;
    int active;
} struct_8008D4F0_point;
typedef struct
{
    char pad_0[0x44];
    struct_8008D4F0_point points[8];
} struct_8008D4F0;
extern VECTOR levantPos_8008BD18;
extern short dword_8008D474[2];
extern int off_8007DC70;
extern short asc_80084350[]; // a short table (indexed & 0xFFF) starts at +0x1F0 (0x80084540)
typedef struct
{
    int fileIdx;
    unsigned int** ppDest;
} OverlayEntry;
extern OverlayEntry overlays_8007D9E8[];
extern int QueueFileRequest_8003BC84(int* p);
extern int StartFileRequestTask_8003C6C8(int* req);
void OnEffectFileLoaded_80020F5C();
extern unsigned short padPrevHeld_800918C8[];
extern unsigned short padRepeat_800918CC[];
extern unsigned short padReleased_800918D4[];
extern unsigned short padPressed_8009194C[];
extern unsigned short padHoldFrames_80091950[][16];
extern signed char padAnalog_800918D8[][4];
extern unsigned char padAnalogMax_800918E0[][4];
typedef struct
{
    int field_0;
    unsigned int flags_4;
    int field_8;
    int field_C;
    char pad_10[0xA];
    short field_1A;
    char pad_1C[0xA];
    short field_26;
    char pad_28[0x48];
    VECTOR target_70;
    char pad_80[0x10];
    int field_90;
    char pad_94[0x10];
    int field_A4;
    int field_A8;
    int pad_AC;
    int field_B0;
    char pad_B4[8];
    short field_BC;
    short field_BE;
    short field_C0;
    short field_C2;
    short field_C4;
    short field_C6;
    short field_C8;
    short field_CA;
    char pad_CC[4];
    unsigned char* script_D0;
    unsigned int field_D4;
    char pad_D8[0x1C];
    unsigned short field_F4;
    short field_F6;
    char pad_F8[6];
    short field_FE;
} ScriptObj;
// Matched
void sub_8001EA48(void* arg0)
{
    ScriptObj* o = arg0;
    int done;
    int flag22;
    int flag21;
    int target;
    unsigned char* cmd;
    int n;
    int mode;
    int r;
    flag22 = 0;
    flag21 = flag22;
    done = flag22;
    target = o->field_90;
    if (o->field_C6 <= 0)
    {
        return;
    }
    if (o->flags_4 & 0x4000)
    {
        if (++o->field_C8 >= o->field_CA)
        {
            o->field_C8 = 0;
            o->field_CA = 0;
            o->flags_4 |= 0x10000;
        }
    }
    if (o->flags_4 & 0x10000)
    {
        target = -1;
    }
    cmd = o->script_D0 + o->field_C4 * 4;
    while (!done)
    {
        if (target != *(short*)(cmd + 2) && o->field_90 != *(short*)(cmd + 2) && *(short*)(cmd + 2) != -2)
        {
            return;
        }
        o->flags_4 &= ~0x10000;
        switch (cmd[0])
        {
        case 0:
            o->flags_4 &= 0xFF17FFFF;
            return;
        case 1:
            n = *(short*)(cmd + 6);
            if (o->field_C2 != n)
            {
                sub_8001D6EC((struct_obj_A*)o, 0);
                if (n == 0x4003)
                {
                    n = o->field_A4;
                    o->field_C2 = o->field_A4;
                    o->field_A4 = o->field_FE;
                    o->field_FE = -1;
                }
                else
                {
                    o->field_C2 = n;
                }
                mode = flag22 ? -2 : -1;
                if (o->field_A8 >= 0)
                {
                    mode = o->field_A8;
                    o->field_A8 = -1;
                }
                sub_8001D760((char*)o, n, mode, flag21);
            }
            done = 1;
            break;
        case 2:
            flag22 = 1;
            break;
        case 3:
            if (!(o->flags_4 & 0x2000000))
            {
                r = o->field_D4;
                if (!(r & 1))
                {
                    flag21 = 1;
                }
                o->field_D4 = r & ~1;
            }
            break;
        case 4:
            o->field_C8 = 0;
            o->field_CA = *(short*)(cmd + 6);
            break;
        case 5:
            o->field_C8 = 0;
            o->field_CA = o->field_F4;
            break;
        case 6:
            sub_8001D9E4((struct_obj_A*)o, sub_8001F03C((int)o, (int)cmd, 0x4000, 0), *(short*)(cmd + 6));
            break;
        case 7:
            sub_8001DA08((struct_obj_A*)o, sub_8001F03C((int)o, (int)cmd, 0x4000, 0), *(short*)(cmd + 6));
            break;
        case 8:
            sub_8001DA2C((struct_obj_A*)o);
            break;
        case 9:
            sub_8001DA4C((char*)o, sub_8001F03C((int)o, (int)cmd, 0x4001, 0), o->field_26, *(short*)(cmd + 6));
            break;
        case 10:
            sub_8001DA4C((char*)o, sub_8001F03C((int)o, (int)cmd, 0x4001, 0), o->field_26, o->field_F6);
            break;
        case 11:
            sub_8001D730((struct_obj_A*)o, *(short*)(cmd + 6));
            break;
        case 12:
            sub_8001D8B4((char*)o, *(short*)(cmd + 6));
            break;
        case 13:
            if (sub_8001D8A8((short*)o))
            {
                break;
            }
            else
            {
                o->flags_4 |= 0x10000;
                return;
            }
        case 14:
            sub_8001D92C((char*)o, *(short*)(cmd + 6));
            break;
        case 15:
            if ((o->flags_4 & 0x4080000) && o->field_C < 3)
            {
                if (!TurnActorTowards_8001DDFC((char*)o, &o->target_70, o->target_70.pad))
                {
                    sub_8001D71C((struct_obj_A*)o);
                    o->flags_4 |= 0x10000;
                    return;
                }
                o->flags_4 &= ~0x80000;
            }
            o->flags_4 &= ~0x400000;
            if (!(o->flags_4 & 0x20000))
            {
                o->flags_4 |= 0x10000;
                return;
            }
            o->flags_4 &= ~0x20000;
            break;
        case 16:
            sub_8001EFC4((struct_obj_F*)o);
            break;
        case 17:
            if (o->field_C2 != o->field_C0)
            {
                o->field_C2 = o->field_C0;
                sub_8001D760((char*)o, o->field_C0, -2, flag21);
            }
            break;
        case 18:
            if (!sub_8001DC60((char*)o, (int)&o->target_70, o->target_70.pad, 200))
            {
                o->flags_4 |= 0x10000;
                return;
            }
            target = -1;
            o->flags_4 &= ~0x80000;
            break;
        case 19:
            if (TurnActorTowards_8001DDFC((char*)o, &o->target_70, o->target_70.pad))
            {
                target = -1;
                o->flags_4 &= ~0x80000;
            }
            else
            {
                sub_8001D71C((struct_obj_A*)o);
                o->flags_4 |= 0x10000;
                return;
            }
            break;
        case 21:
            if (o->field_CA != 0 || o->field_90 != o->field_1A || (o->flags_4 & 0x2000000))
            {
                o->flags_4 |= 0x10000;
                return;
            }
            break;
        case 22:
            sub_8001D6EC((struct_obj_A*)o, *(short*)(cmd + 6) != 0);
            break;
        case 23:
            if (++o->field_B0 > *(short*)(cmd + 6))
            {
                o->field_B0 = 0;
            }
            else
            {
                o->flags_4 |= 0x10000;
                return;
            }
            break;
        case 24:
            o->field_BC = 0;
            o->field_BE = *(short*)(cmd + 6);
            o->flags_4 = o->flags_4 | *(short*)(cmd + 0xA) | 0x40000000;
            break;
        }
        o->field_C4 += cmd[1];
        cmd += cmd[1] * 4;
    }
}
INCLUDE_DATA(dword_8007411C);
// Matched
void sub_8001EFC4(struct_obj_F* p)
{
    unsigned int f = p->flags_4;
    int n;
    if (f & 0x800000)
    {
        n = p->field_C;
        if (n < 0)
        {
            if (f & 0x200000)
            {
                sub_800A5BCC(n - 2);
            }
        }
        else if (n >= 3)
        {
            if (f & 0x200000)
            {
                sub_800A5BCC(n - 2);
            }
        }
    }
    p->flags_4 &= 0xFF17FFFF;
}
typedef struct
{
    signed char id;
    char pad_1;
    short start;
    short loop;
    short end;
    char pad_8[0x34];
} struct_3c;
// Matched
int sub_8001F03C(int a0, int a1, int a2, int a3)
{
    char* o = (char*)a0;
    unsigned char* s = (unsigned char*)a1;
    int t;
    int rep;
    int flag;
    int start;
    int loop;
    int idx;
    int end;
    t = 0;
    rep = t;
    flag = t;
    while (s[0] != 0)
    {
        if (s[0] == 1)
        {
            idx = *(short*)(s + 6);
            if (flag == 0)
            {
                start = (*(struct_3c**)(o + 0x148))[idx].start;
            }
            else
            {
                start = (*(struct_3c**)(o + 0x148))[idx].loop;
            }
            loop = (*(struct_3c**)(o + 0x148))[idx].loop;
            end = (*(struct_3c**)(o + 0x148))[idx].end;
            if (a2 != -1 && a2 < 0x4000 && (*(struct_3c**)(o + 0x148))[a2].id == (*(struct_3c**)(o + 0x148))[idx].id && end >= a3)
            {
                return ((t + a3 - start) << 12) / *(short*)(o + 0x1E);
            }
            if (start == loop)
            {
                t += (end - start + 1) * (rep + 1);
            }
            else
            {
                t += (end - loop + 1) * (rep + 1);
                t += loop - start;
            }
            t--;
            flag = 0;
        }
        else if (s[0] == 0x14)
        {
            if (a2 >= 0x4000 && a2 == *(short*)(s + 6))
            {
                return (t << 12) / *(short*)(o + 0x1E);
            }
        }
        else if (s[0] == 0xF)
        {
            t = 0;
        }
        else if (s[0] == 2)
        {
            flag = 1;
        }
        else if (s[0] == 4)
        {
            rep = *(short*)(s + 6) - 1;
        }
        else if (s[0] == 5)
        {
            rep = *(short*)(o + 0xF4) - 1;
        }
        else if (s[0] == 0x17)
        {
            t += *(short*)(s + 6);
        }
        else if (s[0] == 0 || s[0] == 0x10)
        {
            if (a2 != -1 && a2 < 0x4000 && (*(struct_3c**)(o + 0x148))[a2].end < a3)
            {
                t += a3 - (*(struct_3c**)(o + 0x148))[a2].end;
            }
            return (t << 12) / *(short*)(o + 0x1E);
        }
        s += s[1] * 4;
    }
    return -1;
}
// Matched
short sub_8001F268(char* o, short* out, int a2, int idx)
{
    short* e = (short*)(*(char**)(o + 0x148) + idx * 60 + 8);
    int i;
    for (i = 0; i < 10; i++)
    {
        if (e[i * 2] < 0 && e[i * 2 + 1] < 0)
        {
            out[i * 2] = -1;
            out[i * 2 + 1] = -1;
        }
        else
        {
            out[i * 2] = sub_8001F03C((int)o, a2, idx, e[i * 2]);
            out[i * 2 + 1] = sub_8001F03C((int)o, a2, idx, e[i * 2 + 1]);
        }
    }
    return out[0];
}
extern void sub_8004D288(int* out, int* s, int k);
extern int sub_800B716C(VECTOR* pos, VECTOR* prev, SVECTOR* rot, void* a3);
// Matched
void sub_8001F354(void* a0)
{
    char* o = a0;
    int save[3];
    int* e;
    int dx;
    int dz;
    int v;
    short* r;
    int* s;
    short c;
    int sn;
    short a;
    e = (int*)(*(char**)(*(char**)(o + 0x15C) + 0x54) + *(int*)(o + 0x9C) * 28);
    *(int*)(o + 0x44) = *(int*)(o + 0x38);
    *(int*)(o + 0x48) = *(int*)(o + 0x3C);
    *(int*)(o + 0x4C) = *(int*)(o + 0x40);
    save[0] = *(int*)(o + 0x64);
    save[1] = *(int*)(o + 0x68);
    save[2] = *(int*)(o + 0x6C);
    sub_8004D288((int*)(o + 0x64), e, *(unsigned int*)(o + 0x90) % e[0]);
    if (*(unsigned int*)(o + 0x90) % e[0] == 0 || (*(int*)(o + 4) & 8))
    {
        *(int*)(o + 4) &= ~8;
        if (*(int*)(o + 4) & 0x40000)
        {
            dx = 0;
            dz = 0;
        }
        else
        {
            dx = *(int*)(o + 0x64);
            dz = *(int*)(o + 0x6C);
        }
    }
    else if (*(int*)(o + 4) & 0x40000)
    {
        dx = *(int*)(o + 0x64) - save[0];
        dz = *(int*)(o + 0x6C) - save[2];
    }
    else
    {
        dx = *(int*)(o + 0x64);
        dz = *(int*)(o + 0x6C);
    }
    if (dx < 0)
    {
        dx = 0;
    }
    if (dz < 0)
    {
        dz = 0;
    }
    if (*(int*)(o + 4) & 0x20000000)
    {
        dx = dx * *(int*)(o + 0x8C) / 4096;
        dz = dz * *(int*)(o + 0x8C) / 4096;
    }
    r = *(short**)(o + 0x144);
    s = (int*)(o + 0x138);
    if (*(int*)(o + 4) & 0x4000000)
    {
        if (TurnActorTowards_8001DDFC(o, (VECTOR*)(o + 0x70), *(int*)(o + 0x7C)))
        {
            *(int*)(o + 4) &= ~0x4000000;
        }
    }
    if (*(int*)(o + 4) & 0x2000000)
    {
        *(int*)(o + 0x64) = (*(short**)(*(char**)(o + 0x160) + 8))[*(int*)(o + 0x98) * 4 + 0];
        *(int*)(o + 0x68) = (*(short**)(*(char**)(o + 0x160) + 8))[*(int*)(o + 0x98) * 4 + 1];
        *(int*)(o + 0x6C) = (*(short**)(*(char**)(o + 0x160) + 8))[*(int*)(o + 0x98) * 4 + 2];
        *(int*)(o + 0x38) = *(int*)(o + 0x50) + *(int*)(o + 0x64) / *(int*)(*(char**)(o + 0x160) + 4);
        *(int*)(o + 0x3C) = *(int*)(o + 0x54) + *(int*)(o + 0x68) / *(int*)(*(char**)(o + 0x160) + 4);
        *(int*)(o + 0x40) = *(int*)(o + 0x58) + *(int*)(o + 0x6C) / *(int*)(*(char**)(o + 0x160) + 4);
        *(short*)(o + 0x5E) = (*(short**)(*(char**)(o + 0x160) + 8))[*(int*)(o + 0x98) * 4 + 3];
    }
    else if (*(int*)(o + 4) & 0x1000000)
    {
        a = *(short*)(o + 0x5E);
        sn = (asc_80084350 + 0xF8)[a & 0xFFF];
        c = (asc_80084350 + 0xF8)[(a + 0x400) & 0xFFF];
        *(int*)(o + 0x40) = *(int*)(o + 0x58) + (*(int*)(o + 0x6C) * c - *(int*)(o + 0x64) * sn) / 4096 / e[2];
        *(int*)(o + 0x38) = *(int*)(o + 0x50) + (*(int*)(o + 0x6C) * sn + *(int*)(o + 0x64) * c) / 4096 / e[2];
        *(int*)(o + 0x3C) = *(int*)(o + 0x54) + *(int*)(o + 0x68) / e[2];
    }
    else if (*(int*)(o + 4) & 0x40000)
    {
        *(int*)(o + 0x38) += dz * (asc_80084350 + 0xF8)[*(short*)(o + 0x5E) & 0xFFF] / 4096 * r[2] / 4096 * s[2] / 4096 / e[2];
        *(int*)(o + 0x40) += dz * (asc_80084350 + 0xF8)[(*(short*)(o + 0x5E) + 0x400) & 0xFFF] / 4096 * r[2] / 4096 * s[2] / 4096 / e[2];
    }
    else
    {
        *(int*)(o + 0x38) = *(int*)(o + 0x50) + dz * (asc_80084350 + 0xF8)[*(short*)(o + 0x5E) & 0xFFF] / 4096 / e[2];
        *(int*)(o + 0x40) = *(int*)(o + 0x58) + dz * (asc_80084350 + 0xF8)[(*(short*)(o + 0x5E) + 0x400) & 0xFFF] / 4096 / e[2];
    }
    if (*(int*)(o + 4) & 0x40000)
    {
        *(int*)(o + 0x84) = *(int*)(o + 0x80);
        *(int*)(o + 0x80) = sub_800B716C((VECTOR*)(o + 0x38), (VECTOR*)(o + 0x44), (SVECTOR*)(o + 0x5C), o + 0xB4);
    }
}
// Matched
void sub_8001F918(void* a0)
{
    char* p = a0;
    switch (*(short*)(p + 0x10))
    {
    case 0:
        break;
    case 1:
        RequestModelAnim_8002032C(*(short*)(p + 0x16), ((int*)*(int*)p)[1], *(short*)(p + 0x12));
        *(unsigned short*)(p + 0x14) = *(unsigned short*)(p + 0x12);
        *(short*)(p + 0x12) = -1;
        *(short*)(p + 0x10) = 2;
        break;
    case 2:
        if (AreFileRequestsDone_80024DC4((int*)*(int*)(p + 0x15C)))
        {
            *(short*)(p + 0x10) = 0;
        }
        break;
    }
}
// Matched
void sub_8001F9AC(void* p)
{
    sub_8001F9F0(p);
    sub_8001FB00(p);
    sub_8001FD08(p);
    sub_8001FF48(p);
    sub_800200F8(p);
}
// Matched
void sub_8001F9F0(char* o)
{
    unsigned int f = *(unsigned int*)(o + 4);
    if (f & 1)
    {
        if (f & 2)
        {
            *(short*)(o + 0x26) += *(short*)(o + 0x28);
            if (*(short*)(o + 0x2A) < *(short*)(o + 0x26))
            {
                *(short*)(o + 0x26) = *(short*)(o + 0x2A);
                *(unsigned int*)(o + 4) &= ~3;
            }
        }
        else
        {
            *(short*)(o + 0x26) -= *(short*)(o + 0x28);
            if (*(short*)(o + 0x26) < *(short*)(o + 0x2A))
            {
                *(short*)(o + 0x26) = *(short*)(o + 0x2A);
                *(unsigned int*)(o + 4) &= ~1;
            }
        }
    }
    *(int*)(o + 0x2C) = *(int*)(o + 0x138) * *(short*)(o + 0x26) / 4096;
    *(int*)(o + 0x30) = *(int*)(o + 0x13C) * *(short*)(o + 0x26) / 4096;
    *(int*)(o + 0x34) = *(int*)(o + 0x140) * *(short*)(o + 0x26) / 4096;
}
// Matched
void sub_8001FB00(char* o)
{
    unsigned int f = *(unsigned int*)(o + 4);
    int r = 0;
    int v;
    int w;
    *(int*)(o + 8) = 0;
    if (f & 0x780)
    {
        if (f & 0x80)
        {
            r = 0x10;
        }
        else if (f & 0x100)
        {
            r = 0x30;
        }
        else if (f & 0x200)
        {
            r = 0x50;
        }
        else if (f & 0x400)
        {
            r = 0x70;
        }
    }
    if (*(unsigned int*)(o + 4) & 0x40000000)
    {
        v = (asc_80084350 + 0xF8)[(*(short*)(o + 0xBC) * *(short*)(o + 0xBE) + 0x400) & 0xFFF];
        (*(short*)(o + 0xBC))++;
        *(int*)(o + 8) = r | 0x80 | (-((v + 0x1000) / 2) << 16);
    }
    if (*(unsigned int*)(o + 4) & 0x60)
    {
        v = *(short*)(o + 0x20) + 0x1000 / *(short*)(o + 0x22);
        if (v >= 0)
        {
            w = v;
            if (v > 0x1000)
            {
                w = 0x1000;
            }
        }
        else
        {
            w = 0;
        }
        *(short*)(o + 0x20) = w;
        if (*(unsigned int*)(o + 4) & 0x20)
        {
            *(int*)(o + 8) = r | 0x80 | ((0x1000 - *(short*)(o + 0x20)) << 16);
        }
        else
        {
            *(int*)(o + 8) = r | 0x80 | (*(short*)(o + 0x20) << 16);
        }
    }
    if (*(unsigned int*)(o + 4) & 0x800)
    {
        *(int*)(o + 8) |= (*(short*)(o + 0x15A) - *(short*)(o + 0x152)) << 8;
    }
}
// Matched
int sub_8001FC90(char* a0)
{
    SVECTOR v;
    long sxy;
    long p;
    long flag;
    v.vx = *(unsigned short*)(a0 + 0x38);
    v.vy = *(unsigned short*)(a0 + 0x3C);
    v.vz = *(unsigned short*)(a0 + 0x40);
    v.vx -= dword_8008D600[0].field_0;
    v.vy -= dword_8008D600[1].field_0;
    v.vz -= dword_8008D600[2].field_0;
    RotTransPers(&v, &sxy, &p, &flag);
    return flag >= 0;
}
extern int sub_80019CC4();
extern void sub_8001C440();
extern void sub_80047E28();
extern void sub_80046A58();
extern void sub_800459E4();
typedef struct
{
    char pad_0[0x184];
    int field_184;
} ActorTail_8001FD08;
// Matched
void sub_8001FD08(void* a0)
{
    char* o = (char*)a0;
    int v;
    char* t;
    unsigned long* ot;
    unsigned long* ot2;
    if (!(*(int*)(o + 4) & 0x2000) && sub_8001FC90(o))
    {
        v = sub_80019CC4((VECTOR*)(o + 0x38));
        *(char**)(o + 0x178) = *(char**)(*(char**)(o + 0x15C) + 0x54) + *(int*)(o + 0x9C) * 28;
        *(int*)(o + 0x164) = *(int*)(*(char**)(o + 0x15C) + 0x50);
        *(char**)(o + 0x168) = o + 0x38;
        *(char**)(o + 0x16C) = o + 0x5C;
        *(int*)(o + 0x170) = *(int*)(o + 0x134);
        *(int*)(o + 0x174) = *(int*)(o + 0x144);
        *(unsigned int*)(o + 0x17C) = *(unsigned int*)(o + 0x90) % **(unsigned int**)(o + 0x178);
        *(int*)(o + 0x180) = *(int*)(o + 8);
        *(char**)(o + 0x188) = o + 0x2C;
        ((ActorTail_8001FD08*)o)->field_184 = *(int*)(o + 0x1C4);
        if (unknownFlags_8008D678 & 0x10000)
        {
            ot = pOT_8008B4C8;
        }
        else
        {
            ot = pOT_8008D690;
        }
        *(unsigned long**)(o + 0x18C) = ot;
        if (*(int*)(o + 4) & 0x1000)
        {
            t = *(char**)(*(char**)(o + 0x15C) + 0x54);
        }
        else
        {
            t = 0;
        }
        if (*(int*)(o + 4) & 0x10)
        {
            sub_80047E28(o + 0x164, *(int*)(o + 0x174), *(char**)(*(char**)(o + 0x15C) + 0x54) + *(int*)(o + 0xA0) * 28,
                         *(unsigned int*)(o + 0x94) % *(unsigned int*)(*(char**)(*(char**)(o + 0x15C) + 0x54) + *(int*)(o + 0xA0) * 28),
                         0x1000 - *(int*)(o + 0xAC), (char*)stru_8008D534 + v * 24, t);
        }
        else
        {
            sub_80046A58(o + 0x164, (char*)stru_8008D534 + v * 24, t);
        }
        if (unknownFlags_8008D678 & 0x10000)
        {
            ot2 = pOT_8008B4C8;
        }
        else
        {
            ot2 = pOT_8008D690;
        }
        sub_800459E4(*(int*)(o + 0x134), *(char**)(o + 0x15C) + 0x5C, ot2, *(int*)(o + 8));
        sub_8001C440(*(int*)(o + 0x15C), *(int*)(o + 0x9C), *(unsigned int*)(o + 0x90) % **(unsigned int**)(o + 0x178));
    }
}
// Matched
void sub_8001FF48(char* o)
{
    int g;
    int f;
    *(int*)(o + 4) &= ~0x4000;
    if (!(*(int*)(o + 4) & 4))
    {
        *(short*)(o + 0x1C) += *(short*)(o + 0x1E);
        if (*(short*)(o + 0x1C) >= 0x1000)
        {
            *(short*)(o + 0x1C) -= 0x1000;
            (*(int*)(o + 0x90))++;
        }
        if (*(int*)(o + 0x90) == *(short*)(o + 0x1A))
        {
            *(int*)(o + 4) |= 0x4000;
        }
        else if (*(short*)(o + 0x1A) < *(int*)(o + 0x90))
        {
            *(int*)(o + 4) |= 8;
            *(int*)(o + 0x90) = *(short*)(o + 0x18);
        }
    }
    f = *(int*)(o + 4);
    if (f & 0x10)
    {
        if (f < 0)
        {
            *(int*)(o + 0xAC) += 0x111;
        }
        else
        {
            *(int*)(o + 0xAC) += 0x1000 / *(short*)(o + 0x24);
        }
        if (*(int*)(o + 0xAC) >= 0x1000)
        {
            g = *(int*)(o + 4) & ~0x10;
            *(int*)(o + 4) = g & 0x7FFFFFFF;
        }
        f = *(int*)(o + 4);
    }
    if (f & 0x2000000)
    {
        *(int*)(o + 4) = f & ~0x4000;
        if (++*(int*)(o + 0x98) >= **(int**)(o + 0x160))
        {
            *(int*)(o + 0x90) = *(short*)(o + 0x1A);
            *(int*)(o + 4) = (*(int*)(o + 4) & ~0x2000000) | 0x4008;
            *(int*)(o + 0x50) = *(int*)(o + 0x38);
            *(int*)(o + 0x54) = *(int*)(o + 0x3C);
            *(int*)(o + 0x58) = *(int*)(o + 0x40);
            if (*(int*)(o + 0xD4) & 4)
            {
                *(int*)(o + 4) |= 0x80000000;
                *(int*)(o + 0xD4) &= ~1;
            }
        }
    }
}
// Matched
void sub_800200F8(void* a0)
{
    char* o = a0;
    int i;
    if (*(int*)(o + 4) & 0x10000000)
    {
        if (**(short**)(o + 0x134) != -1)
        {
            i = 0;
            do
            {
                (*(MATRIX**)(o + 0x1C8))[i] = dword_80098188[i];
                i++;
            } while ((*(short**)(o + 0x134))[i * 4] != -1);
        }
    }
}
// Matched
void ClearModelAnimRefs_800201A4(void)
{
    int i;
    for (i = 0; i < 7; i++)
    {
        ClearModelAnimRef_800204AC(&modelAnimRefs_800919A0[i]);
    }
}
// Matched
int AddModelAnimRef_800201EC(int a0)
{
    int i;
    struct_obj_C* p = modelAnimRefs_800919A0;
    for (i = 0; i < 7; i++, p++)
    {
        if (a0 == p->field_0)
        {
            p->field_4++;
            return i;
        }
    }
    p = modelAnimRefs_800919A0;
    for (i = 0; i < 7; i++, p++)
    {
        if (p->field_0 == 0)
        {
            p->field_0 = a0;
            p->field_4 = 1;
            return i;
        }
    }
    return -1;
}
// Matched
void ReleaseModelAnimRef_80020278(int a0, int a1)
{
    int i;
    struct_obj_C* e = &modelAnimRefs_800919A0[a0];
    for (i = 0; i < 0x23; i++)
    {
        if ((e->field_8[i] >> a1) & 1)
        {
            ReleaseModelAnim_800203B0(a0, a1, i);
        }
    }
    if (--e->field_4 == 0)
    {
        ClearModelAnimRef_800204AC(e);
    }
}
// Matched
int RequestModelAnim_8002032C(int a0, int a1, int a2)
{
    struct_obj_C* e = &modelAnimRefs_800919A0[a0];
    unsigned short* s = (unsigned short*)((char*)e + a2 * 2);
    int r = 0;
    if (s[4] == 0)
    {
        LoadModelAnim_80025440(e->field_0, a2, r);
        r = 1;
    }
    s[4] |= 1 << a1;
    return r;
}
// Matched
void ReleaseModelAnim_800203B0(int a0, int a1, int a2)
{
    struct_obj_C* e = &modelAnimRefs_800919A0[a0];
    if ((e->field_8[a2] &= ~(1 << a1)) == 0)
    {
        FreeModelAnim_8002556C(e->field_0, a2);
    }
}
// Matched
int sub_80020410(int a0, int a1, int a2)
{
    struct_obj_C* e = &modelAnimRefs_800919A0[a0];
    int* list;
    int i;
    if (((e->field_8[a2] >> a1) & 1) == 0)
    {
        list = *(int**)(e->field_0 + 0x58);
        if (list != 0)
        {
            for (i = 0; i < list[0]; i++)
            {
                if (a2 == list[i + 1])
                {
                    return 1;
                }
            }
        }
        return 0;
    }
    return 1;
}
// Matched
void ClearModelAnimRef_800204AC(struct_obj_C* p)
{
    int i;
    for (i = 0x22; i >= 0; i--)
    {
        p->field_8[i] = 0;
    }
    p->field_0 = 0;
    p->field_4 = 0;
}
// Matched
void ResetModelLoader_800204D0(void)
{
    int* p = (int*)modelLoaderTask_8008B54C[9];
    int* q = p + 3;
    int i;
    p[0] = 0;
    p[1] = 1;
    p[2] = 0;
    for (i = 0; i < 4; i++)
    {
        q[0] = 0;
        q[1] = -1;
        q[2] = 0;
        q[3] = 0;
        q[4] = -1;
        q += 5;
    }
}
// Matched
void FreeModelLoaderList_8002052C(void)
{
    int* p = modelLoaderTask_8008B54C[0x24 / 4];
    if (p[2])
    {
        FreeModelList_80024BB0(p + 2);
    }
}
// Matched
void StartModelLoader_8002056C(void)
{
    struct_cb* q = (struct_cb*)((char*)modelLoaderTask_8008B54C + 0x10);
    q->fn_8 = ModelLoaderTask_800209AC;
    q->flags_0 = (q->flags_0 | 1) & ~0x8000;
    *q->field_14 = 0;
    q->fn_8(q, q->field_14);
}
// Matched
int IsModelLoaderDone_800205D0(void)
{
    return modelLoaderTask_8008B54C[0x24 / 4][1];
}
// Matched
void StopModelLoader_800205F0(void)
{
    int* n = (int*)modelLoaderTask_8008B54C;
    n[4] = (n[4] & ~1) | 0x8000;
}
// Matched
int CountLoaderModels_80020614(void)
{
    int* p = modelLoaderTask_8008B54C[9];
    struct_20* e = (struct_20*)(p + 3);
    int count = 0;
    int i;
    for (i = 0; i < 4; i++)
    {
        if (e->field_4 >= 0)
        {
            count++;
        }
        e++;
    }
    return count;
}
// Matched
int GetLoaderModelId_80020654(int k)
{
    int* p = modelLoaderTask_8008B54C[9];
    struct_20* e = (struct_20*)(p + 3);
    int n = 0;
    int i;
    for (i = 0; i < 4; i++)
    {
        if (e->field_4 >= 0)
        {
            if (n == k)
            {
                return e->field_4;
            }
            n++;
        }
        e++;
    }
    return -1;
}
// Matched
int RequestLoaderModel_800206A0(int id, int a1, int a2, int a3)
{
    int* p = modelLoaderTask_8008B54C[9];
    struct_20* e = (struct_20*)(p + 3);
    int i;
    for (i = 0; i < 4; i++)
    {
        if (id == e->field_4)
        {
            return 1;
        }
        e++;
    }
    e = (struct_20*)(p + 3);
    for (i = 0; i < 4; i++)
    {
        if (e->field_4 == -1)
        {
            e->field_0 = 0;
            e->field_4 = id;
            e->field_8 = a1;
            e->field_C = a2;
            e->field_10 = a3;
            p[1] = 0;
            return 1;
        }
        e++;
    }
    return 0;
}
// Matched
struct_112* AcquireLoaderModel_80020734(int arg)
{
    return AcquireModel_80024D70(modelLoaderTask_8008B54C[0x24 / 4][2], arg);
}
// Matched
void FreeLoaderModel_80020768(int a0)
{
    int* base = (int*)modelLoaderTask_8008B54C[9];
    int* p = base + 4;
    int i;
    for (i = 0; i < 4; i++)
    {
        if (p[0] >= 0 && p[3] >= 0)
        {
            if (a0 == AcquireModel_80024D70(base[2], p[0]))
            {
                FreeModel_80024C48(a0);
                p[0] = -1;
                return;
            }
        }
        p += 5;
    }
}
// Matched
void FreeLoaderModelAnimSets_80020814(void)
{
    int* base = (int*)modelLoaderTask_8008B54C[9];
    int* p = base + 7;
    int i;
    for (i = 0; i < 4; i++)
    {
        if (p[-3] >= 0 && p[0] >= 0)
        {
            FreeModelAnimSet_80025884(AcquireModel_80024D70(base[2], p[-3]));
        }
        p += 5;
    }
}
// Matched
void LoadLoaderModelAnimSets_80020898(void)
{
    int* base = (int*)modelLoaderTask_8008B54C[9];
    int* p = base + 7;
    int i;
    for (i = 0; i < 4; i++)
    {
        if (p[-3] >= 0 && p[0] >= 0)
        {
            LoadModelAnimSet_80025780(AcquireModel_80024D70(base[2], p[-3]), p[0], 1);
        }
        p += 5;
    }
}
// Matched
int AreLoaderModelsLoaded_80020924(void)
{
    int* base = (int*)modelLoaderTask_8008B54C[9];
    int* p = base + 3;
    int i;
    for (i = 0; i < 4; i++)
    {
        if (p[1] >= 0)
        {
            if (AreFileRequestsDone_80024DC4(AcquireModel_80024D70(base[2], p[1])) == 0)
            {
                return 0;
            }
        }
        p += 5;
    }
    return 1;
}
// Matched
void ModelLoaderTask_800209AC(struct_cb* p, int* a1)
{
    int* q = a1;
    int s = q[0];
    int t;
    switch (s)
    {
    case 0:
        LoadRequestedModels_80020A38(q);
        t = q[0];
        eventDispatchHalt_8008B540 = 1;
        q[0] = t + 1;
        break;
    case 1:
        if (AreRequestedModelsLoaded_80020B70(q))
        {
            StopModelLoader_800205F0();
        }
        eventDispatchHalt_8008B540 = s;
        break;
    }
}
// Matched
void LoadRequestedModels_80020A38(int* p)
{
    struct_20* e;
    int i;
    if (p[2] == 0)
    {
        InitModelList_80024ADC(&p[2], off_8007DC70, 1);
    }
    e = (struct_20*)(p + 3);
    for (i = 0; i < 4; i++)
    {
        if (e->field_4 >= 0 && e->field_0 == 0)
        {
            LoadModel_80025200(p[2], e->field_4, e->field_8, e->field_C, 1);
        }
        e++;
    }
    e = (struct_20*)(p + 3);
    for (i = 0; i < 4; i++)
    {
        if (e->field_4 >= 0 && e->field_0 == 0)
        {
            if (e->field_10 >= 0)
            {
                LoadModelAnimSet_80025780(AcquireModel_80024D70(p[2], e->field_4), e->field_10, 1);
            }
            e->field_0 = 1;
        }
        e++;
    }
}
// Matched
int AreRequestedModelsLoaded_80020B70(int* a0)
{
    int* p = a0 + 3;
    int i;
    for (i = 0; i < 4; i++)
    {
        if (p[0] != 0)
        {
            if (AreFileRequestsDone_80024DC4(AcquireModel_80024D70(a0[2], p[1])) == 0)
            {
                return 0;
            }
        }
        p += 5;
    }
    a0[1] = 1;
    return 1;
}
// Matched
int LoadOverlay_80020BF8(unsigned int mode, enum OverlayIds overlayIdx)
{
    int req[8];
    switch (mode)
    {
    case 0:
        req[0] = 0x22;
        break;
    case 2:
        DATA_ReadFileInto_8003CAEC(overlays_8007D9E8[overlayIdx].fileIdx, *overlays_8007D9E8[overlayIdx].ppDest);
        return -1;
    case 1:
    case 3:
        req[0] = 0x2A;
        break;
    }
    req[1] = overlays_8007D9E8[overlayIdx].fileIdx;
    req[2] = 0;
    req[3] = 0;
    req[4] = (int)*overlays_8007D9E8[overlayIdx].ppDest;
    req[5] = 0;
    req[6] = 0;
    req[7] = 0;
    return QueueFileRequest_8003BC84(req);
}
// Matched
void InitOverlayLoaderTask_80020CB8(struct_cb* p, int* q)
{
    q[1] = -1;
    q[0] = 0x1D;
    p->fn_8 = (void (*)(struct struct_cb*, int*))UpdateOverlayLoaderTask_80020CD8;
}
// Matched
void UpdateOverlayLoaderTask_80020CD8(int a0, int* p)
{
    if (p[0] != p[1])
    {
        p[1] = p[0];
        p[2] = LoadOverlay_80020BF8(2, p[0]);
    }
}
#if 0
// Not matched
int LoadOverlayIfChanged_80020D1C(int a0, int a1)
{
    int* p = overlayLoaderTask_8008D4C0[9];
    if (p[0] == a1)
    {
        return -1;
    }
    p[0] = a1;
    p[1] = a1;
    return LoadOverlay_80020BF8(a0, a1);
}
#endif
INCLUDE_ASM(LoadOverlayIfChanged_80020D1C);
// Matched
void ResetOverlayLoaderTask_80020D68(void)
{
    *overlayLoaderTask_8008D4C0[0x24 / 4] = 0x1D;
}
// Matched
int sub_80020D84(void)
{
    int* p = overlayLoaderTask_8008D4C0[9];
    int r;
    if (p[0] == 0x1D)
    {
        r = GetFileRequestStatus_8003BE30(p[2]) == 0;
    }
    else
    {
        ResetOverlayLoaderTask_80020D68();
        r = 0;
    }
    return r;
}
// Matched
void LoadEffectFile_80020DDC(int a0, int* out, short* a2, short* a3, int a4, int a5)
{
    int req[8];
    struct
    {
        int* out;
        short a[2];
        short b[2];
        short c[2];
        int d;
    } arg;
    arg.out = out;
    arg.a[0] = a2[0];
    arg.a[1] = a2[1];
    arg.b[0] = a3[0];
    arg.b[1] = a3[1];
    arg.c[0] = a3[0];
    arg.c[1] = a3[1];
    arg.d = a4;
    ListInit_8003FDB0(out + 1);
    req[0] = 0x28;
    if (a5)
    {
        req[0] |= 4;
    }
    else
    {
        req[0] |= 1;
    }
    req[1] = a0;
    req[2] = 0;
    req[3] = 0;
    req[4] = 0;
    req[5] = (int)&arg;
    req[6] = 0x14;
    req[7] = (int)OnEffectFileLoaded_80020F5C;
    *out = StartFileRequestTask_8003C6C8(req);
}
// Matched
int IsEffectFileLoaded_80020EBC(int* p)
{
    return GetFileRequestStatus_8003BE30(*p) == 0;
}
// Matched
void FreeEffectFile_80020EE0(int* p)
{
    ListFreeAll_8003FEC8(p + 1);
}
// Matched
int sub_80020F00(struct_list_14* p, int a, int b)
{
    int i;
    for (i = 0; i < p->count; i++)
    {
        if (p->items[i].field_0 == a && p->items[i].field_4 == b)
        {
            return p->items[i].field_8;
        }
    }
    return -1;
}
void sub_80021298(int* src, int* out, int a2, int a3, int heap);
void sub_80021464(int* hdr, int* out, int a2, int a3, int heap);
int LoadMdecImages_800215E8(int* hdr, int* out, int heap);
void sub_800216E8(int* a0, int a1, int a2);
typedef struct
{
    int a;
    int b;
    int c;
} struct_3i;
// Matched
void OnEffectFileLoaded_80020F5C(int* arg_in, int* hdr)
{
    int* arg = arg_in;
    int* out = (int*)arg[0];
    int* p1 = (int*)((char*)hdr + hdr[1]);
    int* p2 = (int*)((char*)hdr + hdr[2]);
    int* p3 = (int*)((char*)hdr + hdr[3]);
    int* p4 = (int*)((char*)hdr + hdr[4]);
    int* p5 = (int*)((char*)hdr + hdr[5]);
    int* p6 = (int*)((char*)hdr + hdr[6]);
    int i;
    int max;
    int r;
    int n;
    int* src;
    out[5] = 0;
    out[7] = 0;
    out[9] = 0;
    out[11] = 0;
    out[4] = (int)ListAlloc_8003FDC0(out + 1, p1[0]);
    MemCopy_800403E8((unsigned int*)out[4], (unsigned int*)(p1 + 1), p1[0]);
    n = p2[0];
    if (n)
    {
        out[5] = n;
        out[6] = (int)ListAlloc_8003FDC0(out + 1, n * 12);
        src = p2 + 1;
        for (i = 0; i < out[5]; i++)
        {
            ((struct_3i*)out[6])[i].a = src[0];
            ((struct_3i*)out[6])[i].b = src[1];
            ((struct_3i*)out[6])[i].c = src[2];
            src += 3;
        }
    }
    n = p3[0];
    if (n)
    {
        out[7] = n;
        out[8] = (int)ListAlloc_8003FDC0(out + 1, n * 0x34);
        for (i = 0; i < out[7]; i++)
        {
            int* d = (int*)(out[8] + i * 0x34);
            sub_80021298((int*)((char*)p3 + p3[i + 1]), d, (int)(arg + 1), arg[4], (int)(out + 1));
        }
    }
    n = p4[0];
    if (n)
    {
        out[9] = n;
        out[10] = (int)ListAlloc_8003FDC0(out + 1, n * 0x1C);
        for (i = 0; i < out[9]; i++)
        {
            int* d = (int*)(out[10] + i * 0x1C);
            sub_80021464((int*)((char*)p4 + p4[i + 1]), d, (int)(arg + 1), arg[4], (int)(out + 1));
        }
    }
    n = p5[0];
    if (n)
    {
        out[11] = n;
        out[12] = (int)ListAlloc_8003FDC0(out + 1, n * 8);
        i = 0;
        max = i;
        for (; i < out[11]; i++)
        {
            r = LoadMdecImages_800215E8((int*)((char*)p5 + p5[i + 1]), (int*)(out[12] + i * 8), (int)(out + 1));
            if (max < r)
            {
                max = r;
            }
        }
        sub_800216E8(out + 13, max, (int)(out + 1));
    }
    if (GetTiyFileCount_80028E68(p6))
    {
        LoadTiyTimsRelocated_80028FDC(0, 0, 0, (int)p6, GetTiyFileCount_80028E68(p6), (int)(arg + 1), arg[4]);
    }
}
typedef struct
{
    unsigned char b[4];
} struct_b4;
typedef struct
{
    unsigned char b[8];
} struct_b8;
typedef struct
{
    struct_b4 f0;
    struct_b4 f4;
    struct_b4 f8;
    struct_b4 fC;
    struct_b8 f10;
    struct_b4 f18;
} struct_1c;
// Matched
void sub_80021298(int* src, int* out, int a2, int a3, int heap)
{
    int buf[10];
    int i;
    int j;
    int n;
    struct_1c* d;
    struct_1c* s;
    out[0] = *src++;
    out[1] = (int)ListAlloc_8003FDC0(heap, out[0]);
    out[2] = (int)ListAlloc_8003FDC0(heap, out[0] * 4);
    for (i = 0; i < out[0]; i++)
    {
        n = *src++;
        s = (struct_1c*)src;
        d = (struct_1c*)ListAlloc_8003FDC0(heap, n * 28);
        ((unsigned char*)out[1])[i] = n;
        ((struct_1c**)out[2])[i] = d;
        for (j = 0; j < ((unsigned char*)out[1])[i]; j++)
        {
            d->f0 = s->f0;
            d->f4 = s->f4;
            d->f8 = s->f8;
            d->fC = s->fC;
            d->f10 = s->f10;
            d->f18 = s->f18;
            d++;
            s++;
        }
        src = (int*)s;
    }
    MemCopy_800403E8((unsigned int*)buf, (unsigned int*)src, 0x28);
    InitPolyFT4_80029A10(out + 3, buf);
}
// Matched
void sub_80021464(int* hdr, int* out, int a2, int a3, int heap)
{
    int* models = (int*)((char*)hdr + hdr[1]);
    int* images = (int*)((char*)hdr + hdr[2]);
    if (GetFtgObjectCount_80021738(models))
    {
        out[0] = GetFtgObjectCount_80021738(models);
        AllocFtgObjects_80021744(&out[1], out[0], heap);
        LoadFtgObjects_80021824(models, (char*)out[1], out[0], heap, a2);
    }
    if (sub_80021DE4(models))
    {
        sub_80021DF0(&out[2], sub_80021DE4(models), heap);
        sub_80021E4C(models, &out[2], sub_80021DE4(models));
    }
    else
    {
        out[2] = 0;
    }
    out[4] = 0;
    out[5] = 0;
    out[6] = 0;
    if (images[0] && images[1])
    {
        out[4] = images[0];
        out[5] = images[1];
        out[6] = (int)ListAlloc_8003FDC0(heap, images[0] * 40 * images[1]);
        MemCopy_800403E8((unsigned int*)out[6], (unsigned int*)(images + 2), images[0] * 40 * images[1]);
    }
}
// Matched
int LoadMdecImages_800215E8(int* hdr, int* out, int heap)
{
    int i;
    int max;
    int size;
    unsigned long* src;
    int n;
    int count = hdr[0];
    out[0] = count;
    out[1] = (int)ListAlloc_8003FDC0(heap, count * 4);
    i = 0;
    max = i;
    for (; i < out[0]; i++)
    {
        size = hdr[i * 2 + 2];
        src = (unsigned long*)((char*)hdr + hdr[i * 2 + 1]);
        ((int*)out[1])[i] = (int)ListAlloc_8003FDC0(heap, size);
        MemCopy_800403E8((unsigned int*)((int*)out[1])[i], (unsigned int*)src, size);
        n = DecDCTBufSize(src);
        if (max < n)
        {
            max = n;
        }
    }
    return max;
}
// Matched
void sub_800216E8(int* a0, int a1, int a2)
{
    a0[0] = ListAlloc_8003FDC0(a2, (a1 + 1) * 4);
    a0[1] = ListAlloc_8003FDC0(a2, 0x2000);
}
// Matched
int GetFtgObjectCount_80021738(int* p)
{
    return p[1];
}
// Matched
void AllocFtgObjects_80021744(int* p, int idx, int a2)
{
    *p = HeapAlloc_8003FC8C(idx * 0x54, a2);
}
// Matched
void FreeFtgObjects_80021784(int** a0, unsigned int n, int heap)
{
    char* p = (char*)*a0;
    unsigned int i;
    for (i = 0; i < n; i++)
    {
        FreeFtgObject_800229B0((int*)p, heap);
        p += 0x54;
    }
    HeapFree_8003FD18(*a0, heap);
    *a0 = 0;
}
// Matched
void sub_80021804(int* p, int heap)
{
    FreeFtgObject_800229B0(p, heap);
}
// Matched
void LoadFtgObjects_80021824(int* a0, char* a1, int a2, int a3, int a4)
{
    unsigned int n = GetFtgObjectCount_80021738(a0);
    int r = (int)(a0 + 4);
    unsigned int i;
    for (i = 0; i < n; i++)
    {
        r = LoadFtgObject_80022458(a1, r, a3, a4);
        a1 += 0x54;
    }
}
typedef struct
{
    short n;
    short pad;
    char* p;
} ModelList;
typedef struct
{
    ModelList l[8];
    int n8;
    char* p8;
    int n9;
    unsigned short f4C;
    unsigned short f4E;
    char* p9;
} Model54;
#define S ((Model54*)a0)
#define D ((Model54*)a1)
// Matched
void sub_800218A8(int a0, void* a1, int a2)
{
    char* buf;
    int size;
    int i;
    size = S->l[0].n * 0x24 + S->l[1].n * 0x3C;
    size += S->l[2].n * 0x30;
    size += S->l[3].n * 0x48;
    size += S->l[4].n * 0x2C;
    size += S->l[5].n * 0x50;
    size += S->l[6].n * 0x38;
    size += S->l[7].n * 0x5C;
    size += S->n8 * 0x14;
    size += S->n9 * 0x14;
    if (size)
    {
        buf = (char*)HeapAlloc_8003FC8C(size, (struct Pool*)a2);
    }
    else
    {
        buf = 0;
    }
    D->l[0].n = S->l[0].n;
    D->l[0].p = buf;
    buf += S->l[0].n * 0x24;
    D->l[1].n = S->l[1].n;
    D->l[1].p = buf;
    buf += S->l[1].n * 0x3C;
    D->l[2].n = S->l[2].n;
    D->l[2].p = buf;
    buf += S->l[2].n * 0x30;
    D->l[3].n = S->l[3].n;
    D->l[3].p = buf;
    buf += S->l[3].n * 0x48;
    D->l[4].n = S->l[4].n;
    D->l[4].p = buf;
    buf += S->l[4].n * 0x2C;
    D->l[5].n = S->l[5].n;
    D->l[5].p = buf;
    buf += S->l[5].n * 0x50;
    D->l[6].n = S->l[6].n;
    D->l[6].p = buf;
    buf += S->l[6].n * 0x38;
    D->l[7].n = S->l[7].n;
    D->l[7].p = buf;
    buf += S->l[7].n * 0x5C;
    D->n8 = S->n8;
    D->p8 = buf;
    buf += S->n8 * 0x14;
    D->n9 = S->n9;
    D->p9 = buf;
    for (i = 0; i < D->l[0].n; i++)
    {
        MemCopy_800403E8((unsigned int*)(D->l[0].p + i * 0x24), (unsigned int*)(S->l[0].p + i * 0x24), 0x24);
    }
    for (i = 0; i < D->l[1].n; i++)
    {
        MemCopy_800403E8((unsigned int*)(D->l[1].p + i * 0x3C), (unsigned int*)(S->l[1].p + i * 0x3C), 0x3C);
    }
    for (i = 0; i < D->l[2].n; i++)
    {
        MemCopy_800403E8((unsigned int*)(D->l[2].p + i * 0x30), (unsigned int*)(S->l[2].p + i * 0x30), 0x30);
    }
    for (i = 0; i < D->l[3].n; i++)
    {
        MemCopy_800403E8((unsigned int*)(D->l[3].p + i * 0x48), (unsigned int*)(S->l[3].p + i * 0x48), 0x48);
    }
    for (i = 0; i < D->l[4].n; i++)
    {
        MemCopy_800403E8((unsigned int*)(D->l[4].p + i * 0x2C), (unsigned int*)(S->l[4].p + i * 0x2C), 0x2C);
    }
    for (i = 0; i < D->l[5].n; i++)
    {
        MemCopy_800403E8((unsigned int*)(D->l[5].p + i * 0x50), (unsigned int*)(S->l[5].p + i * 0x50), 0x50);
    }
    for (i = 0; i < D->l[6].n; i++)
    {
        MemCopy_800403E8((unsigned int*)(D->l[6].p + i * 0x38), (unsigned int*)(S->l[6].p + i * 0x38), 0x38);
    }
    for (i = 0; i < D->l[7].n; i++)
    {
        MemCopy_800403E8((unsigned int*)(D->l[7].p + i * 0x5C), (unsigned int*)(S->l[7].p + i * 0x5C), 0x5C);
    }
    for (i = 0; i < D->n8; i++)
    {
        MemCopy_800403E8((unsigned int*)(D->p8 + i * 0x14), (unsigned int*)(S->p8 + i * 0x14), 0x14);
    }
    for (i = 0; i < D->n9; i++)
    {
        MemCopy_800403E8((unsigned int*)(D->p9 + i * 0x14), (unsigned int*)(S->p9 + i * 0x14), 0x14);
    }
    D->f4C = S->f4C;
    D->f4E = S->f4E;
}
#undef S
#undef D
// Matched
int sub_80021DE4(int* p)
{
    return p[2];
}
// Matched
void sub_80021DF0(int* p, int a1, int a2)
{
    p[0] = a1;
    p[1] = HeapAlloc_8003FC8C(a1 * 16, a2);
}
// Matched
// p is volatile to keep the store before the load
void sub_80021E24(volatile int* p, int h)
{
    p[0] = 0;
    HeapFree_8003FD18(p[1]);
}
// Matched
void sub_80021E4C(int* a0, int* a1, unsigned int n)
{
    unsigned short* src = (unsigned short*)((char*)a0 + a0[3]);
    unsigned int i;
    for (i = 0; i < n; i++)
    {
        unsigned short* dst = (unsigned short*)((char*)a1[1] + i * 16);
        dst[0] = src[0];
        dst[1] = src[1];
        dst[2] = src[2];
        dst[3] = src[3];
        dst[4] = src[4];
        dst[5] = src[5];
        dst[6] = src[6];
        dst[7] = src[7];
        src += 8;
    }
}
// r2 is unused (the original frame has room for it)
// Matched
void sub_80021EDC(unsigned char* p, unsigned char* d)
{
    RECT r;
    RECT r2;
    r.x = p[4];
    r.y = p[5];
    r.w = p[0xE];
    r.h = p[0xF];
    if (p[8] < r.x)
    {
        r.x = p[8];
    }
    if (r.x > p[0xC])
    {
        r.x = p[0xC];
    }
    if (r.x > p[0xE])
    {
        r.x = p[0xE];
    }
    if (p[9] < r.y)
    {
        r.y = p[9];
    }
    if (r.y > p[0xD])
    {
        r.y = p[0xD];
    }
    if (r.y > p[0xF])
    {
        r.y = p[0xF];
    }
    if (r.w < p[0xC])
    {
        r.w = p[0xC];
    }
    if (r.w < p[8])
    {
        r.w = p[8];
    }
    if (r.w < p[4])
    {
        r.w = p[4];
    }
    if (r.h < p[0xD])
    {
        r.h = p[0xD];
    }
    if (r.h < p[9])
    {
        r.h = p[9];
    }
    if (r.h < p[5])
    {
        r.h = p[5];
    }
    d[3] = 9;
    d[7] = 0x2C;
    d[4] = p[0];
    d[5] = p[1];
    d[6] = p[2];
    d[0xC] = r.x;
    d[0xD] = r.y;
    d[0x14] = r.w;
    d[0x15] = r.y;
    d[0x1C] = r.x;
    d[0x1D] = r.h;
    d[0x24] = r.w;
    d[0x25] = r.h;
    *(short*)(d + 8) = 0;
    *(short*)(d + 0xA) = 0;
    *(short*)(d + 0x10) = r.w - r.x;
    *(short*)(d + 0x12) = 0;
    *(short*)(d + 0x18) = 0;
    *(short*)(d + 0x1A) = r.h - r.y;
    *(short*)(d + 0x20) = r.w - r.x;
    *(short*)(d + 0x22) = r.h - r.y;
    d[7] = p[3];
    *(unsigned short*)(d + 0x16) = *(unsigned short*)(p + 0xA);
    *(unsigned short*)(d + 0xE) = *(unsigned short*)(p + 6);
}
// Matched
void sub_800221DC(unsigned char* p, unsigned char* d, DR_TPAGE* tp)
{
    RECT r;
    r.x = p[4];
    r.y = p[5];
    r.w = p[0xE];
    r.h = p[0xF];
    if (p[8] < r.x)
    {
        r.x = p[8];
    }
    if (r.x > p[0xC])
    {
        r.x = p[0xC];
    }
    if (r.x > p[0xE])
    {
        r.x = p[0xE];
    }
    if (p[9] < r.y)
    {
        r.y = p[9];
    }
    if (r.y > p[0xD])
    {
        r.y = p[0xD];
    }
    if (r.y > p[0xF])
    {
        r.y = p[0xF];
    }
    if (r.w < p[0xC])
    {
        r.w = p[0xC];
    }
    if (r.w < p[8])
    {
        r.w = p[8];
    }
    if (r.w < p[4])
    {
        r.w = p[4];
    }
    if (r.h < p[0xD])
    {
        r.h = p[0xD];
    }
    if (r.h < p[9])
    {
        r.h = p[9];
    }
    if (r.h < p[5])
    {
        r.h = p[5];
    }
    d[3] = 4;
    d[7] = 0x64;
    d[4] = p[0];
    d[5] = p[1];
    d[6] = p[2];
    d[0xC] = r.x;
    d[0xD] = r.y;
    *(short*)(d + 8) = 0;
    *(short*)(d + 0xA) = 0;
    *(short*)(d + 0x10) = r.w - r.x;
    *(short*)(d + 0x12) = r.h - r.y;
    *(unsigned short*)(d + 0xE) = *(unsigned short*)(p + 6);
    SetDrawTPage(tp, 0, 1, *(unsigned short*)(p + 0xA));
}
typedef void (*fn_80022458_a)(unsigned char* p, int a3);
typedef int (*fn_80022458_b)(unsigned char* hdr, unsigned char* p, int a0, int k, int h);
extern fn_80022458_a ftgPrimRelocators_8007DB08[];
extern fn_80022458_b ftgPrimLoaders_8007DAE0[];
typedef struct
{
    short n;
    short pad;
    int p;
} struct_22634;
void sub_80022B84(int* c, int* x, int* y);
int sub_80022634(struct_22634* out, int* c, int h);
int sub_8002300C(unsigned char* hdr, unsigned char* p, int* a, int k, int h);
int sub_8002320C(unsigned char* hdr, unsigned char* p, int* b, int k, int h);
typedef struct struct_22CC4 struct_22CC4;
void sub_80022CC4(struct_22CC4* a0, struct_22634* a, struct_22634* b, int h);
// Matched
int LoadFtgObject_80022458(int a0, unsigned char* a1, int h, int a3)
{
    int cnt[10];
    int A[2];
    int B[2];
    unsigned int i;
    unsigned int n;
    unsigned char* hdr;
    unsigned char* p;
    unsigned int type;
    unsigned int j;
    int k;
    for (j = 0; j < 10; j++)
    {
        cnt[j] = 0;
    }
    hdr = a1;
    a1 += 0x28;
    n = sub_80022634((struct_22634*)a0, (int*)hdr, h);
    sub_800228F8(A, B, (char*)hdr, h);
    for (i = 0; i < n; i++)
    {
        p = a1;
        a1 += 4;
        type = *p;
        k = cnt[type];
        cnt[type] = k + 1;
        if (a3 != 0 && ftgPrimRelocators_8007DB08[type] != 0)
        {
            ftgPrimRelocators_8007DB08[type](a1, a3);
        }
        switch (type)
        {
        case 0:
        case 1:
        case 2:
        case 3:
        case 4:
        case 5:
        case 6:
        case 7:
            a1 += ftgPrimLoaders_8007DAE0[type](p, a1, a0, k, h);
            break;
        case 8:
            a1 += sub_8002300C(p, a1, A, k, h);
            break;
        case 9:
            a1 += sub_8002320C(p, a1, B, k, h);
            break;
        }
    }
    sub_80022CC4((struct_22CC4*)a0, (struct_22634*)A, (struct_22634*)B, h);
    sub_800229E0(A, B, h);
    return (int)a1;
}
// Matched
int sub_80022634(struct_22634* out, int* c, int h)
{
    int x;
    int y;
    int size;
    int total;
    char* p;
    p = 0;
    sub_80022B84(c, &x, &y);
    size = c[0] * 0x24 + c[1] * 0x3C;
    total = c[0] + c[1];
    size += c[2] * 0x30;
    total += c[2];
    size += c[3] * 0x48;
    total += c[3];
    size += c[4] * 0x2C;
    total += c[4];
    size += c[5] * 0x50;
    total += c[5];
    size += c[6] * 0x38;
    total += c[6];
    size += c[7] * 0x5C;
    total += c[7];
    size += x * 0x14;
    total += c[8];
    size += y * 0x14;
    total += c[9];
    if (size != 0)
    {
        p = (char*)HeapAlloc_8003FC8C(size, h);
    }
    out[0].n = c[0];
    out[0].p = (int)p;
    p += c[0] * 0x24;
    out[1].n = c[1];
    out[1].p = (int)p;
    p += c[1] * 0x3C;
    out[2].n = c[2];
    out[2].p = (int)p;
    p += c[2] * 0x30;
    out[3].n = c[3];
    out[3].p = (int)p;
    p += c[3] * 0x48;
    out[4].n = c[4];
    out[4].p = (int)p;
    p += c[4] * 0x2C;
    out[5].n = c[5];
    out[5].p = (int)p;
    p += c[5] * 0x50;
    out[6].n = c[6];
    out[6].p = (int)p;
    p += c[6] * 0x38;
    out[7].n = c[7];
    out[7].p = (int)p;
    p += c[7] * 0x5C;
    ((int*)out)[0x40 / 4] = x;
    ((int*)out)[0x44 / 4] = (int)p;
    p += x * 0x14;
    ((int*)out)[0x48 / 4] = y;
    ((int*)out)[0x50 / 4] = (int)p;
    return total;
}
typedef struct
{
    unsigned short count;
    int ptr;
} struct_cnt_ptr;
// Matched
int sub_800228F8(struct_cnt_ptr* a0, struct_cnt_ptr* a1, int* a2, int heap)
{
    int n;
    int m;
    a0->count = a2[8];
    n = a2[8];
    if (n)
    {
        a0->ptr = HeapAlloc_8003FC8C(n << 3, (struct Pool*)heap);
    }
    else
    {
        a0->ptr = 0;
    }
    a1->count = a2[9];
    m = a2[9];
    n += m;
    if (m)
    {
        a1->ptr = HeapAlloc_8003FC8C(m * 12, (struct Pool*)heap);
    }
    else
    {
        a1->ptr = 0;
    }
    return n;
}
// Matched
void FreeFtgObject_800229B0(int* p, int heap)
{
    int a = p[1];
    if (a)
    {
        HeapFree_8003FD18(a, heap);
    }
}
// Matched
void sub_800229E0(int* a0, int* a1, int h)
{
    int i;
    if (a0[1] != 0)
    {
        for (i = 0; i < *(short*)a0; i++)
        {
            if (((int*)a0[1])[i * 2 + 1] != 0)
            {
                HeapFree_8003FD18(((int*)a0[1])[i * 2 + 1], h);
            }
        }
        HeapFree_8003FD18(a0[1], h);
    }
    if (a1[1] != 0)
    {
        for (i = 0; i < *(short*)a1; i++)
        {
            if (((struct_12*)a1[1])[i].field_8 != 0)
            {
                HeapFree_8003FD18(((struct_12*)a1[1])[i].field_8, h);
            }
        }
        HeapFree_8003FD18(a1[1], h);
    }
}
// Matched
void RelocateTPageClut_80022AE8(unsigned short* a0, unsigned short* a1, short* a2)
{
    int u = a2[0] / 64;
    int v = a2[1] / 256;
    int tp = v * 16 + u;
    unsigned short t = *a1;
    u = (t & 0x3F) * 16;
    v = (t >> 6) & 0x1FF;
    if (((*a0 >> 7) & 3) == 0)
    {
        u += a2[2];
        v += a2[3];
    }
    else
    {
        u += a2[4];
        v += a2[5];
    }
    *a0 += tp;
    *a1 = v * 64 + (u >> 4);
}
typedef struct
{
    unsigned char b0;
    unsigned char b1;
    unsigned char b2;
    unsigned char b3;
    unsigned short f4;
    unsigned short f6;
    unsigned short f8;
    unsigned short fA;
    unsigned short fC;
    unsigned short fE;
    unsigned short f10;
    unsigned short f12;
} struct_20_b;
typedef struct
{
    int count;
    struct_20_b* items;
} struct_8_20b;
typedef struct
{
    int count;
    unsigned short f4;
    unsigned short f6;
    struct_20_b* items;
} struct_12_20b;
#if 0
// Not matched: the original copies c/q/k into extra registers (looks like inlined helpers) and keeps q+4/q+8 unfolded; needs its jump table split out of dword_800740B4 (keep 0x68 of its 0x90 bytes)
void sub_80022B84(int* c, int* x, int* y)
{
    int n;
    int i;
    int a;
    int b;
    int k;
    int* r;
    unsigned char* q;
    unsigned char* t;
    a = 0;
    q = (unsigned char*)c;
    r = (int*)q;
    q += 0x28;
    n = r[0] + r[1] + r[2] + r[3] + r[4] + r[5] + r[6] + r[7] + r[8] + r[9];
    b = 0;
    for (i = 0; i < n; i++)
    {
        t = q;
        q += 4;
        switch (*t)
        {
        case 1:
            q += 0x3C;
            break;
        case 0:
        case 2:
            q += 0x24;
            break;
        case 3:
            q += 0x40;
            break;
        case 5:
            q += 0x50;
            break;
        case 4:
        case 6:
            q += 0x2C;
            break;
        case 7:
            q += 0x54;
            break;
        case 8:
            r = (int*)q;
            k = r[0];
            q = (unsigned char*)(r + 1) + k * 20;
            a += k;
            break;
        case 9:
            r = (int*)q;
            k = r[0];
            q = (unsigned char*)(r + 2) + k * 20;
            b += k;
            break;
        }
    }
    *x = a;
    *y = b;
}
#endif
INCLUDE_ASM(sub_80022B84);
struct struct_22CC4
{
    char pad_0[0x40];
    int n1;
    struct_20_b* d1;
    int n2;
    unsigned short f4C;
    unsigned short f4E;
    struct_20_b* d2;
};
#if 0
// Not matched: first loop swaps the j/k registers and fills the first beqz delay slot; second loop has the j++/n++ increments in the other order
void sub_80022CC4(struct_22CC4* a0, struct_22634* a, struct_22634* b, int h)
{
    int j;
    int n;
    int k;
    struct_8_20b* e;
    struct_12_20b* f;
    if (a->n)
    {
        j = 0;
        e = (struct_8_20b*)a->p;
        k = 0;
        for (n = 0; n < a0->n1; n++)
        {
            if (j >= ((struct_8_20b*)a->p)[k].count)
            {
                k++;
                j = 0;
                e = &((struct_8_20b*)a->p)[k];
            }
            a0->d1[n].f4 = e->items[j].f4;
            a0->d1[n].f6 = e->items[j].f6;
            a0->d1[n].f8 = e->items[j].f8;
            a0->d1[n].fA = 0;
            a0->d1[n].fC = e->items[j].fC;
            a0->d1[n].fE = e->items[j].fE;
            a0->d1[n].f10 = e->items[j].f10;
            a0->d1[n].f12 = 0;
            a0->d1[n].b0 = e->items[j].b0;
            a0->d1[n].b1 = e->items[j].b1;
            a0->d1[n].b2 = e->items[j].b2;
            a0->d1[n].b3 = 0;
            j++;
        }
    }
    if (b->n)
    {
        j = 0;
        a0->f4C = ((struct_12_20b*)b->p)->f4;
        a0->f4E = ((struct_12_20b*)b->p)->f6;
        f = (struct_12_20b*)b->p;
        k = 0;
        for (n = 0; n < a0->n2; n++, j++)
        {
            if (j >= ((struct_12_20b*)b->p)[k].count)
            {
                k++;
                j = 0;
                f = &((struct_12_20b*)b->p)[k];
            }
            a0->d2[n].f4 = f->items[j].f4;
            a0->d2[n].f6 = f->items[j].f6;
            a0->d2[n].f8 = f->items[j].f8;
            a0->d2[n].fA = 0;
            a0->d2[n].fC = f->items[j].fC;
            a0->d2[n].fE = f->items[j].fE;
            a0->d2[n].f10 = f->items[j].f10;
            a0->d2[n].f12 = 0;
            a0->d2[n].b0 = f->items[j].b0;
            a0->d2[n].b1 = f->items[j].b1;
            a0->d2[n].b2 = f->items[j].b2;
            a0->d2[n].b3 = f->items[j].b3;
            a0->d2[n].f12 = f->items[j].f12;
        }
    }
}
#endif
INCLUDE_ASM(sub_80022CC4);
#if 0
// Not matched: s/p regs fixed by copying p; remaining: the source pointer becomes a biased induction variable (q+0x12) instead of plain q
int sub_8002300C(unsigned char* hdr, unsigned char* p_in, int* a, int k, int h)
{
    unsigned char* p = p_in;
    int r = 4;
    int i;
    unsigned char* q;
    ((struct_8_20b*)a[1])[k].count = *(int*)p;
    ((struct_8_20b*)a[1])[k].items = (struct_20_b*)HeapAlloc_8003FC8C(*(int*)p * 20, h);
    q = p + r;
    for (i = 0; i < *(int*)p; i++)
    {
        ((struct_8_20b*)a[1])[k].items[i].f4 = *(unsigned short*)(q + 0);
        ((struct_8_20b*)a[1])[k].items[i].f6 = *(unsigned short*)(q + 2);
        ((struct_8_20b*)a[1])[k].items[i].f8 = *(unsigned short*)(q + 4);
        ((struct_8_20b*)a[1])[k].items[i].fA = 0;
        ((struct_8_20b*)a[1])[k].items[i].fC = *(unsigned short*)(q + 8);
        ((struct_8_20b*)a[1])[k].items[i].fE = *(unsigned short*)(q + 0xA);
        ((struct_8_20b*)a[1])[k].items[i].f10 = *(unsigned short*)(q + 0xC);
        ((struct_8_20b*)a[1])[k].items[i].f12 = 0;
        ((struct_8_20b*)a[1])[k].items[i].b0 = q[0x10];
        ((struct_8_20b*)a[1])[k].items[i].b1 = q[0x11];
        ((struct_8_20b*)a[1])[k].items[i].b2 = q[0x12];
        ((struct_8_20b*)a[1])[k].items[i].b3 = 0;
        q += 20;
        r += 20;
    }
    return r;
}
#endif
INCLUDE_ASM(sub_8002300C);
#if 0
// Not matched: same issues as sub_8002300C plus register assignment
int sub_8002320C(unsigned char* hdr, unsigned char* p, int* b, int k, int h)
{
    int r = 8;
    int i;
    unsigned char* q;
    ((struct_12_20b*)b[1])[k].count = *(int*)p;
    ((struct_12_20b*)b[1])[k].items = (struct_20_b*)HeapAlloc_8003FC8C(*(int*)p * 20, h);
    ((struct_12_20b*)b[1])[k].f4 = *(unsigned short*)(p + 4);
    ((struct_12_20b*)b[1])[k].f6 = *(unsigned short*)(p + 6);
    q = p + r;
    for (i = 0; i < *(int*)p; i++)
    {
        ((struct_12_20b*)b[1])[k].items[i].f4 = *(unsigned short*)(q + 0);
        ((struct_12_20b*)b[1])[k].items[i].f6 = *(unsigned short*)(q + 2);
        ((struct_12_20b*)b[1])[k].items[i].f8 = *(unsigned short*)(q + 4);
        ((struct_12_20b*)b[1])[k].items[i].fA = 0;
        ((struct_12_20b*)b[1])[k].items[i].fC = *(unsigned short*)(q + 8);
        ((struct_12_20b*)b[1])[k].items[i].fE = *(unsigned short*)(q + 0xA);
        ((struct_12_20b*)b[1])[k].items[i].f10 = *(unsigned short*)(q + 0xC);
        ((struct_12_20b*)b[1])[k].items[i].f12 = 0;
        ((struct_12_20b*)b[1])[k].items[i].b0 = q[0x10];
        ((struct_12_20b*)b[1])[k].items[i].b1 = q[0x11];
        ((struct_12_20b*)b[1])[k].items[i].b2 = q[0x12];
        ((struct_12_20b*)b[1])[k].items[i].b3 = hdr[3];
        ((struct_12_20b*)b[1])[k].items[i].f12 = q[0xE] + (q[0xF] << 8);
        r += 20;
        q += 20;
    }
    return r;
}
#endif
INCLUDE_ASM(sub_8002320C);
// Matched
void sub_80023460(char* p, int arg1)
{
    RelocateTPageClut_80022AE8(p + 4, p + 6, arg1);
}
// Matched
int sub_8002348C(unsigned char* a0, int a1, int* a2, int a3)
{
    if (a0[3] & 2)
    {
        SetSemiTrans((char*)a2[1] + a3 * 0x24, 1);
    }
    sub_80023514(a2, a1, a0[3], a3);
    return 0x24;
}
// Matched
void sub_80023514(int* a0, int a1, int a2, int a3)
{
    unsigned char* s = (unsigned char*)a1;
    int o = a3 * 0x24;
    ((unsigned char*)(o + a0[1]))[0] = s[0];
    ((unsigned char*)(o + a0[1]))[1] = s[1];
    ((unsigned char*)(o + a0[1]))[2] = s[2];
    ((unsigned char*)(o + a0[1]))[3] = a2;
    *(unsigned short*)(o + a0[1] + 0xC) = *(unsigned short*)(s + 0xC);
    *(unsigned short*)(o + a0[1] + 0xE) = *(unsigned short*)(s + 0xE);
    *(unsigned short*)(o + a0[1] + 0x10) = *(unsigned short*)(s + 0x10);
    *(unsigned short*)(o + a0[1] + 0x14) = *(unsigned short*)(s + 0x14);
    *(unsigned short*)(o + a0[1] + 0x16) = *(unsigned short*)(s + 0x16);
    *(unsigned short*)(o + a0[1] + 0x18) = *(unsigned short*)(s + 0x18);
    *(unsigned short*)(o + a0[1] + 0x1C) = *(unsigned short*)(s + 0x1C);
    *(unsigned short*)(o + a0[1] + 0x1E) = *(unsigned short*)(s + 0x1E);
    *(unsigned short*)(o + a0[1] + 0x20) = *(unsigned short*)(s + 0x20);
    *(unsigned short*)(o + a0[1] + 4) = *(unsigned short*)(s + 4);
    *(unsigned short*)(o + a0[1] + 6) = *(unsigned short*)(s + 6);
    *(unsigned short*)(o + a0[1] + 8) = *(unsigned short*)(s + 8);
}
// Matched
int sub_80023624(unsigned char* a0, int a1, int* a2, int a3)
{
    if (a0[3] & 2)
    {
        SetSemiTrans((char*)a2[3] + a3 * 0x3C, 1);
    }
    sub_800236AC(a2 + 2, a1, a0[3], a3);
    return 0x3C;
}
// Matched
void sub_800236AC(int* a0, int a1, int a2, int a3)
{
    unsigned char* s = (unsigned char*)a1;
    int o = a3 * 0x3C;
    *(unsigned char*)(o + a0[1]) = *(unsigned char*)s;
    *(unsigned char*)(o + a0[1] + 0x1) = *(unsigned char*)(s + 0x1);
    *(unsigned char*)(o + a0[1] + 0x2) = *(unsigned char*)(s + 0x2);
    *(unsigned char*)(o + a0[1] + 0x3) = a2;
    *(unsigned char*)(o + a0[1] + 0x4) = *(unsigned char*)(s + 0x4);
    *(unsigned char*)(o + a0[1] + 0x5) = *(unsigned char*)(s + 0x5);
    *(unsigned char*)(o + a0[1] + 0x6) = *(unsigned char*)(s + 0x6);
    *(unsigned char*)(o + a0[1] + 0x3) = a2;
    *(unsigned char*)(o + a0[1] + 0x8) = *(unsigned char*)(s + 0x8);
    *(unsigned char*)(o + a0[1] + 0x9) = *(unsigned char*)(s + 0x9);
    *(unsigned char*)(o + a0[1] + 0xA) = *(unsigned char*)(s + 0xA);
    *(unsigned char*)(o + a0[1] + 0x3) = a2;
    *(unsigned short*)(o + a0[1] + 0x24) = *(unsigned short*)(s + 0x14);
    *(unsigned short*)(o + a0[1] + 0x26) = *(unsigned short*)(s + 0x16);
    *(unsigned short*)(o + a0[1] + 0x28) = *(unsigned short*)(s + 0x18);
    *(unsigned short*)(o + a0[1] + 0x2C) = *(unsigned short*)(s + 0x24);
    *(unsigned short*)(o + a0[1] + 0x2E) = *(unsigned short*)(s + 0x26);
    *(unsigned short*)(o + a0[1] + 0x30) = *(unsigned short*)(s + 0x28);
    *(unsigned short*)(o + a0[1] + 0x34) = *(unsigned short*)(s + 0x34);
    *(unsigned short*)(o + a0[1] + 0x36) = *(unsigned short*)(s + 0x36);
    *(unsigned short*)(o + a0[1] + 0x38) = *(unsigned short*)(s + 0x38);
    *(unsigned short*)(o + a0[1] + 0xC) = *(unsigned short*)(s + 0xC);
    *(unsigned short*)(o + a0[1] + 0xE) = *(unsigned short*)(s + 0xE);
    *(unsigned short*)(o + a0[1] + 0x10) = *(unsigned short*)(s + 0x10);
    *(unsigned short*)(o + a0[1] + 0x14) = *(unsigned short*)(s + 0x1C);
    *(unsigned short*)(o + a0[1] + 0x16) = *(unsigned short*)(s + 0x1E);
    *(unsigned short*)(o + a0[1] + 0x18) = *(unsigned short*)(s + 0x20);
    *(unsigned short*)(o + a0[1] + 0x1C) = *(unsigned short*)(s + 0x2C);
    *(unsigned short*)(o + a0[1] + 0x1E) = *(unsigned short*)(s + 0x2E);
    *(unsigned short*)(o + a0[1] + 0x20) = *(unsigned short*)(s + 0x30);
    *(unsigned char*)(o + a0[1] + 0x3) = a2;
}
// Matched
int sub_800238AC(unsigned char* a0, int a1, int* a2, int a3)
{
    if (a0[3] & 2)
    {
        SetSemiTrans((char*)a2[5] + a3 * 0x30, 1);
    }
    sub_80023934(a2 + 4, a1, a0[3], a3);
    return 0x24;
}
// Matched
void sub_80023934(int* a0, int a1, int a2, int a3)
{
    unsigned char* s = (unsigned char*)a1;
    int o = a3 * 0x30;
    *(unsigned short*)(o + a0[1] + 0xA) = *(unsigned short*)(s);
    *(unsigned short*)(o + a0[1] + 0x6) = *(unsigned short*)(s + 0x2);
    *(unsigned char*)(o + a0[1] + 0x4) = *(unsigned char*)(s + 0x12);
    *(unsigned char*)(o + a0[1] + 0x5) = *(unsigned char*)(s + 0x13);
    *(unsigned short*)(o + a0[1] + 0x1E) = *(unsigned char*)(o + a0[1] + 0x4) + (*(unsigned char*)(o + a0[1] + 0x5) << 8);
    *(unsigned char*)(o + a0[1] + 0x8) = *(unsigned char*)(s + 0x1A);
    *(unsigned char*)(o + a0[1] + 0x9) = *(unsigned char*)(s + 0x1B);
    *(unsigned short*)(o + a0[1] + 0x26) = *(unsigned char*)(o + a0[1] + 0x8) + (*(unsigned char*)(o + a0[1] + 0x9) << 8);
    *(unsigned char*)(o + a0[1] + 0xC) = *(unsigned char*)(s + 0x22);
    *(unsigned char*)(o + a0[1] + 0xD) = *(unsigned char*)(s + 0x23);
    *(unsigned short*)(o + a0[1] + 0x2E) = *(unsigned char*)(o + a0[1] + 0xC) + (*(unsigned char*)(o + a0[1] + 0xD) << 8);
    *(unsigned char*)(o + a0[1]) = 0x80;
    *(unsigned char*)(o + a0[1] + 0x1) = 0x80;
    *(unsigned char*)(o + a0[1] + 0x2) = 0x80;
    *(unsigned char*)(o + a0[1] + 0x3) = a2;
    *(unsigned short*)(o + a0[1] + 0x18) = *(unsigned short*)(s + 0xC);
    *(unsigned short*)(o + a0[1] + 0x1A) = *(unsigned short*)(s + 0xE);
    *(unsigned short*)(o + a0[1] + 0x1C) = *(unsigned short*)(s + 0x10);
    *(unsigned short*)(o + a0[1] + 0x20) = *(unsigned short*)(s + 0x14);
    *(unsigned short*)(o + a0[1] + 0x22) = *(unsigned short*)(s + 0x16);
    *(unsigned short*)(o + a0[1] + 0x24) = *(unsigned short*)(s + 0x18);
    *(unsigned short*)(o + a0[1] + 0x28) = *(unsigned short*)(s + 0x1C);
    *(unsigned short*)(o + a0[1] + 0x2A) = *(unsigned short*)(s + 0x1E);
    *(unsigned short*)(o + a0[1] + 0x2C) = *(unsigned short*)(s + 0x20);
    *(unsigned short*)(o + a0[1] + 0x10) = *(unsigned short*)(s + 0x4);
    *(unsigned short*)(o + a0[1] + 0x12) = *(unsigned short*)(s + 0x6);
    *(unsigned short*)(o + a0[1] + 0x14) = *(unsigned short*)(s + 0x8);
}
// Matched
void sub_80023B24(unsigned short* p, int arg1)
{
    RelocateTPageClut_80022AE8(p, p + 1, arg1);
}
// Matched
int sub_80023B48(unsigned char* a0, int a1, int* a2, int a3)
{
    if (a0[3] & 2)
    {
        SetSemiTrans((char*)a2[7] + a3 * 0x48, 1);
    }
    sub_80023BD0(a2 + 6, a1, a0[3], a3);
    return 0x40;
}
// Matched
void sub_80023BD0(int* a0, int a1, int a2, int a3)
{
    unsigned char* s = (unsigned char*)a1;
    int o = a3 * 0x48;
    *(unsigned short*)(o + a0[1] + 0x12) = *(unsigned short*)(s);
    *(unsigned short*)(o + a0[1] + 0xE) = *(unsigned short*)(s + 0x2);
    *(unsigned char*)(o + a0[1] + 0xC) = *(unsigned char*)(s + 0x1E);
    *(unsigned char*)(o + a0[1] + 0xD) = *(unsigned char*)(s + 0x1F);
    *(unsigned short*)(o + a0[1] + 0x36) = *(unsigned char*)(o + a0[1] + 0xC) + (*(unsigned char*)(o + a0[1] + 0xD) << 8);
    *(unsigned char*)(o + a0[1] + 0x10) = *(unsigned char*)(s + 0x2E);
    *(unsigned char*)(o + a0[1] + 0x11) = *(unsigned char*)(s + 0x2F);
    *(unsigned short*)(o + a0[1] + 0x3E) = *(unsigned char*)(o + a0[1] + 0x10) + (*(unsigned char*)(o + a0[1] + 0x11) << 8);
    *(unsigned char*)(o + a0[1] + 0x14) = *(unsigned char*)(s + 0x3E);
    *(unsigned char*)(o + a0[1] + 0x15) = *(unsigned char*)(s + 0x3F);
    *(unsigned short*)(o + a0[1] + 0x46) = *(unsigned char*)(o + a0[1] + 0x14) + (*(unsigned char*)(o + a0[1] + 0x15) << 8);
    *(unsigned char*)(o + a0[1] + 0x3) = a2;
    *(unsigned char*)(o + a0[1]) = *(unsigned char*)(s + 0x4);
    *(unsigned char*)(o + a0[1] + 0x1) = *(unsigned char*)(s + 0x5);
    *(unsigned char*)(o + a0[1] + 0x2) = *(unsigned char*)(s + 0x6);
    *(unsigned char*)(o + a0[1] + 0x4) = *(unsigned char*)(s + 0x8);
    *(unsigned char*)(o + a0[1] + 0x5) = *(unsigned char*)(s + 0x9);
    *(unsigned char*)(o + a0[1] + 0x6) = *(unsigned char*)(s + 0xA);
    *(unsigned char*)(o + a0[1] + 0x8) = *(unsigned char*)(s + 0xC);
    *(unsigned char*)(o + a0[1] + 0x9) = *(unsigned char*)(s + 0xD);
    *(unsigned char*)(o + a0[1] + 0xA) = *(unsigned char*)(s + 0xE);
    *(unsigned short*)(o + a0[1] + 0x30) = *(unsigned short*)(s + 0x18);
    *(unsigned short*)(o + a0[1] + 0x32) = *(unsigned short*)(s + 0x1A);
    *(unsigned short*)(o + a0[1] + 0x34) = *(unsigned short*)(s + 0x1C);
    *(unsigned short*)(o + a0[1] + 0x38) = *(unsigned short*)(s + 0x28);
    *(unsigned short*)(o + a0[1] + 0x3A) = *(unsigned short*)(s + 0x2A);
    *(unsigned short*)(o + a0[1] + 0x3C) = *(unsigned short*)(s + 0x2C);
    *(unsigned short*)(o + a0[1] + 0x40) = *(unsigned short*)(s + 0x38);
    *(unsigned short*)(o + a0[1] + 0x42) = *(unsigned short*)(s + 0x3A);
    *(unsigned short*)(o + a0[1] + 0x44) = *(unsigned short*)(s + 0x3C);
    *(unsigned short*)(o + a0[1] + 0x18) = *(unsigned short*)(s + 0x10);
    *(unsigned short*)(o + a0[1] + 0x1A) = *(unsigned short*)(s + 0x12);
    *(unsigned short*)(o + a0[1] + 0x1C) = *(unsigned short*)(s + 0x14);
    *(unsigned short*)(o + a0[1] + 0x20) = *(unsigned short*)(s + 0x20);
    *(unsigned short*)(o + a0[1] + 0x22) = *(unsigned short*)(s + 0x22);
    *(unsigned short*)(o + a0[1] + 0x24) = *(unsigned short*)(s + 0x24);
    *(unsigned short*)(o + a0[1] + 0x28) = *(unsigned short*)(s + 0x30);
    *(unsigned short*)(o + a0[1] + 0x2A) = *(unsigned short*)(s + 0x32);
    *(unsigned short*)(o + a0[1] + 0x2C) = *(unsigned short*)(s + 0x34);
}
// Matched
void sub_80023E80(unsigned short* p, int arg1)
{
    RelocateTPageClut_80022AE8(p, p + 1, arg1);
}
// Matched
int sub_80023EA4(unsigned char* a0, int a1, int* a2, int a3)
{
    if (a0[3] & 2)
    {
        SetSemiTrans((char*)a2[9] + a3 * 0x2C, 1);
    }
    sub_80023F34(a2 + 8, a1, a0[3], a3);
    return 0x2C;
}
// Matched
void sub_80023F34(int* a0, int a1, int a2, int a3)
{
    unsigned char* s = (unsigned char*)a1;
    int o = a3 * 0x2C;
    *(unsigned char*)(o + a0[1]) = *(unsigned char*)s;
    *(unsigned char*)(o + a0[1] + 0x1) = *(unsigned char*)(s + 0x1);
    *(unsigned char*)(o + a0[1] + 0x2) = *(unsigned char*)(s + 0x2);
    *(unsigned char*)(o + a0[1] + 0x3) = a2;
    *(unsigned short*)(o + a0[1] + 0xC) = *(unsigned short*)(s + 0xC);
    *(unsigned short*)(o + a0[1] + 0xE) = *(unsigned short*)(s + 0xE);
    *(unsigned short*)(o + a0[1] + 0x10) = *(unsigned short*)(s + 0x10);
    *(unsigned short*)(o + a0[1] + 0x14) = *(unsigned short*)(s + 0x14);
    *(unsigned short*)(o + a0[1] + 0x16) = *(unsigned short*)(s + 0x16);
    *(unsigned short*)(o + a0[1] + 0x18) = *(unsigned short*)(s + 0x18);
    *(unsigned short*)(o + a0[1] + 0x1C) = *(unsigned short*)(s + 0x1C);
    *(unsigned short*)(o + a0[1] + 0x1E) = *(unsigned short*)(s + 0x1E);
    *(unsigned short*)(o + a0[1] + 0x20) = *(unsigned short*)(s + 0x20);
    *(unsigned short*)(o + a0[1] + 0x24) = *(unsigned short*)(s + 0x24);
    *(unsigned short*)(o + a0[1] + 0x26) = *(unsigned short*)(s + 0x26);
    *(unsigned short*)(o + a0[1] + 0x28) = *(unsigned short*)(s + 0x28);
    *(unsigned short*)(o + a0[1] + 0x4) = *(unsigned short*)(s + 0x4);
    *(unsigned short*)(o + a0[1] + 0x6) = *(unsigned short*)(s + 0x6);
    *(unsigned short*)(o + a0[1] + 0x8) = *(unsigned short*)(s + 0x8);
}
// Matched
int sub_8002407C(unsigned char* a0, int a1, int* a2, int a3)
{
    if (a0[3] & 2)
    {
        SetSemiTrans((char*)a2[11] + a3 * 0x50, 1);
    }
    sub_80024104(a2 + 10, a1, a0[3], a3);
    return 0x50;
}
// Matched
void sub_80024104(int* a0, int a1, int a2, int a3)
{
    unsigned char* s = (unsigned char*)a1;
    int o = a3 * 0x50;
    *(unsigned char*)(o + a0[1]) = *(unsigned char*)s;
    *(unsigned char*)(o + a0[1] + 0x1) = *(unsigned char*)(s + 0x1);
    *(unsigned char*)(o + a0[1] + 0x2) = *(unsigned char*)(s + 0x2);
    *(unsigned char*)(o + a0[1] + 0x3) = a2;
    *(unsigned char*)(o + a0[1] + 0x4) = *(unsigned char*)(s + 0x4);
    *(unsigned char*)(o + a0[1] + 0x5) = *(unsigned char*)(s + 0x5);
    *(unsigned char*)(o + a0[1] + 0x6) = *(unsigned char*)(s + 0x6);
    *(unsigned char*)(o + a0[1] + 0x3) = a2;
    *(unsigned char*)(o + a0[1] + 0x8) = *(unsigned char*)(s + 0x8);
    *(unsigned char*)(o + a0[1] + 0x9) = *(unsigned char*)(s + 0x9);
    *(unsigned char*)(o + a0[1] + 0xA) = *(unsigned char*)(s + 0xA);
    *(unsigned char*)(o + a0[1] + 0x3) = a2;
    *(unsigned char*)(o + a0[1] + 0xC) = *(unsigned char*)(s + 0xC);
    *(unsigned char*)(o + a0[1] + 0xD) = *(unsigned char*)(s + 0xD);
    *(unsigned char*)(o + a0[1] + 0xE) = *(unsigned char*)(s + 0xE);
    *(unsigned char*)(o + a0[1] + 0x3) = a2;
    *(unsigned short*)(o + a0[1] + 0x30) = *(unsigned short*)(s + 0x18);
    *(unsigned short*)(o + a0[1] + 0x32) = *(unsigned short*)(s + 0x1A);
    *(unsigned short*)(o + a0[1] + 0x34) = *(unsigned short*)(s + 0x1C);
    *(unsigned short*)(o + a0[1] + 0x38) = *(unsigned short*)(s + 0x28);
    *(unsigned short*)(o + a0[1] + 0x3A) = *(unsigned short*)(s + 0x2A);
    *(unsigned short*)(o + a0[1] + 0x3C) = *(unsigned short*)(s + 0x2C);
    *(unsigned short*)(o + a0[1] + 0x40) = *(unsigned short*)(s + 0x38);
    *(unsigned short*)(o + a0[1] + 0x42) = *(unsigned short*)(s + 0x3A);
    *(unsigned short*)(o + a0[1] + 0x44) = *(unsigned short*)(s + 0x3C);
    *(unsigned short*)(o + a0[1] + 0x48) = *(unsigned short*)(s + 0x48);
    *(unsigned short*)(o + a0[1] + 0x4A) = *(unsigned short*)(s + 0x4A);
    *(unsigned short*)(o + a0[1] + 0x4C) = *(unsigned short*)(s + 0x4C);
    *(unsigned short*)(o + a0[1] + 0x10) = *(unsigned short*)(s + 0x10);
    *(unsigned short*)(o + a0[1] + 0x12) = *(unsigned short*)(s + 0x12);
    *(unsigned short*)(o + a0[1] + 0x14) = *(unsigned short*)(s + 0x14);
    *(unsigned short*)(o + a0[1] + 0x18) = *(unsigned short*)(s + 0x20);
    *(unsigned short*)(o + a0[1] + 0x1A) = *(unsigned short*)(s + 0x22);
    *(unsigned short*)(o + a0[1] + 0x1C) = *(unsigned short*)(s + 0x24);
    *(unsigned short*)(o + a0[1] + 0x20) = *(unsigned short*)(s + 0x30);
    *(unsigned short*)(o + a0[1] + 0x22) = *(unsigned short*)(s + 0x32);
    *(unsigned short*)(o + a0[1] + 0x24) = *(unsigned short*)(s + 0x34);
    *(unsigned short*)(o + a0[1] + 0x28) = *(unsigned short*)(s + 0x40);
    *(unsigned short*)(o + a0[1] + 0x2A) = *(unsigned short*)(s + 0x42);
    *(unsigned short*)(o + a0[1] + 0x2C) = *(unsigned short*)(s + 0x44);
}
// Matched
int sub_80024394(unsigned char* a0, int a1, int* a2, int a3)
{
    if (a0[3] & 2)
    {
        SetSemiTrans((char*)a2[13] + a3 * 0x38, 1);
    }
    sub_8002441C(a2 + 12, a1, a0[3], a3);
    return 0x2C;
}
// Matched
void sub_8002441C(int* a0, int a1, int a2, int a3)
{
    unsigned char* s = (unsigned char*)a1;
    int o = a3 * 0x38;
    *(unsigned short*)(o + a0[1] + 0xA) = *(unsigned short*)(s);
    *(unsigned short*)(o + a0[1] + 0x6) = *(unsigned short*)(s + 0x2);
    *(unsigned char*)(o + a0[1] + 0x4) = *(unsigned char*)(s + 0x12);
    *(unsigned char*)(o + a0[1] + 0x5) = *(unsigned char*)(s + 0x13);
    *(unsigned short*)(o + a0[1] + 0x1E) = *(unsigned char*)(o + a0[1] + 0x4) + (*(unsigned char*)(o + a0[1] + 0x5) << 8);
    *(unsigned char*)(o + a0[1] + 0x8) = *(unsigned char*)(s + 0x1A);
    *(unsigned char*)(o + a0[1] + 0x9) = *(unsigned char*)(s + 0x1B);
    *(unsigned short*)(o + a0[1] + 0x26) = *(unsigned char*)(o + a0[1] + 0x8) + (*(unsigned char*)(o + a0[1] + 0x9) << 8);
    *(unsigned char*)(o + a0[1] + 0xC) = *(unsigned char*)(s + 0x22);
    *(unsigned char*)(o + a0[1] + 0xD) = *(unsigned char*)(s + 0x23);
    *(unsigned short*)(o + a0[1] + 0x2E) = *(unsigned char*)(o + a0[1] + 0xC) + (*(unsigned char*)(o + a0[1] + 0xD) << 8);
    *(unsigned char*)(o + a0[1] + 0xE) = *(unsigned char*)(s + 0x2A);
    *(unsigned char*)(o + a0[1] + 0xF) = *(unsigned char*)(s + 0x2B);
    *(unsigned short*)(o + a0[1] + 0x36) = *(unsigned char*)(o + a0[1] + 0xE) + (*(unsigned char*)(o + a0[1] + 0xF) << 8);
    *(unsigned char*)(o + a0[1]) = 0x80;
    *(unsigned char*)(o + a0[1] + 0x1) = 0x80;
    *(unsigned char*)(o + a0[1] + 0x2) = 0x80;
    *(unsigned char*)(o + a0[1] + 0x3) = a2;
    *(unsigned short*)(o + a0[1] + 0x18) = *(unsigned short*)(s + 0xC);
    *(unsigned short*)(o + a0[1] + 0x1A) = *(unsigned short*)(s + 0xE);
    *(unsigned short*)(o + a0[1] + 0x1C) = *(unsigned short*)(s + 0x10);
    *(unsigned short*)(o + a0[1] + 0x20) = *(unsigned short*)(s + 0x14);
    *(unsigned short*)(o + a0[1] + 0x22) = *(unsigned short*)(s + 0x16);
    *(unsigned short*)(o + a0[1] + 0x24) = *(unsigned short*)(s + 0x18);
    *(unsigned short*)(o + a0[1] + 0x28) = *(unsigned short*)(s + 0x1C);
    *(unsigned short*)(o + a0[1] + 0x2A) = *(unsigned short*)(s + 0x1E);
    *(unsigned short*)(o + a0[1] + 0x2C) = *(unsigned short*)(s + 0x20);
    *(unsigned short*)(o + a0[1] + 0x30) = *(unsigned short*)(s + 0x24);
    *(unsigned short*)(o + a0[1] + 0x32) = *(unsigned short*)(s + 0x26);
    *(unsigned short*)(o + a0[1] + 0x34) = *(unsigned short*)(s + 0x28);
    *(unsigned short*)(o + a0[1] + 0x10) = *(unsigned short*)(s + 0x4);
    *(unsigned short*)(o + a0[1] + 0x12) = *(unsigned short*)(s + 0x6);
    *(unsigned short*)(o + a0[1] + 0x14) = *(unsigned short*)(s + 0x8);
}
// Matched
void sub_8002467C(unsigned short* p, int arg1)
{
    RelocateTPageClut_80022AE8(p, p + 1, arg1);
}
// Matched
int sub_800246A0(unsigned char* a0, int a1, int* a2, int a3)
{
    if (a0[3] & 2)
    {
        SetSemiTrans((char*)a2[15] + a3 * 0x5C, 1);
    }
    sub_80024730(a2 + 14, a1, a0[3], a3);
    return 0x54;
}
// Matched
void sub_80024730(int* a0, int a1, int a2, int a3)
{
    unsigned char* s = (unsigned char*)a1;
    int o = a3 * 0x5C;
    *(unsigned short*)(o + a0[1] + 0x16) = *(unsigned short*)(s);
    *(unsigned short*)(o + a0[1] + 0x12) = *(unsigned short*)(s + 0x2);
    *(unsigned char*)(o + a0[1] + 0x10) = *(unsigned char*)(s + 0x22);
    *(unsigned char*)(o + a0[1] + 0x11) = *(unsigned char*)(s + 0x23);
    *(unsigned short*)(o + a0[1] + 0x42) = *(unsigned char*)(o + a0[1] + 0x10) + (*(unsigned char*)(o + a0[1] + 0x11) << 8);
    *(unsigned char*)(o + a0[1] + 0x14) = *(unsigned char*)(s + 0x32);
    *(unsigned char*)(o + a0[1] + 0x15) = *(unsigned char*)(s + 0x33);
    *(unsigned short*)(o + a0[1] + 0x4A) = *(unsigned char*)(o + a0[1] + 0x14) + (*(unsigned char*)(o + a0[1] + 0x15) << 8);
    *(unsigned char*)(o + a0[1] + 0x18) = *(unsigned char*)(s + 0x42);
    *(unsigned char*)(o + a0[1] + 0x19) = *(unsigned char*)(s + 0x43);
    *(unsigned short*)(o + a0[1] + 0x52) = *(unsigned char*)(o + a0[1] + 0x18) + (*(unsigned char*)(o + a0[1] + 0x19) << 8);
    *(unsigned char*)(o + a0[1] + 0x1A) = *(unsigned char*)(s + 0x52);
    *(unsigned char*)(o + a0[1] + 0x1B) = *(unsigned char*)(s + 0x53);
    *(unsigned short*)(o + a0[1] + 0x5A) = *(unsigned char*)(o + a0[1] + 0x1A) + (*(unsigned char*)(o + a0[1] + 0x1B) << 8);
    *(unsigned char*)(o + a0[1] + 0x3) = a2;
    *(unsigned char*)(o + a0[1]) = *(unsigned char*)(s + 0x4);
    *(unsigned char*)(o + a0[1] + 0x1) = *(unsigned char*)(s + 0x5);
    *(unsigned char*)(o + a0[1] + 0x2) = *(unsigned char*)(s + 0x6);
    *(unsigned char*)(o + a0[1] + 0x4) = *(unsigned char*)(s + 0x8);
    *(unsigned char*)(o + a0[1] + 0x5) = *(unsigned char*)(s + 0x9);
    *(unsigned char*)(o + a0[1] + 0x6) = *(unsigned char*)(s + 0xA);
    *(unsigned char*)(o + a0[1] + 0x8) = *(unsigned char*)(s + 0xC);
    *(unsigned char*)(o + a0[1] + 0x9) = *(unsigned char*)(s + 0xD);
    *(unsigned char*)(o + a0[1] + 0xA) = *(unsigned char*)(s + 0xE);
    *(unsigned char*)(o + a0[1] + 0xC) = *(unsigned char*)(s + 0x10);
    *(unsigned char*)(o + a0[1] + 0xD) = *(unsigned char*)(s + 0x11);
    *(unsigned char*)(o + a0[1] + 0xE) = *(unsigned char*)(s + 0x12);
    *(unsigned short*)(o + a0[1] + 0x3C) = *(unsigned short*)(s + 0x1C);
    *(unsigned short*)(o + a0[1] + 0x3E) = *(unsigned short*)(s + 0x1E);
    *(unsigned short*)(o + a0[1] + 0x40) = *(unsigned short*)(s + 0x20);
    *(unsigned short*)(o + a0[1] + 0x44) = *(unsigned short*)(s + 0x2C);
    *(unsigned short*)(o + a0[1] + 0x46) = *(unsigned short*)(s + 0x2E);
    *(unsigned short*)(o + a0[1] + 0x48) = *(unsigned short*)(s + 0x30);
    *(unsigned short*)(o + a0[1] + 0x4C) = *(unsigned short*)(s + 0x3C);
    *(unsigned short*)(o + a0[1] + 0x4E) = *(unsigned short*)(s + 0x3E);
    *(unsigned short*)(o + a0[1] + 0x50) = *(unsigned short*)(s + 0x40);
    *(unsigned short*)(o + a0[1] + 0x54) = *(unsigned short*)(s + 0x4C);
    *(unsigned short*)(o + a0[1] + 0x56) = *(unsigned short*)(s + 0x4E);
    *(unsigned short*)(o + a0[1] + 0x58) = *(unsigned short*)(s + 0x50);
    *(unsigned short*)(o + a0[1] + 0x1C) = *(unsigned short*)(s + 0x14);
    *(unsigned short*)(o + a0[1] + 0x1E) = *(unsigned short*)(s + 0x16);
    *(unsigned short*)(o + a0[1] + 0x20) = *(unsigned short*)(s + 0x18);
    *(unsigned short*)(o + a0[1] + 0x24) = *(unsigned short*)(s + 0x24);
    *(unsigned short*)(o + a0[1] + 0x26) = *(unsigned short*)(s + 0x26);
    *(unsigned short*)(o + a0[1] + 0x28) = *(unsigned short*)(s + 0x28);
    *(unsigned short*)(o + a0[1] + 0x2C) = *(unsigned short*)(s + 0x34);
    *(unsigned short*)(o + a0[1] + 0x2E) = *(unsigned short*)(s + 0x36);
    *(unsigned short*)(o + a0[1] + 0x30) = *(unsigned short*)(s + 0x38);
    *(unsigned short*)(o + a0[1] + 0x34) = *(unsigned short*)(s + 0x44);
    *(unsigned short*)(o + a0[1] + 0x36) = *(unsigned short*)(s + 0x46);
    *(unsigned short*)(o + a0[1] + 0x38) = *(unsigned short*)(s + 0x48);
}
// Matched
void sub_80024AB8(unsigned short* p, int arg1)
{
    RelocateTPageClut_80022AE8(p, p + 1, arg1);
}
// Matched
void InitModelList_80024ADC(struct_112_list** a0, void* a1, int heap)
{
    struct_112_list* l;
    int i;
    l = *a0 = (struct_112_list*)HeapAlloc_8003FC8C(0x10, (struct Pool*)heap);
    l->count = sub_80026600(a1);
    l->field_4 = heap;
    l->items = (struct_112*)HeapAlloc_8003FC8C(l->count * 0x70, (struct Pool*)heap);
    l->field_C = a1;
    for (i = 0; i < l->count; i++)
    {
        l->items[i].field_0 = (int)l;
        l->items[i].field_30 = i;
        ClearModel_800266CC(&l->items[i]);
    }
}
// Matched
void FreeModelList_80024BB0(struct_112_list** a0)
{
    struct_112_list* l = *a0;
    int i;
    for (i = 0; i < l->count; i++)
    {
        FreeModel_80024C48(&l->items[i]);
    }
    HeapFree_8003FD18(l->items, l->field_4);
    HeapFree_8003FD18(l, l->field_4);
    *a0 = 0;
}
// Matched
void FreeModel_80024C48(struct_112* p)
{
    int h;
    sub_80025AB0(p);
    sub_80025C38(p, 1);
    h = ((int*)p->field_0)[1];
    if (p->field_44 != 0)
    {
        HeapFree_8003FD18(p->field_44, h);
    }
    if (p->field_4C != 0)
    {
        HeapFree_8003FD18(p->field_4C, h);
    }
    if (p->field_50 != 0)
    {
        FreeFtgObjects_80021784((int**)&p->field_50, p->field_3C, h);
    }
    if (p->field_54 != 0)
    {
        FreeModelAnims_8002679C((struct_28**)&p->field_54, p->field_3E, h);
    }
    if (p->field_58 != 0)
    {
        HeapFree_8003FD18(p->field_58, h);
    }
    if (p->field_60 != 0)
    {
        sub_80021E24(&p->field_5C, h);
    }
    if (p->field_64 != 0)
    {
        HeapFree_8003FD18(p->field_64, h);
    }
    if (p->field_68 != 0)
    {
        FreeFtgObjects_80021784((int**)&p->field_68, p->field_42, h);
    }
    if (p->field_6C != 0)
    {
        HeapFree_8003FD18(p->field_6C, h);
    }
    ClearModel_800266CC(p);
}
// Matched
struct_112* AcquireModel_80024D70(struct_112_list* p, unsigned int id)
{
    int i = FindModelIndex_80026630(p, id);
    if (i >= 0)
    {
        struct_112* r = &p->items[i];
        r->field_3A++;
        return r;
    }
    return 0;
}
// Matched
int AreFileRequestsDone_80024DC4(void* a0)
{
    int* p = (int*)a0;
    int i;
    i = 0;
    while (i < p[1])
    {
        if (GetFileRequestStatus_8003BE30(p[2 + i]) != 0)
        {
            return 0;
        }
        i++;
    }
    p[1] = 0;
    return 1;
}
// Matched
char* sub_80024E38(struct_obj_E* p)
{
    char* result = 0;
    int* hdr = p->field_4C;
    if (hdr && hdr[0])
    {
        result = (char*)hdr + hdr[0] + 4;
    }
    return result;
}
// Matched
char* sub_80024E64(struct_obj_E* p)
{
    char* result = 0;
    int* hdr = p->field_4C;
    if (hdr && hdr[1])
    {
        result = (char*)hdr + hdr[1];
    }
    return result;
}
// Matched
char* sub_80024E90(void* p, int n)
{
    char* r = sub_80024FA8(p, n);
    if (r)
    {
        r += *(int*)r;
    }
    return r;
}
// Matched
char* sub_80024EC8(void* p, int n)
{
    char* r = sub_80024FA8(p, n);
    if (r)
    {
        r += *(int*)(r + 4);
    }
    return r;
}
// Matched
char* sub_80024F00(void* p, int n)
{
    char* r = sub_80024FA8(p, n);
    if (r)
    {
        r += *(int*)(r + 8);
    }
    return r;
}
// Matched
char* sub_80024F38(void* p, int n)
{
    char* r = sub_80024FA8(p, n);
    if (r)
    {
        r += *(int*)(r + 0xC);
    }
    return r;
}
// Matched
char* sub_80024F70(void* p, int n)
{
    char* r = sub_80024FA8(p, n);
    if (r)
    {
        r += *(int*)(r + 0x10);
    }
    return r;
}
#if 0
// Not matched: the original keeps the 0 result in v0 and copies it into the loop counter; ours keeps the result in a2
char* sub_80024FA8(void* a0, int n)
{
    char* hdr = *(char**)((char*)a0 + 0x4C);
    char* r = 0;
    int i = 0;
    if (hdr)
    {
        int off = *(int*)(hdr + 8);
        if (off)
        {
            hdr = hdr + off + 8;
            for (; i < n; i++)
            {
                hdr += *(int*)(hdr + 0x14);
            }
            return hdr;
        }
    }
    return r;
}
#endif
INCLUDE_ASM(sub_80024FA8);
// Matched
void sub_80024FFC(struct_112* p, int* ids)
{
    int n;
    int heap;
    for (n = 0; ids[n] >= 0; n++)
    {
    }
    heap = ((int*)p->field_0)[1];
    p->field_40 = n;
    p->field_64 = HeapAlloc_8003FC8C(n * sizeof(struct_58), heap);
    n--;
    while (n >= 0)
    {
        int id = ids[n];
        ((struct_58*)p->field_64)[n].id = id;
        ((struct_58*)p->field_64)[n].d = ((struct_54*)p->field_50)[id];
        n--;
    }
}
// Matched
void sub_8002512C(unsigned int* a0, char* a1, int a2)
{
    int i;
    for (i = 0; i < *(unsigned short*)(a1 + 0x40); i++)
    {
        int* e = (int*)(i * 0x58 + *(int*)(a1 + 0x64));
        if (a2 == e[0])
        {
            MemCopy_800403E8(a0, (unsigned int*)(e + 1), 0x54);
            break;
        }
    }
}
// Matched
void sub_800251A0(void* dst, struct_obj_E* src, int a2, int idx)
{
    MemCopy_800403E8((unsigned int*)dst, (unsigned int*)&src->field_50[idx], sizeof(struct_54));
}
// Matched
void nullsub_4(void)
{
}
// Matched
int GetModelDesc_800251E4(int idx)
{
    return modelDescs_800824CC[idx];
}
// Matched
int LoadModel_80025200(struct_112_list* a0, int id, int sel, int a3, int flag)
{
    int b[16];
    int c[8];
    int two = 1;
    int i;
    unsigned short* e;
    struct_112* it;
    int x;
    int u;
    int v;
    i = FindModelIndex_80026630(a0, id);
    if (i >= 0)
    {
        return AreFileRequestsDone_80024DC4((int*)&a0->items[i]) == 0;
    }
    i = FindFreeModelIndex_8002667C(a0);
    if (i >= 0)
    {
        e = (unsigned short*)modelDescs_800824CC[id];
        it = &a0->items[i];
        x = ((int*)a0)[3] + i * 16;
        InitModelLoadParams_80025ED0(b);
        if (sel != -1)
        {
            b[0] |= 3;
        }
        b[0] |= 0xC;
        v = 0;
        b[5] = (int)it;
        b[6] = x;
        b[1] = (int)e;
        b[2] = sel;
        b[3] = a3;
        if (sel != -1)
        {
            two = 0;
            v += e[2];
            v += e[4];
            u = e[1];
        }
        else
        {
            u = e[5];
        }
        v += e[6];
        v += e[8];
        c[1] = e[0];
        c[0] = 0x68;
        if (flag == 1)
        {
            c[0] = 0x6C;
        }
        else
        {
            c[0] = 0x69;
        }
        c[2] = u;
        c[3] = v;
        c[4] = 0;
        c[5] = (int)b;
        c[6] = 0x3C;
        c[7] = (int)OnModelFileLoaded_80025D7C;
        AddFileRequest_80025D00((struct_list10*)it, c);
        if (two != 0)
        {
            InitModelLoadParams_80025ED0(b);
            b[0] = 1;
            b[5] = (int)it;
            b[1] = (int)e;
            c[1] = e[0];
            c[0] = 0x68;
            if (flag == 1)
            {
                c[0] = 0x6C;
            }
            else
            {
                c[0] = 0x69;
            }
            c[2] = e[1];
            c[3] = e[2];
            c[5] = (int)b;
            c[6] = 0x3C;
            c[4] = 0;
            c[7] = (int)OnModelFileLoaded_80025D7C;
            AddFileRequest_80025D00((struct_list10*)it, c);
        }
        it->id_38 = id;
        return 1;
    }
    return 2;
}
#if 0
// Not matched: the table-entry sum lands in the wrong one of v0/v1, and &b is set up one slot early
int LoadModelAnim_80025440(struct_112* p, int idx, int flag)
{
    int b[16];
    int c[8];
    unsigned short* e;
    unsigned short* t;
    int u;
    int v;
    int k;
    unsigned char* f = (unsigned char*)p->field_44 + idx;
    if (*f == 0)
    {
        k = idx * 2 + 10;
        e = (unsigned short*)modelDescs_800824CC[p->id_38];
        t = (unsigned short*)((k + e[9]) * 2 + (int)e);
        u = t[0];
        v = t[1];
        *f = 1;
        InitModelLoadParams_80025ED0(b);
        b[0] = 0x10;
        b[5] = (int)p;
        b[1] = (int)e;
        b[4] = idx;
        c[0] = 0x68;
        if (flag != 0)
        {
            c[0] = 0x6C;
        }
        else
        {
            c[0] = 0x69;
        }
        c[1] = e[0];
        c[2] = u;
        c[3] = v;
        c[4] = 0;
        c[5] = (int)b;
        c[6] = 0x3C;
        c[7] = (int)OnModelFileLoaded_80025D7C;
        AddFileRequest_80025D00((struct_list10*)p, c);
        return 1;
    }
    return AreFileRequestsDone_80024DC4((int*)p) == 0;
}
#endif
INCLUDE_ASM(LoadModelAnim_80025440);
// Matched
void FreeModelAnim_8002556C(struct_112* p, int idx)
{
    if (((char*)p->field_44)[idx])
    {
        FreeModelAnimData_800269C4(p->field_54, p->field_3E, idx, ((int*)p->field_0)[1]);
        ((char*)p->field_44)[idx] = 0;
    }
}
// Matched
int IsModelAnimLoaded_800255D8(struct_112* p, int idx)
{
    return ((char*)p->field_44)[idx] != 0;
}
// Matched
int sub_800255F0(int a, int idx, int a2)
{
    int* a0 = (int*)a;
    int b[16];
    int c[8];
    unsigned int x = a0[2];
    int y = a0[3];
    unsigned short* e = (unsigned short*)modelDescs_800824CC[idx];
    InitModelLoadParams_80025ED0(b);
    b[0] = 2;
    b[2] = a2;
    c[0] = 0x69;
    b[5] = x;
    b[6] = y;
    b[1] = (int)e;
    c[1] = e[0];
    c[2] = e[3];
    c[3] = e[4];
    c[4] = 0;
    c[5] = (int)b;
    c[6] = 0x3C;
    c[7] = (int)OnModelFileLoaded_80025D7C;
    AddFileRequest_80025D00((struct_list10*)x, c);
    return 1;
}
// Matched
int sub_800256B8(int a, int id)
{
    struct_112_list* a0 = (struct_112_list*)a;
    int b[16];
    int c[8];
    struct_112* it = &a0->items[FindModelIndex_80026630(a0, id)];
    unsigned short* e = (unsigned short*)modelDescs_800824CC[it->id_38];
    InitModelLoadParams_80025ED0(b);
    b[0] = 8;
    b[5] = (int)it;
    b[3] = 3;
    b[1] = (int)e;
    c[0] = 0x69;
    c[1] = e[0];
    c[2] = e[7];
    c[3] = e[8];
    c[4] = 0;
    c[5] = (int)b;
    c[6] = 0x3C;
    c[7] = (int)OnModelFileLoaded_80025D7C;
    AddFileRequest_80025D00((struct_list10*)it, c);
    return 1;
}
// Matched
int LoadModelAnimSet_80025780(struct_112* p, int idx, int flag)
{
    int b[16];
    int c[8];
    unsigned short* e;
    char* t;
    int u;
    int v;
    FreeModelAnimSet_80025884(p);
    e = (unsigned short*)modelDescs_800824CC[p->id_38];
    t = (char*)e + (e[9] * 6 + 0x14);
    u = ((unsigned short*)t)[idx * 2 + 1];
    v = ((unsigned short*)t)[idx * 2 + 2];
    InitModelLoadParams_80025ED0(b);
    b[0] = 0x20;
    b[5] = (int)p;
    b[1] = (int)e;
    c[0] = 0x68;
    if (flag != 0)
    {
        c[0] = 0x6C;
    }
    else
    {
        c[0] = 0x69;
    }
    c[1] = e[0];
    c[2] = u;
    c[3] = v;
    c[4] = 0;
    c[5] = (int)b;
    c[6] = 0x3C;
    c[7] = (int)OnModelFileLoaded_80025D7C;
    AddFileRequest_80025D00((struct_list10*)p, c);
    return 1;
}
// Matched
void FreeModelAnimSet_80025884(struct_112* p)
{
    int* list = (int*)p->field_58;
    if (list)
    {
        int heap = ((int*)p->field_0)[1];
        int n = list[0];
        int i;
        for (i = 0; i < n; i++)
        {
            int id = ((int*)p->field_58)[i + 1];
            if (id >= 0)
            {
                FreeModelAnim_8002556C(p, id);
            }
        }
        HeapFree_8003FD18(p->field_58, heap);
        p->field_58 = 0;
    }
}
// Matched
int IsAnimInModelAnimSet_80025924(int* p, int id)
{
    int* list = (int*)p[0x58 / 4];
    int i;
    int n;
    if (list != 0)
    {
        n = list[0];
        for (i = 0; i < n; i++)
        {
            if (id == list[i + 1])
            {
                return 1;
            }
        }
    }
    return 0;
}
// Matched
int sub_80025974(struct_112* p, int idx, int flag)
{
    int b[16];
    int c[8];
    unsigned short* e;
    char* t;
    int u;
    int v;
    int* g;
    sub_80025AB0(p);
    e = (unsigned short*)modelDescs_800824CC[p->id_38];
    t = (char*)e + (e[9] * 6 + 0x14);
    t += *(unsigned short*)t * 4 + 2;
    g = (int*)p->field_0;
    u = ((unsigned short*)t)[idx * 2 + 1];
    v = ((unsigned short*)t)[idx * 2 + 2];
    InitModelLoadParams_80025ED0(b);
    b[0] = 0x40;
    b[5] = (int)p;
    b[6] = g[3] + p->field_30 * 16;
    b[2] = p->field_34;
    b[1] = (int)e;
    c[0] = 0x68;
    if (flag != 0)
    {
        c[0] = 0x6C;
    }
    else
    {
        c[0] = 0x69;
    }
    c[1] = e[0];
    c[2] = u;
    c[3] = v;
    c[4] = 0;
    c[5] = (int)b;
    c[6] = 0x3C;
    c[7] = (int)OnModelFileLoaded_80025D7C;
    AddFileRequest_80025D00((struct_list10*)p, c);
    return 1;
}
// Matched
void sub_80025AB0(struct_112* p)
{
    struct Pool* h = (struct Pool*)((int*)p->field_0)[1];
    if (p->field_68)
    {
        FreeFtgObjects_80021784((int**)&p->field_68, p->field_42, h);
        p->field_42 = 0;
        p->field_68 = 0;
    }
    if (p->field_6C)
    {
        HeapFree_8003FD18(p->field_6C, h);
        p->field_43 = 0;
        p->field_6C = 0;
    }
}
// Matched
void sub_80025B20(void* dst, struct_obj_E* src, int idx)
{
    MemCopy_800403E8((unsigned int*)dst, (unsigned int*)&src->field_68[idx], sizeof(struct_54));
}
// Matched
void sub_80025B5C(struct_obj_E* p, int idx, int sel)
{
    struct_54 tmp;
    if (idx == sel)
    {
        sub_8002512C((unsigned int*)&tmp, (char*)p, idx);
    }
    else if (sel < p->field_3C)
    {
        sub_800251A0(&tmp, p, idx, sel);
    }
    else
    {
        sub_80025B20(&tmp, p, sel - p->field_3C);
    }
    p->field_50[idx] = tmp;
}
// Matched
void sub_80025C38(struct_112* p, int flag)
{
    int i;
    for (i = 0; i < p->field_40; i++)
    {
        int* e = (int*)(i * 0x58 + p->field_64);
        sub_80025B5C(p, e[0], e[0]);
    }
    if (flag)
    {
        for (i = 0; i < p->field_43; i++)
        {
            short* s = (short*)(i * 4 + p->field_6C);
            sub_80025B5C(p, s[0], s[1]);
        }
    }
}
// Matched
int AddFileRequest_80025D00(struct_list10* a0, int* a1)
{
    if (a0->count < 10)
    {
        a1[2] <<= 11;
        a1[3] <<= 11;
        a0->items[a0->count] = QueueFileRequest_8003BC84(a1);
        a0->count += 1;
        return 1;
    }
    return 0;
}
// Matched
void OnModelFileLoaded_80025D7C(int* a0, int b)
{
    if (a0[0] & 1)
    {
        a0[7] = b;
        b += *(unsigned short*)(a0[1] + 4) << 11;
    }
    if (a0[0] & 2)
    {
        a0[8] = b;
        b += *(unsigned short*)(a0[1] + 8) << 11;
    }
    if (a0[0] & 4)
    {
        a0[9] = b;
        b += *(unsigned short*)(a0[1] + 0xC) << 11;
    }
    if (a0[0] & 8)
    {
        a0[10] = b;
        b += *(unsigned short*)(a0[1] + 0x10) << 11;
    }
    if (a0[0] & 0x10)
    {
        a0[11] = b;
    }
    if (a0[0] & 0x20)
    {
        a0[12] = b;
    }
    if (a0[0] & 0x40)
    {
        a0[0] |= 0x80;
        a0[14] = b + ((int*)b)[1];
        a0[0] |= 0x40;
        a0[13] = b + ((int*)b)[2];
        a0[0] |= 2;
        a0[8] = b + ((int*)b)[3];
    }
    ParseModelFile_80025F14(a0);
}
// Matched
void InitModelLoadParams_80025ED0(int* p)
{
    p[2] = -1;
    p[0] = 0;
    p[1] = 0;
    p[3] = 2;
    p[4] = 0;
    p[5] = 0;
    p[6] = 0;
    p[7] = 0;
    p[8] = 0;
    p[9] = 0;
    p[10] = 0;
    p[11] = 0;
    p[13] = 0;
    p[14] = 0;
}
// Matched
void ParseModelFile_80025F14(int* a0)
{
    if (a0[0] & 1)
    {
        sub_80026014((char*)a0);
    }
    if (a0[0] & 2)
    {
        LoadModelTextures_8002607C(a0);
    }
    if (a0[0] & 4)
    {
        LoadModelFtg_800260FC(a0);
    }
    if (a0[0] & 8)
    {
        LoadModelAnims_800261C8(a0);
    }
    if (a0[0] & 0x10)
    {
        LoadSingleModelAnim_800263CC(a0);
    }
    if (a0[0] & 0x20)
    {
        LoadModelAnimSetSection_80026410(a0);
    }
    if (a0[0] & 0x40)
    {
        sub_8002651C(a0);
    }
    if (a0[0] & 0x80)
    {
        sub_8002659C((char*)a0);
    }
}
typedef struct
{
    char pad_0[0x14];
    struct_112* owner_14;
    int* data_18;
    int* data_1C;
    char pad_20[0x14];
    int* list_34;
    unsigned char* data_38;
} struct_loader;
// Matched
void sub_80026014(char* a0)
{
    int* q = *(int**)(a0 + 0x1C);
    struct_112* p = *(struct_112**)(a0 + 0x14);
    int h = ((int*)p->field_0)[1];
    int n = q[0];
    int r;
    p->field_48 = n;
    r = HeapAlloc_8003FC8C(n, h);
    p->field_4C = r;
    MemCopy_800403E8((unsigned int*)r, (unsigned int*)(*(int*)(a0 + 0x1C) + 4), n);
}
// Matched
void LoadModelTextures_8002607C(int* a0)
{
    if (a0[2] != -1)
    {
        int* p = (int*)a0[5];
        LoadTiyTimsRelocated_80028FDC(0, 0, 0, a0[8], GetTiyFileCount_80028E68((int*)a0[8]), a0[6] + 4, a0[2]);
        p[0x34 / 4] = a0[2];
    }
}
#if 0
// Not matched: the a0[9] list argument is loaded before the a0[6] load in the original, ours after; insensitive to statement order, types and temporaries
void LoadModelFtg_800260FC(int* a0)
{
    int q = a0[6];
    struct_112* p = (struct_112*)a0[5];
    int h = ((int*)p->field_0)[1];
    q += 4;
    p->field_3C = GetFtgObjectCount_80021738((int*)a0[9]);
    AllocFtgObjects_80021744(&p->field_50, p->field_3C, h);
    LoadFtgObjects_80021824((int*)a0[9], (char*)p->field_50, p->field_3C, h, q);
    if (sub_80021DE4((int*)a0[9]) != 0)
    {
        sub_80021DF0(&p->field_5C, sub_80021DE4((int*)a0[9]), h);
        sub_80021E4C((char*)a0[9], &p->field_5C, sub_80021DE4((int*)a0[9]));
    }
}
#endif
INCLUDE_ASM(LoadModelFtg_800260FC);
// Matched
void LoadModelAnims_800261C8(int* a0)
{
    struct_112* p = (struct_112*)a0[5];
    int h = ((int*)p->field_0)[1];
    int i;
    int j;
    int mode;
    p->field_3E = *(unsigned short*)(a0[1] + 0x12);
    if (p->field_54 == 0)
    {
        AllocModelAnims_80026730((struct_28**)&p->field_54, p->field_3E, h);
    }
    if (p->field_44 != 0)
    {
        HeapFree_8003FD18(p->field_44, h);
    }
    p->field_44 = HeapAlloc_8003FC8C(p->field_3E, h);
    for (i = 0; i < p->field_3E; i++)
    {
        mode = a0[3];
        if (mode == 0)
        {
            if (i == 0)
            {
                ((unsigned char*)p->field_44)[0] = 1;
            }
            else
            {
                ((unsigned char*)p->field_44)[i] = 0;
            }
        }
        else if (mode == 1)
        {
            if (i == 0)
            {
                ((unsigned char*)p->field_44)[0] = 1;
            }
            else if (i == 1)
            {
                ((unsigned char*)p->field_44)[1] = 1;
            }
            else
            {
                ((unsigned char*)p->field_44)[i] = 0;
            }
        }
        else if (mode == 3)
        {
            if (i == 0)
            {
                ((unsigned char*)p->field_44)[0] = 0;
            }
            else if (i == 1)
            {
                ((unsigned char*)p->field_44)[1] = 0;
            }
            else
            {
                ((unsigned char*)p->field_44)[i] = *(unsigned char*)(a0[1] + 0x14 + i * 2);
            }
        }
        else
        {
            ((unsigned char*)p->field_44)[i] = *(unsigned char*)(a0[1] + 0x14 + i * 2);
        }
    }
    for (i = 0, j = 0; i < p->field_3E; i++)
    {
        if (((unsigned short*)(a0[1] + 0x14))[i] != 0)
        {
            if (((unsigned char*)p->field_44)[i] != 0)
            {
                LoadModelAnimData_80026A8C((char*)p->field_54 + i * 28, a0[10] + ((int*)a0[10])[j + 1], h);
            }
            j++;
        }
    }
}
// Matched
void LoadSingleModelAnim_800263CC(int* p)
{
    int* tmp27;
    int** q = (int**)p[5];
    tmp27 = *(q + 0);
    LoadModelAnimData_80026A8C((char*)q[0x54 / 4] + p[4] * 28, *(p + 0xB), tmp27[1]);
}
// Matched
void LoadModelAnimSetSection_80026410(int* a0)
{
    int* q = (int*)a0[12];
    struct_112* p = (struct_112*)a0[5];
    int n = q[0];
    int h = ((int*)p->field_0)[1];
    int* list = (int*)HeapAlloc_8003FC8C((n + 1) * 4, h);
    int i;
    int id;
    int src;
    p->field_58 = (int)list;
    list[0] = n;
    for (i = 0; i < n; i++)
    {
        id = q[i * 2 + 1];
        src = (int)q + q[i * 2 + 2];
        if (((unsigned char*)p->field_44)[id] == 0)
        {
            ((int*)p->field_58)[i + 1] = id;
            ((unsigned char*)p->field_44)[id] = 1;
            LoadModelAnimData_80026A8C((char*)p->field_54 + id * 28, src, h);
        }
        else
        {
            ((int*)p->field_58)[i + 1] = -1;
        }
    }
}
#if 0
// Not matched: the original loads the list argument (+0x34) right after the owner pointer, ours schedules it first (same as LoadModelFtg_800260FC)
void sub_8002651C(int* a)
{
    struct_112* p = ((struct_loader*)a)->owner_14;
    int* list = ((struct_loader*)a)->list_34;
    int heap = ((int*)p->field_0)[1];
    int* q = ((struct_loader*)a)->data_18 + 1;
    p->field_42 = GetFtgObjectCount_80021738(list);
    AllocFtgObjects_80021744(&p->field_68, p->field_42, heap);
    LoadFtgObjects_80021824(((struct_loader*)a)->list_34, (char*)p->field_68, p->field_42, heap, (int)q);
}
#endif
INCLUDE_ASM(sub_8002651C);
// Matched
void sub_8002659C(char* a0)
{
    unsigned char* q = *(unsigned char**)(a0 + 0x38);
    struct_112* p = *(struct_112**)(a0 + 0x14);
    int h = ((int*)p->field_0)[1];
    int r;
    p->field_43 = *q;
    q += 4;
    r = HeapAlloc_8003FC8C(p->field_43 << 2, h);
    p->field_6C = r;
    MemCopy_800403E8((unsigned int*)r, (unsigned int*)q, p->field_43 << 2);
}
// Matched
int sub_80026600(struct_16_b* p)
{
    int n = 0;
    if (p->field_2 != -1)
    {
        do
        {
            p++;
            n++;
        } while (p->field_2 != -1);
    }
    return n;
}
// Matched
int FindModelIndex_80026630(struct_112_list* p, unsigned int id)
{
    int i;
    for (i = 0; i < p->count; i++)
    {
        if (p->items[i].id_38 == id)
        {
            return i;
        }
    }
    return -1;
}
// Matched
int FindFreeModelIndex_8002667C(struct_112_list* p)
{
    int i;
    for (i = 0; i < p->count; i++)
    {
        if (p->items[i].id_38 == 0xFFFF)
        {
            return i;
        }
    }
    return -1;
}
// Matched
void ClearModel_800266CC(struct_112* p)
{
    p->id_38 = 0xFFFF;
    p->field_4 = 0;
    p->field_34 = 0;
    p->field_3A = 0;
    p->field_3C = 0;
    p->field_3E = 0;
    p->field_40 = 0;
    p->field_42 = 0;
    p->field_43 = 0;
    p->field_44 = 0;
    p->field_48 = 0;
    p->field_4C = 0;
    p->field_50 = 0;
    p->field_54 = 0;
    p->field_58 = 0;
    p->field_5C = 0;
    p->field_60 = 0;
    p->field_64 = 0;
    p->field_68 = 0;
    p->field_6C = 0;
}
// Matched
int sub_80026724(int* p)
{
    return p[0];
}
// Matched
void AllocModelAnims_80026730(struct_28** a0, int a1, int a2)
{
    struct_28* p = (struct_28*)HeapAlloc_8003FC8C(a1 * 28, a2);
    int i;
    *a0 = p;
    for (i = 0; i < a1; i++)
    {
        p[i].field_10 = 0;
        p[i].field_14 = 0;
        p[i].field_18 = 0;
    }
}
// Matched
void FreeModelAnims_8002679C(struct_28** a0, int n, int heap)
{
    struct_28* arr;
    int i;
    if (*a0)
    {
        arr = *a0;
        for (i = 0; i < n; i++)
        {
            if (arr[i].field_10)
            {
                HeapFree_8003FD18(arr[i].field_10, heap);
            }
            if (arr[i].field_14)
            {
                HeapFree_8003FD18(arr[i].field_14, heap);
            }
            if (arr[i].field_18)
            {
                HeapFree_8003FD18(arr[i].field_18, heap);
            }
        }
        HeapFree_8003FD18(arr, heap);
        *a0 = 0;
    }
}
// Matched
void sub_80026870(int* a0, int a1, int a2)
{
    int r = sub_80026724((int*)a1);
    AllocModelAnims_80026730((struct_28**)a0, r, a2);
    sub_800268E8(a0[0], a1, r, a2, -1);
}
// Matched
void sub_800268E8(int a0, int a1, int n, int h, int mask)
{
    int* q = (int*)a1;
    int i;
    for (i = 0; i < n; i++, a0 += sizeof(struct_28))
    {
        int bit = 1 << i;
        if ((mask & bit) && ((struct_28*)a0)->field_14 == 0 && ((struct_28*)a0)->field_18 == 0)
        {
            LoadModelAnimData_80026A8C((struct_28*)a0, a1 + q[i + 1], h);
        }
    }
}
// Matched
void FreeModelAnimData_800269C4(int a0, int n, int sel, int h)
{
    struct_28* p = (struct_28*)a0;
    int i;
    for (i = 0; i < n; i++, p++)
    {
        if (sel == i && p->field_14 != 0 && p->field_18 != 0)
        {
            if (p->field_10 != 0)
            {
                HeapFree_8003FD18(p->field_10, h);
            }
            HeapFree_8003FD18(p->field_14, h);
            HeapFree_8003FD18(p->field_18, h);
            p->field_10 = 0;
            p->field_14 = 0;
            p->field_18 = 0;
        }
    }
}
#if 0
// Not matched: original copies src[0] through a temporary into n (s3) and orders the param copies before the flag init; the last loop reads the source before computing the k*8 dest offset
void LoadModelAnimData_80026A8C(void* a0, int a1, int a2)
{
    int* o = a0;
    int* src = (int*)a1;
    int h = a2;
    int f1 = 0;
    int f2 = f1;
    unsigned int n;
    unsigned int m;
    unsigned short* s;
    unsigned short* d;
    unsigned int i;
    unsigned int j;
    int r;
    int k;
    o[0] = src[0];
    o[1] = src[1];
    n = o[0];
    m = o[1];
    if ((int)n < 0)
    {
        n &= 0x7FFFFFFF;
        s = (unsigned short*)(src + 3);
        o[0] = n;
        o[2] = src[2];
        f1 = 1;
    }
    else
    {
        o[2] = 0x20;
        s = (unsigned short*)(src + 2);
    }
    if ((int)m < 0)
    {
        m &= 0x7FFFFFFF;
        f2 = 1;
    }
    else
    {
        o[3] = 0;
    }
    o[5] = HeapAlloc_8003FC8C(m * 6, (struct Pool*)h);
    o[6] = HeapAlloc_8003FC8C((m + 2) * (n << 1) * 3, (struct Pool*)h);
    d = (unsigned short*)o[5];
    for (i = 0; i < m; i++)
    {
        *d++ = *s++;
        *d++ = *s++;
        *d++ = *s++;
    }
    d = (unsigned short*)o[6];
    for (j = 0; j < n; j++)
    {
        *d++ = *s++;
        *d++ = *s++;
        *d++ = *s++;
        *d++ = *s++;
        *d++ = *s++;
        *d++ = *s++;
        for (i = 0; i < m; i++)
        {
            *d++ = *s++;
            *d++ = *s++;
            *d++ = *s++;
        }
    }
    if (f2)
    {
        r = m * 6 + 8;
        r += (m * 6 + 0xC) * n;
        if (f1)
        {
            r += 4;
        }
        s = (unsigned short*)((char*)src + r);
        if (r & 3)
        {
            r += 2;
            s = (unsigned short*)((char*)src + r);
        }
        o[3] = *(int*)s;
        s += 2;
        o[4] = HeapAlloc_8003FC8C(o[3] * 8, (struct Pool*)h);
        for (k = 0; k < o[3]; k++)
        {
            ((unsigned short*)o[4])[k * 4 + 0] = s[0];
            ((unsigned short*)o[4])[k * 4 + 1] = s[1];
            ((unsigned short*)o[4])[k * 4 + 2] = s[2];
            ((unsigned short*)o[4])[k * 4 + 3] = s[3];
            s += 4;
        }
    }
}
#endif
INCLUDE_ASM(LoadModelAnimData_80026A8C);
// Matched
int sub_80026D6C(int* p)
{
    return p[0];
}
// Matched
void sub_80026D78(struct_12** a0, int a1, int a2)
{
    struct_12* p = (struct_12*)HeapAlloc_8003FC8C(a1 * 12, a2);
    int i;
    for (i = 0; i < a1; i++)
    {
        p[i].field_0 = 0;
        p[i].field_4 = 0;
        p[i].field_8 = 0;
    }
    *a0 = p;
}
// Matched
void sub_80026DE8(struct_12** a0, int n, int h)
{
    struct_12* p = *a0;
    int i;
    for (i = 0; i < n; i++, p++)
    {
        if (p->field_8 != 0)
        {
            HeapFree_8003FD18(p->field_8, h);
        }
    }
    HeapFree_8003FD18(*a0, h);
    *a0 = 0;
}
// Matched
void sub_80026E74(struct_12* a0, int* a1, int a2)
{
    int i;
    for (i = 0; i < sub_80026D6C(a1); i++)
    {
        sub_80026EF8(a0, (unsigned short*)((char*)a1 + a1[i + 1]), a2);
        a0++;
    }
}
// Matched
typedef struct
{
    unsigned short a;
    unsigned short b;
    unsigned short c;
    unsigned short d;
} struct_4h;
// Matched
void sub_80026EF8(struct_12* p, unsigned short* s, int a2)
{
    unsigned short* d;
    int i;
    p->field_0 = *(int*)s;
    s += 2;
    p->field_4 = *(int*)s;
    s += 2;
    d = (unsigned short*)HeapAlloc_8003FC8C(p->field_0 * 8, a2);
    p->field_8 = (int)d;
    for (i = 0; i < p->field_0; i++)
    {
        d[0] = s[0];
        d[1] = s[1];
        d[2] = s[2];
        d[3] = s[3];
        d += 4;
        s += 4;
    }
}
extern int dword_8008D648[];
extern int* dword_80082674;
extern int dword_80091C98;
extern int dword_80091C94;
extern int dword_80091C5C;
extern int dword_80091C58;
extern int dword_80091C90;
extern int dword_80091C9C;
extern int dword_80091C8C;
typedef struct
{
    int pos[3];
    int mapIdx;
} struct_80091C78;
extern struct_80091C78 stru_80091C78;
extern int dword_800B1DC8;
extern int dword_80091C54;
extern short word_80091CB8[];
extern int dword_80091C10;
extern int dword_80091C68;
extern int dword_80091C48;
// Matched
void sub_80026FAC(void)
{
    ListInit_8003FDB0(&dword_80091C68);
    ListInit_8003FDB0(&dword_80091C20);
    ListInit_8003FDB0(&dword_80091C10);
    ListInit_8003FDB0(&dword_80091C48);
    dword_80091C30[0] = 0x3A;
    dword_80091C30[1] = 0;
    dword_80091C30[2] = 0;
    dword_80091C30[3] = -1;
    dword_8008B500[1] = 0;
    dword_8008B500[2] = 0;
    dword_8008B500[3] = 0;
    dword_8008B500[10] = 0;
    dword_8008B500[14] = 0;
    dword_8008B500[15] = 0;
    dword_8008D648[0] = 0;
    dword_8008D648[1] = 0;
    dword_8008D648[2] = 0;
    dword_8008D648[3] = 0;
    dword_8008D648[1] = 0;
    dword_8008D648[2] = 0;
    dword_8008D648[4] = 0;
    dword_8008D648[5] = 0;
    dword_8008D648[6] = 0;
    dword_80091C88 = -1;
    dword_80091C44 = -1;
    dword_80082674 = 0;
    dword_80091C98 = 0;
    dword_80091C94 = 0;
    dword_80091C5C = 1;
    dword_80091C58 = 1;
    dword_80091C90 = 0;
    dword_80091CA0 = 0;
    dword_80091C9C = 0;
    dword_80091C8C = 0;
    stru_80091C78.mapIdx = -1;
    dword_80091C54 = dword_800B1DC8;
    word_80091CB8[7] = -1;
    word_80091CB8[6] = -1;
    word_80091CB8[5] = -1;
    word_80091CB8[4] = -1;
    word_80091CB8[3] = -1;
    word_80091CB8[2] = -1;
    word_80091CB8[1] = -1;
    word_80091C40[0] = -1;
    word_80091CB8[0] = -1;
    word_80091C40[1] = -1;
    dword_80082678 = 0;
    InitActors_8001D378();
}
extern int dword_80091C74;
extern int dword_80091CB4;
extern int dword_80082668;
extern int dword_8008266C;
extern int* dword_800B1DA8;
extern int* dword_8008D400;
extern int* messageWindowTask_8008D640;
extern int* dword_8008D49C;
extern int* dword_8008D674;
extern int* fileRequestTasks_8008D488;
extern void FreeActors_8001D3C4(int a0);
extern void sub_800AC73C(void);
extern void sub_800A54A0(void);
extern void sub_800A58B4(void);
extern void sub_800A7784(void);
extern void sub_800A170C(void);
extern void sub_800A1794(void);
// Matched
void sub_80027118(void)
{
    word_80091CB8[7] = -1;
    word_80091CB8[6] = -1;
    word_80091CB8[5] = -1;
    word_80091CB8[4] = -1;
    word_80091CB8[3] = -1;
    word_80091CB8[2] = -1;
    word_80091CB8[1] = -1;
    word_80091C40[0] = -1;
    word_80091CB8[0] = -1;
    word_80091C40[1] = -1;
    sub_8002741C();
    dword_80082678 = 0;
    dword_80091C74 = -1;
    dword_80091CB4 = 0;
    dword_80091C88 = -1;
    dword_80082668 = 0;
    dword_8008266C = 0;
    if (dword_80091C8C == 0)
    {
        StopAllEventEntries_80043B40(dword_800B1DA8);
        StopAllEventEntries_80043B40(dword_8008D400);
    }
    sub_800AC73C();
    StopAllEventEntries_80043B40(messageWindowTask_8008D640);
    StopAllEventEntries_80043B40(dword_8008D49C);
    StopAllEventEntries_80043B40(dword_8008D674);
    StopAllEventEntries_80043B40(fileRequestTasks_8008D488);
    sub_800A54A0();
    sub_800A58B4();
    FreeActors_8001D3C4(dword_80091CA0);
    sub_800A7784();
    sub_800A170C();
    sub_800A1794();
    ListFreeAll_8003FEC8(&dword_80091C10);
    ListFreeAll_8003FEC8(&dword_80091C68);
    if (!(unknownFlags_8008D678 & 0x20000))
    {
        ListFreeAll_8003FEC8(&dword_80091C48);
    }
}
// Matched
void sub_8002728C(void)
{
    dword_80091C44 = -1;
    ListFreeAll_8003FEC8(&dword_80091C20);
}
// Matched
void sub_800272BC(int a0, int a1)
{
    dword_80091C88 = a0;
    dword_80091C44 = a1;
}
#if 0
// Not matched (close)
int sub_800272D0(void)
{
    int* a = dword_800B1DC4[0x24 / 4];
    int* b = dword_800B1DB8[0x24 / 4];
    if (*a != 0)
    {
        return 1;
    }
    if (*b == 0)
    {
        return 0;
    }
    return 1;
}
#endif
// Matched
int sub_800272D0(void)
{
    int* a = dword_800B1DC4[9];
    int* b = dword_800B1DB8[9];
    if (a[0] != 0 || b[0] != 0)
    {
        return 1;
    }
    return 0;
}
// Matched
void sub_80027314(void)
{
    dword_80082670 = 1;
    word_8008B862 = -1;
}
// Matched
int sub_80027330(short a0)
{
    if (dword_80082678 == 0)
    {
        word_80091C40[0] = a0;
        return 1;
    }
    return 0;
}
// Matched
// Matched
int sub_80027358(int id)
{
    int* p;
    short* s;
    if (dword_80082678 == 1)
    {
        if (word_80091C40[0] != id)
        {
            word_8008B860 = id;
            return 0;
        }
        p = dword_800B1DB8[9];
        if (GetFileRequestStatus_8003BE30(p[1]) != 3)
        {
            return 0;
        }
        sub_8002728C();
        ConsumeFileRequest_8003BFD0(p[1], 0);
        sub_80028DC0();
        s = (short*)&saveData_8008B570;
        s[0x2F0 / 2] = id;
        s[0x2F2 / 2] = id;
        dword_80082678 = 0;
        return 1;
    }
    word_8008B860 = id;
    return 0;
}
// Matched
void sub_8002741C(void)
{
    int* p;
    if (dword_80082678 == 1)
    {
        p = dword_800B1DB8[9];
        CancelFileRequest_8003C060(p[1]);
        dword_80082678 = 0;
        p[0] = 0;
    }
}
// Matched
void sub_80027478(int mask, int set)
{
    int f;
    int code;
    if (set)
    {
        dword_80091C30[2] |= mask;
    }
    else
    {
        dword_80091C30[2] &= ~mask;
    }
    f = dword_80091C30[2];
    if (f && !(f & 1))
    {
        code = 0;
        if (!(f & 0x40))
        {
            if (dword_80091C30[0] & f)
            {
                code = 1;
            }
            else if (dword_80091C30[1] & f)
            {
                code = 2;
            }
        }
        dword_80091C30[2] |= 1;
        SetFadeMode_8001C19C(code, 0x20);
    }
}
// Matched
int sub_80027540(void)
{
    int* g = dword_80091C30;
    if (g[2] & 0x40)
    {
        return 1;
    }
    if (g[2] & 1)
    {
        if (g[2] == 1 && IsFadeDone_8001C2FC())
        {
            g[3] = 2;
            g[2] &= ~1;
            return 1;
        }
        return 0;
    }
    if (g[3] > 0)
    {
        g[3]--;
        if (g[3] <= 0)
        {
            SetFadeMode_8001C19C(3, 0);
        }
    }
    return 1;
}
// Matched
void sub_800275E8(char** a0, int a1, int a2)
{
    char* p;
    char* q;
    int i;
    if (a1 != 0)
    {
        p = (char*)ListAlloc_8003FDC0(a2, a1);
        *a0 = p;
        q = p;
        for (i = 0; i < a1; i++)
        {
            q[i] = 1;
        }
    }
}
// Matched
int* sub_80027650(int* a0, int a1, int h)
{
    int* src;
    int* d;
    int n;
    int i;
    int* g = dword_80091C60;
    a0 += 1;
    n = *a0++;
    src = a0;
    g[0] = n;
    if (n != 0)
    {
        d = (int*)ListAlloc_8003FDC0(h, n * 16);
        g[1] = (int)d;
        for (i = 0; i < g[0]; i++)
        {
            d[0] = src[0];
            d[1] = src[1];
            d[2] = src[2];
            d[3] = src[3];
            d += 4;
            src += 4;
        }
    }
    return src;
}
// Matched
void sub_80027708(int* a0, int a1)
{
    int r = GetFtgObjectCount_80021738(a0);
    dword_8008B500[0x38 / 4] = r;
    if (r != 0)
    {
        AllocFtgObjects_80021744(&dword_8008B500[0x3C / 4], r, a1);
        LoadFtgObjects_80021824(a0, dword_8008B500[0x3C / 4], dword_8008B500[0x38 / 4], a1, 0);
    }
}
typedef struct
{
    int field_0;
    int count;
    unsigned short field_8;
    unsigned short field_A;
    unsigned short* items;
} struct_27778;
// Matched
void sub_80027778(int* a0, int h)
{
    struct_27778* arr;
    unsigned int i;
    int j;
    int* src;
    unsigned short* q;
    int n;
    dword_8008D648[1] = a0[0];
    dword_8008D648[2] = a0[1];
    n = a0[2];
    dword_8008D648[0] = n;
    arr = (struct_27778*)ListAlloc_8003FDC0(h, n * 16);
    for (i = 0; i < dword_8008D648[0]; i++)
    {
        src = (int*)((char*)a0 + a0[i + 3]);
        arr[i].field_0 = *src++;
        arr[i].count = *src++;
        q = (unsigned short*)src;
        arr[i].field_8 = *q++;
        arr[i].field_A = *q++;
        arr[i].items = (unsigned short*)ListAlloc_8003FDC0(h, arr[i].count * 2);
        for (j = 0; j < arr[i].count; j++)
        {
            arr[i].items[j] = *q++;
        }
    }
    dword_8008D648[3] = (int)arr;
}
typedef struct
{
    unsigned char a;
    unsigned char b;
    unsigned short c;
} struct_4b;
typedef struct
{
    unsigned int count;
    struct_4b* items;
} struct_8_4b;
typedef struct
{
    short a;
    short b;
} struct_2s;
// Matched
void sub_800278BC(int* a, int h)
{
    int* a0 = a;
    unsigned int i;
    unsigned int j;
    int n;
    int* q;
    struct_4b* r;
    struct_2s* e;
    n = a0[0];
    dword_8008D648[4] = n;
    dword_8008D648[5] = (int)ListAlloc_8003FDC0(h, n * 8);
    for (i = 0; i < dword_8008D648[4]; i++)
    {
        q = (int*)((char*)a0 + a0[i + 1]);
        ((struct_8_4b*)dword_8008D648[5])[i].count = *q;
        ((struct_8_4b*)dword_8008D648[5])[i].items = (struct_4b*)ListAlloc_8003FDC0(h, ((struct_8_4b*)dword_8008D648[5])[i].count * 4);
        r = (struct_4b*)(q + 1);
        for (j = 0; j < ((struct_8_4b*)dword_8008D648[5])[i].count; j++)
        {
            ((struct_8_4b*)dword_8008D648[5])[i].items[j].a = r[j].a;
            ((struct_8_4b*)dword_8008D648[5])[i].items[j].b = r[j].b;
            ((struct_8_4b*)dword_8008D648[5])[i].items[j].c = r[j].c;
        }
    }
    dword_8008D648[6] = (int)ListAlloc_8003FDC0(h, dword_8008D648[4] * 4);
    for (i = 0; i < dword_8008D648[4]; i++)
    {
        e = (struct_2s*)(i * 4 + dword_8008D648[6]);
        e->b = 0;
        e->a = 0;
    }
}
typedef struct
{
    short x;
    short y;
    short z;
    short pad;
} struct_a88_sv;
typedef struct
{
    int field_0;
    struct_a88_sv v[4];
} struct_a88_24;
typedef struct
{
    struct_a88_sv v[4];
} struct_20v;
typedef struct
{
    unsigned short n;
    struct_20v* items;
} struct_8_20v;
#if 0
// Not matched: s1/s2 swapped (p vs arr+i) and the source-item address is strength-reduced differently
int* sub_80027A88(struct_8_20v** out, int* count, int heap, int* hdr)
{
    struct_8_20v* arr;
    unsigned int i;
    unsigned int j;
    unsigned char* p;
    unsigned char* rec;
    int* hh;
    p = (unsigned char*)hdr + 0x10;
    hh = hdr;
    arr = (struct_8_20v*)ListAlloc_8003FDC0(heap, hdr[1] * 8);
    *count = hdr[1];
    if (hdr[1] == 0)
    {
        *out = 0;
        return (int*)((unsigned char*)hdr + hdr[0]);
    }
    for (i = 0; i < hh[1]; i++)
    {
        rec = p;
        arr[i].n = *(unsigned short*)rec;
        p = rec + 0x28;
        arr[i].items = (struct_20v*)ListAlloc_8003FDC0(heap, *(int*)rec * 32);
        for (j = 0; j < *(unsigned int*)rec; j++)
        {
            arr[i].items[j].v[3].x = ((struct_a88_24*)(rec + 0x2C))[j].v[0].x;
            arr[i].items[j].v[3].y = ((struct_a88_24*)(rec + 0x2C))[j].v[0].y;
            arr[i].items[j].v[3].z = ((struct_a88_24*)(rec + 0x2C))[j].v[0].z;
            arr[i].items[j].v[3].pad = 0;
            arr[i].items[j].v[0].x = ((struct_a88_24*)(rec + 0x2C))[j].v[1].x;
            arr[i].items[j].v[0].y = ((struct_a88_24*)(rec + 0x2C))[j].v[1].y;
            arr[i].items[j].v[0].z = ((struct_a88_24*)(rec + 0x2C))[j].v[1].z;
            arr[i].items[j].v[0].pad = 0;
            arr[i].items[j].v[1].x = ((struct_a88_24*)(rec + 0x2C))[j].v[2].x;
            arr[i].items[j].v[1].y = ((struct_a88_24*)(rec + 0x2C))[j].v[2].y;
            arr[i].items[j].v[1].z = ((struct_a88_24*)(rec + 0x2C))[j].v[2].z;
            arr[i].items[j].v[1].pad = 0;
            arr[i].items[j].v[2].x = ((struct_a88_24*)(rec + 0x2C))[j].v[3].x;
            arr[i].items[j].v[2].y = ((struct_a88_24*)(rec + 0x2C))[j].v[3].y;
            arr[i].items[j].v[2].z = ((struct_a88_24*)(rec + 0x2C))[j].v[3].z;
            arr[i].items[j].v[2].pad = 0;
            p += 0x28;
        }
    }
    *out = arr;
    return (int*)((unsigned char*)hdr + hh[0]);
}
#endif
INCLUDE_ASM(sub_80027A88);
// Matched
void sub_80027CC0(struct_obj_D* p, int* q)
{
    q[0] = 0;
    q[1] = 0;
    sub_80027CF8(p, q);
    p->field_8 = (void (*)(void))sub_80027CF8;
}
typedef struct
{
    short f0;
    short f2;
    short f4;
    short f6;
    short f8;
    short fA;
    char pad_C[4];
} MapEntry16;
extern MapEntry16** dword_800B0608[];
#define MAP_ENTRY_CF8(i) dword_800B0608[saveData_8008B570.mapId_2E4[0].field_0][saveData_8008B570.mapId_2E4[1].field_0][i]
extern int dword_800B0EC0;
extern int dword_80091CB0;
extern void sub_800ADDAC(void);
extern int sub_800A683C(int a0);
extern void sub_800AD124(int a0);
extern int sub_800A5030(int a0, int a1, int a2);
extern void sub_800A52AC(int a0);
extern int sub_800AC38C(void);
extern int sub_800AD154(int a0);
extern void sub_800B88A4(int a0);
extern void PlayMusic_800300E0(int a, int b);
extern void sub_80028808(void* a0, int* a1);
#if 0
// Not matched: 5 instructions: in case 1 the a1[0] load, the constant 1 and the eventDispatchHalt address get rotated registers (a0/v0/v1)
void sub_80027CF8(void* a0, int* a)
{
    int* a1 = a;
    short v[2];
    int req[8];
    MapEntry16* e;
    int t;
    int m;
    int n;
    int k;
    switch (a1[0])
    {
    case 0:
        m = dword_800B0EC0;
        if (m == 1 && sub_80020D84() == 0)
        {
            eventDispatchHalt_8008B540 = m;
        }
        else if (sub_80027540() != 0)
        {
            if (dword_80091C9C != 1 &&
                saveData_8008B570.mapId_2E4[0].field_2 == saveData_8008B570.mapId_2E4[0].field_0 &&
                saveData_8008B570.mapId_2E4[1].field_2 == saveData_8008B570.mapId_2E4[1].field_0 &&
                saveData_8008B570.mapId_2E4[2].field_2 == saveData_8008B570.mapId_2E4[2].field_0)
            {
            }
            else
            {
                if (dword_80091C54)
                {
                    sub_800ADDAC();
                }
                if (sub_800A683C(-1) != MAP_ENTRY_CF8(saveData_8008B570.mapId_2E4[2].field_0).f6)
                {
                    sub_800AD124(0);
                }
                e = dword_800B0608[saveData_8008B570.mapId_2E4[0].field_0][saveData_8008B570.mapId_2E4[1].field_0];
                for (dword_80091CB0 = 0; e[dword_80091CB0].f0 != -1; dword_80091CB0++)
                {
                }
                v[1] = MAP_ENTRY_CF8(saveData_8008B570.mapId_2E4[2].field_2).f6;
                v[0] = MAP_ENTRY_CF8(saveData_8008B570.mapId_2E4[2].field_0).f6;
                t = sub_800A5030(v[0], v[1], dword_80091C90);
                sub_800A52AC(v[0]);
                dword_80091C54 = 1;
                dword_80082670 = 0;
                dword_80091C9C = 0;
                saveData_8008B570.mapId_2E4[0].field_2 = saveData_8008B570.mapId_2E4[0].field_0;
                saveData_8008B570.mapId_2E4[1].field_2 = saveData_8008B570.mapId_2E4[1].field_0;
                saveData_8008B570.mapId_2E4[2].field_2 = saveData_8008B570.mapId_2E4[2].field_0;
                if ((unsigned short)(saveData_8008B570.mapId_2E4[0].field_0 - 1) < 2)
                {
                    unknownFlags_8008D678 |= 0x1000000;
                }
                else
                {
                    unknownFlags_8008D678 &= ~0x1000000;
                }
                sub_80025C38((struct_112*)sub_800AC38C(), (((unsigned int)unknownFlags_8008D678 >> 24) ^ 1) & 1);
                dword_80091CA0 = 0;
                if (dword_80091C90 != 0 || MAP_ENTRY_CF8(saveData_8008B570.mapId_2E4[2].field_0).fA != 0 || t != 0)
                {
                    dword_80091CA0 = 1;
                }
                dword_80091C90 = MAP_ENTRY_CF8(saveData_8008B570.mapId_2E4[2].field_0).fA;
                sub_80027118();
                sub_8002728C();
                m = MAP_ENTRY_CF8(saveData_8008B570.mapId_2E4[2].field_0).f8;
                if (m >= 0)
                {
                    if (sub_800AD154(12) == 1 && m == 0xD)
                    {
                        m = 0xF;
                    }
                    else if (sub_800AD154(12) == 2 && m == 0xD)
                    {
                        m = 0x91;
                    }
                    else if (sub_800AD154(12) == 3 && m == 0x29)
                    {
                        m = 0x26;
                    }
                    else if (sub_800AD154(12) == 4 && m == 0x2A)
                    {
                        m = 0x25;
                    }
                    PlayMusic_800300E0(m, 1);
                    sub_800315D8(m);
                    sub_80027478(0x20, 1);
                }
                if (dword_80091C90 == 0 && dword_80091C58 != 0)
                {
                    sub_800B88A4(t);
                    k = a1[0];
                    eventDispatchHalt_8008B540 = 1;
                    n = k;
                    a1[0] = n + 1;
                    sub_80027478(0x10, 1);
                    break;
                }
                a1[0] += 1;
            }
        }
        if (a1[0] != 1)
        {
            break;
        }
    case 1:
        req[0] = 0x2C;
        req[1] = MAP_ENTRY_CF8(saveData_8008B570.mapId_2E4[2].field_0).f0;
        req[2] = 0;
        req[3] = 0;
        req[4] = 0;
        req[5] = 0;
        req[6] = 0;
        req[7] = (int)sub_80028808;
        a1[1] = QueueFileRequest_8003BC84(req);
        sub_80027478(2, 1);
        n = a1[0];
        eventDispatchHalt_8008B540 = 1;
        a1[0] = n + 1;
        break;
    case 2:
        if (IsSoundTaskReady_800306B0() && IsModelLoaderDone_800205D0() && GetFileRequestStatus_8003BE30(a1[1]) == 0)
        {
            sub_80027478(0x72, 0);
            a1[0] = 0;
        }
        else
        {
            eventDispatchHalt_8008B540 = 1;
        }
        break;
    }
}
#endif
INCLUDE_ASM(sub_80027CF8);
// Matched
// Matched
void sub_8002830C(struct_obj_D* p)
{
    short* s = (short*)&saveData_8008B570;
    s[0x2E6 / 2] = -1;
    s[0x2EA / 2] = -1;
    s[0x2EE / 2] = -1;
    s[0x2F2 / 2] = -1;
    unknownFlags_8008D678 &= ~0x20000;
    dword_80091CA0 = 1;
    sub_80027118();
    sub_8002728C();
    p->field_8 = (void (*)(void))sub_80027CC0;
}
// Matched
void sub_80028388(struct_obj_D* p, int* q)
{
    q[0] = 0;
    q[1] = 0;
    sub_800283C0(p, q);
    p->field_8 = (void (*)(void))sub_800283C0;
}
extern int sub_800A6D50(int a0);
extern int dword_800B1228;
extern void sub_80028C60();
// Matched
void sub_800283C0(void* a0, int* a)
{
    int* a1 = a;
    int req[8];
    int req2[8];
    int req3[8];
    int s;
    int load;
    int wait;
    s = a1[0];
    switch (s)
    {
    case 0:
        if (sub_800A6D50(0) != 1 && dword_80082670 == 0)
        {
            break;
        }
        if (dword_800B1228 & 0x4000)
        {
            break;
        }
        if (word_80091C40[1] != word_80091C40[0])
        {
            req[0] = 0xC69;
            req[1] = dword_800B0608[saveData_8008B570.mapId_2E4[0].field_0][saveData_8008B570.mapId_2E4[1].field_0][saveData_8008B570.mapId_2E4[2].field_0].f2;
            req[2] = dword_80082674[word_80091C40[0] * 3];
            req[3] = dword_80082674[word_80091C40[0] * 3 + (dword_80082670 ? 2 : 1)];
            req[4] = 0;
            req[5] = 0;
            req[6] = 0;
            req[7] = (int)sub_80028C60;
            a1[1] = QueueFileRequest_8003BC84(req);
            dword_80082678 = 1;
            word_80091C40[1] = word_80091C40[0];
            break;
        }
        if (saveData_8008B570.mapId_2E4[3].field_2 != saveData_8008B570.mapId_2E4[3].field_0)
        {
            load = 1;
            wait = 2;
            if (dword_80082670 == 0)
            {
                sub_8002728C();
            }
            if (dword_80082678)
            {
                if (word_80091C40[0] == saveData_8008B570.mapId_2E4[3].field_0)
                {
                    load = 0;
                }
                wait = ConsumeFileRequest_8003BFD0(a1[1], 1);
                dword_80082678 = 0;
            }
            if (load)
            {
                req2[0] = 0x46C;
                req2[1] = dword_800B0608[saveData_8008B570.mapId_2E4[0].field_0][saveData_8008B570.mapId_2E4[1].field_0][saveData_8008B570.mapId_2E4[2].field_0].f2;
                req2[2] = dword_80082674[saveData_8008B570.mapId_2E4[3].field_0 * 3];
                req2[3] = dword_80082674[saveData_8008B570.mapId_2E4[3].field_0 * 3 + (dword_80082670 ? 2 : 1)];
                req2[4] = 0;
                req2[5] = 0;
                req2[6] = 0;
                req2[7] = (int)sub_80028C60;
                a1[1] = QueueFileRequest_8003BC84(req2);
            }
            word_80091CB8[7] = saveData_8008B570.mapId_2E4[3].field_0;
            word_80091CB8[6] = saveData_8008B570.mapId_2E4[3].field_0;
            saveData_8008B570.mapId_2E4[3].field_2 = saveData_8008B570.mapId_2E4[3].field_0;
            if (wait)
            {
                if (dword_80082670 == 0)
                {
                    sub_80027478(4, 1);
                }
                eventDispatchHalt_8008B540 = 1;
                a1[0] = 1;
            }
            break;
        }
        if (word_80091CB8[6] != word_80091CB8[7])
        {
            req3[0] = 0x450;
            req3[1] = dword_800B0608[saveData_8008B570.mapId_2E4[0].field_0][saveData_8008B570.mapId_2E4[1].field_0][saveData_8008B570.mapId_2E4[2].field_0].f2;
            req3[2] = dword_80082674[word_80091CB8[6] * 3];
            req3[3] = 0;
            req3[4] = 0;
            req3[5] = 0;
            req3[6] = 0;
            req3[7] = 0;
            word_80091CB8[7] = word_80091CB8[6];
            a1[1] = QueueFileRequest_8003BC84(req3);
            a1[0] = 2;
        }
        break;
    case 1:
        if (GetFileRequestStatus_8003BE30(a1[1]) == 0)
        {
            dword_80082670 = 0;
            dword_80082668 = 0;
            sub_80028DC0();
            sub_80027478(4, 0);
            a1[0] = 0;
        }
        else
        {
            eventDispatchHalt_8008B540 = 1;
        }
        break;
    case 2:
        if (GetFileRequestStatus_8003BE30(a1[1]) == 0)
        {
            a1[0] = 0;
        }
        break;
    }
}
typedef struct
{
    int x;
    int y;
    int z;
    short rx;
    short ry;
    short rz;
} PosRot;
typedef struct
{
    char pad_0[0xC];
    int fC;
} MapEntry16b;
typedef struct
{
    char pad_0[0x7A8];
    PosRot pos;
} SaveData7A8;
extern void sub_800A5628(int a0, int* a1, int a2);
extern void sub_800B73C0(int a0, int a1);
extern int sub_800B76B8(char* a0, PosRot* a1);
extern int* sub_80027A88();
extern unsigned int* dword_80073210;
extern short dword_80091CA8[];
extern char* dword_8008B4A4;
#if 0
// Not matched: 2 instructions: in the mapIdx >= 0 branch the original loads the index (lhu) before the -1 store to field_2
void sub_80028808(void* a0, int* a1)
{
    char buf[0x104];
    int n;
    int* p;
    unsigned int cnt;
    unsigned int i;
    unsigned int j;
    int a;
    int c;
    int c2;
    p = a1;
    n = *p++;
    if (n != 0 && dword_80091C8C == 0)
    {
        MemCopy_800403E8(dword_80073210, (unsigned int*)p, n);
        dword_80091CB4 = ((MapEntry16b*)dword_800B0608[saveData_8008B570.mapId_2E4[0].field_0][saveData_8008B570.mapId_2E4[1].field_0])[saveData_8008B570.mapId_2E4[2].field_0].fC;
    }
    p = (int*)((char*)p + n);
    dword_80082668 = 1;
    dword_8008266C = n != 0;
    cnt = *p++;
    for (j = 0; j < cnt; j++)
    {
        a = *p++;
        c = *p++;
        c2 = *p++;
        sub_800A5628(a, p, c);
        p = (int*)((char*)p + c2);
    }
    dword_8008B500[0] = saveData_8008B570.mapId_2E4[2].field_0;
    dword_8008B500[1] = *p++;
    dword_8008B500[2] = *p++;
    MemCopy_800403E8((unsigned int*)buf, (unsigned int*)p, 0x104);
    p = sub_80027A88(&dword_8008B500[3], &dword_8008B500[1], &dword_80091C68, (char*)p + 0x104);
    sub_800B73C0(dword_8008B500[3], dword_8008B500[1]);
    p = sub_80027A88(&dword_8008B500[5], &dword_8008B500[4], &dword_80091C68, p);
    sub_800B73C0(dword_8008B500[5], dword_8008B500[4]);
    sub_800275E8((char**)&dword_8008B500[6], dword_8008B500[4], (int)&dword_80091C68);
    p = sub_80027A88(&dword_8008B500[10], &dword_8008B500[9], &dword_80091C68, p);
    sub_800B73C0(dword_8008B500[10], dword_8008B500[9]);
    p = sub_80027A88(&dword_8008B500[12], &dword_8008B500[11], &dword_80091C68, p);
    sub_800B73C0(dword_8008B500[12], dword_8008B500[11]);
    sub_800275E8((char**)&dword_8008B500[13], dword_8008B500[11], (int)&dword_80091C68);
    p = sub_80027A88(&dword_8008B500[8], &dword_8008B500[7], &dword_80091C68, p);
    sub_800B73C0(dword_8008B500[8], dword_8008B500[7]);
    cnt = p[0];
    sub_80027708(p, (int)&dword_80091C68);
    p = (int*)((char*)p + cnt);
    cnt = *p++;
    LoadTiy_80028E74(0, 0, 0, (int)p, (int)&dword_80091C68);
    p = sub_80027650((int*)((char*)p + cnt), 0, (int)&dword_80091C68);
    dword_80082674 = (int*)ListAlloc_8003FDC0(&dword_80091C68, dword_8008B500[1] * 12);
    MemCopy_800403E8((unsigned int*)dword_80082674, (unsigned int*)p, dword_8008B500[1] * 12);
    if (dword_8008266C && dword_80091C5C && dword_80091C8C == 0 && dword_80091CB4)
    {
        ((void (*)(int))dword_80091CB4)(0);
    }
    if (dword_80091C98)
    {
        ((SaveData7A8*)&saveData_8008B570)->pos.x = stru_80091C78.pos[0];
        ((SaveData7A8*)&saveData_8008B570)->pos.y = stru_80091C78.pos[1];
        ((SaveData7A8*)&saveData_8008B570)->pos.z = stru_80091C78.pos[2];
        ((SaveData7A8*)&saveData_8008B570)->pos.rx = dword_80091CA8[0];
        ((SaveData7A8*)&saveData_8008B570)->pos.ry = dword_80091CA8[1];
        ((SaveData7A8*)&saveData_8008B570)->pos.rz = dword_80091CA8[2];
    }
    dword_80091C98 = 0;
    if (dword_80091C94)
    {
        ((SaveData7A8*)&saveData_8008B570)->pos.x = ((PosRot*)buf)->x;
        ((SaveData7A8*)&saveData_8008B570)->pos.y = ((PosRot*)buf)->y;
        ((SaveData7A8*)&saveData_8008B570)->pos.z = ((PosRot*)buf)->z;
        ((SaveData7A8*)&saveData_8008B570)->pos.rx = ((PosRot*)buf)->rx;
        ((SaveData7A8*)&saveData_8008B570)->pos.ry = ((PosRot*)buf)->ry;
        ((SaveData7A8*)&saveData_8008B570)->pos.rz = ((PosRot*)buf)->rz;
    }
    dword_80091C94 = 0;
    if (((int*)&stru_80091C78)[3] >= 0)
    {
        saveData_8008B570.mapId_2E4[3].field_0 = ((int*)&stru_80091C78)[3];
        saveData_8008B570.mapId_2E4[3].field_2 = -1;
        ((int*)&stru_80091C78)[3] = -1;
    }
    else
    {
        for (i = 0; i < dword_8008B500[1]; i++)
        {
            if (sub_800B76B8((char*)dword_8008B500[3] + i * 8, &((SaveData7A8*)&saveData_8008B570)->pos) >= 0)
            {
                saveData_8008B570.mapId_2E4[3].field_0 = i;
                saveData_8008B570.mapId_2E4[3].field_2 = -1;
                break;
            }
        }
    }
    *(int*)(*(char**)(dword_8008B4A4 + 0x24) + 0x84) = saveData_8008B570.mapId_2E4[3].field_0;
}
#endif
INCLUDE_ASM(sub_80028808);
