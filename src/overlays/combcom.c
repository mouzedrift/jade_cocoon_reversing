// COMBCOM.BIN
#include "common.h"
#include "funcs.h"
#include "globals.h"

typedef struct CombComTask
{
    unsigned int flags_0;
    int field_4;
    void (*next_8)();
} CombComTask;

typedef struct CombComDlg
{
    int f0;
    int f4;
    int f8;
    int fC;
} CombComDlg;

extern char dword_800CD298[];
extern char dword_800CD2A4[];
extern unsigned char byte_800CD839;
extern unsigned char byte_800CD83C;
extern unsigned char byte_800CD844;
extern unsigned char byte_800A85BD;
extern unsigned char dword_800A4078[];
extern short word_800CD2A8;
extern short word_800CD28C[];
extern unsigned short word_800CD3CC;
extern char dword_800CD468[];
extern void* dword_800CD490;
extern void* dword_800CD414;
extern char dword_800CD3CC[];
extern int dword_800A3A88;
extern int sub_800A11BC(int);
extern int sub_800A1AAC(int);
extern int sub_8003DA54(void*);
extern int sub_8001AE54(int);
extern void sub_8001AEC0(int, int);

INCLUDE_OVERLAY_ASM(combcom, dword_800C9E88);

INCLUDE_OVERLAY_ASM(combcom, sub_800CB7AC);

void sub_800CB88C()
{
    if (sub_8001AE54(sub_800A11BC(byte_800CD839)) >= 5)
    {
        word_800CD2A8 = sub_8001AE54(sub_800A11BC(byte_800CD839));
    }
    if (dword_800A3A88 & 2)
    {
        word_800CD28C[1] = 3;
        word_800CD28C[2] = 5;
        dword_800CD414 = dword_800CD3CC;
    }
}

void sub_800CB924()
{
    if (sub_800A1AAC(byte_800CD839) == 1)
    {
        dword_800CD490 = dword_800CD468;
        word_800CD3CC |= 2;
    }
}

INCLUDE_OVERLAY_ASM(combcom, sub_800CB974);

INCLUDE_OVERLAY_ASM(combcom, sub_800CBA20);

// Near miss: the two table lookups are not merged in the original
#if 0
void sub_800CBAD4(int a)
{
    unsigned char v;
    if ((a & 0xFF) == 3)
    {
        if (byte_800CD844 & 5)
        {
            v = dword_800A4078[byte_800CD839 * 4];
        }
        else
        {
            v = byte_800CD83C;
        }
    }
    else
    {
        v = dword_800A4078[byte_800CD839 * 4];
    }
    byte_800A85BD = v;
}
#endif
INCLUDE_OVERLAY_ASM(combcom, sub_800CBAD4);

INCLUDE_OVERLAY_ASM(combcom, sub_800CBB4C);

// Near miss: prologue store of ra is scheduled later than in the original
#if 0
void sub_800CBBE0(int p)
{
    short v[2];
    CombComDlg d;
    v[0] = 0xA;
    v[1] = 0x14;
    d.f0 = p;
    d.f4 = 0;
    d.f8 = 0;
    d.fC = 0;
    sub_8002AF10((int)&d, (int)v, 0xF);
}
#endif
INCLUDE_OVERLAY_ASM(combcom, sub_800CBBE0);

void sub_800CBC28()
{
    sub_80031BDC((short)sub_8003DA54(dword_800CD298));
}

void sub_800CBC58()
{
    int r = sub_800A11BC(byte_800CD839);
    sub_8001AEC0(r, (short)sub_8003DA54(dword_800CD2A4));
}

INCLUDE_OVERLAY_ASM(combcom, sub_800CBCA0);

INCLUDE_OVERLAY_ASM(combcom, sub_800CBEA4);

INCLUDE_OVERLAY_ASM(combcom, sub_800CC40C);

INCLUDE_OVERLAY_ASM(combcom, sub_800CC674);

INCLUDE_OVERLAY_ASM(combcom, sub_800CC9FC);

INCLUDE_OVERLAY_ASM(combcom, sub_800CCA94);

int sub_800CCD84()
{
    if ((byte_800CD844 & 4) == 0)
    {
        return 1 << (byte_800CD839 + 8);
    }
    return 1 << ((byte_800CD839 ^ 1) + 8);
}

INCLUDE_OVERLAY_ASM(combcom, sub_800CCDD0);

INCLUDE_OVERLAY_ASM(combcom, sub_800CCFCC);

INCLUDE_OVERLAY_ASM(combcom, sub_800CD0C8);

INCLUDE_OVERLAY_ASM(combcom, sub_800CD16C);

INCLUDE_OVERLAY_ASM(combcom, dword_800CD28C);
