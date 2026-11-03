// NAME.BIN - player name selection screen, loaded at 0x800B6D00
#include "common.h"
#include "funcs.h"
#include "globals.h"
typedef struct
{
    unsigned short flags_0;
    char pad_2[6];
    short field_8;
    short pad_A;
    short field_C;
    unsigned short pad_E;
    short name_10[10]; // SJIS characters, the first byte of a full-width character is >= 0x81
    short buffer_24[2];
    short field_28[10];
    short pad_3C[4];
    short length_44; // length of name_10 in bytes
} NameEntry;
extern int dword_800B83F8;
extern char defaultName_800B83B8[0x14];
extern unsigned short padPressed_8009194C;
extern short name_800C8204;
extern void sub_800B7AB4(NameEntry* p);
extern void sub_800B7F08(NameEntry* p);
extern int sub_800B7F70(NameEntry* p);
extern void sub_800B7CA4(NameEntry* p);

INCLUDE_OVERLAY_ASM(name, dword_800B6D00);

INCLUDE_OVERLAY_ASM(name, sub_800B6E4C);

// Matched
int sub_800B6FC8(void)
{
    return dword_800B83F8;
}

INCLUDE_OVERLAY_ASM(name, sub_800B6FD8);

INCLUDE_OVERLAY_ASM(name, sub_800B70F4);

INCLUDE_OVERLAY_ASM(name, sub_800B7414);

INCLUDE_OVERLAY_ASM(name, sub_800B75EC);

INCLUDE_OVERLAY_ASM(name, sub_800B78EC);

// Matched
void sub_800B7A88(NameEntry* p)
{
    sub_800B7AB4(p);
    sub_800B7CA4(p);
}

INCLUDE_OVERLAY_ASM(name, sub_800B7AB4);

void sub_800B7C68(NameEntry* p)
{
    if (p->length_44)
    {
        *(short*)((char*)p->name_10 + p->length_44) = 0;
        p->length_44 -= 2;
        *(short*)((char*)p->name_10 + p->length_44) = 0;
    }
}

// Matched
void sub_800B7CA4(NameEntry* p)
{
    if (p->length_44 >= 0x15)
    {
        p->length_44 = 0x14;
    }
    if (p->length_44 < 0)
    {
        p->length_44 = 0;
    }
}

#if 0
// Not matched: the original loads the limit after the sign extension of the incremented index
void sub_800B7CD8(NameEntry* p)
{
    if (padPressed_8009194C & 2)
    {
        if (++p->pad_A > name_800C8204 - 1)
        {
            p->pad_A = 0;
        }
    }
    else if (padPressed_8009194C & 8)
    {
        p->pad_A--;
        if (p->pad_A < 0)
        {
            p->pad_A = name_800C8204 - 1;
        }
    }
}
#endif

INCLUDE_OVERLAY_ASM(name, sub_800B7CD8);

// Matched
void sub_800B7D60(NameEntry* p)
{
    if (padPressed_8009194C & 0x800)
    {
        p->field_8 = 2;
        p->field_C = 2;
    }
    if (padPressed_8009194C & 0x100)
    {
        if (p->flags_0 & 8)
        {
            sub_800B7F08(p);
        }
    }
}

void sub_800B7DC4(NameEntry* p)
{
    if (IsConfirmPressedP1_8003D380(0))
    {
        if (p->field_C >= 2)
        {
            return;
        }
        if (p->field_C < 0)
        {
            return;
        }
        p->pad_A = p->field_C;
    }
    if (IsCancelPressedP1_8003D41C(0))
    {
        p->field_8 = 0;
        p->field_C = p->pad_E;
    }
}

INCLUDE_OVERLAY_ASM(name, sub_800B7E30);

// Matched
void sub_800B7F08(NameEntry* p)
{
    int i;
    short* s;

    MemCopy_800403E8((unsigned int*)p->name_10, (unsigned int*)p->field_28, 0x14);
    s = p->field_28;
    i = 0;
    for (i = 0; i < 10; s++)
    {
        i++;
        if (*s == 0)
        {
            break;
        }
    }
    p->length_44 = sub_800B7F70(p);
}

int sub_800B7F70(NameEntry* p)
{
    int n;
    short* q;
    for (n = 0, q = p->field_28; n < 10; n++, q++)
    {
        if (*q == 0)
        {
            break;
        }
    }
    return n * 2;
}

// Matched
void sub_800B7FA0(NameEntry* p)
{
    MemCopy_800403E8((unsigned int*)p->name_10, (unsigned int*)defaultName_800B83B8, 0x14);
    p->length_44 = 0;
}

// Matched
int sub_800B7FD8(unsigned char* p)
{
    int n = 0;
    do
    {
        if (*p != 0x91)
        {
            if (*p != 0)
            {
                return 0;
            }
        }
        n++;
        p += 2;
    } while (n < 10);
    return 1;
}

// Matched
void sub_800B8018(void)
{
}

typedef struct
{
    int flags;
    unsigned short s4;
    unsigned short s6;
    short s8;
    short sA;
} NameCursor;
extern short name_800B83C8[];
extern short name_800B83D0[];
void sub_800B8020(NameCursor* p, int k)
{
    if (p->flags & name_800B83C8[k - 1])
    {
        if ((p->flags & 1) && (unsigned)(k - 1) < 2)
        {
            p->s6 += name_800B83D0[k - 1] * (p->s8 - 1);
        }
        else if ((p->flags & 2) && (unsigned)(k - 3) < 2)
        {
            p->s6 += name_800B83D0[k - 1] * p->s8 * (p->sA - 1);
        }
    }
}

typedef struct
{
    int mask;
    int result;
} NameCursorTbl;
extern NameCursorTbl name_800B83D8[];
extern int sub_8003D630();
extern void PlaySfx_80031494(int);
int sub_800B80E4(NameCursor* p)
{
    int old = (short)p->s6;
    int k = sub_8003D630();
    if (k)
    {
        sub_800B8020(p, k);
        if (p->flags & name_800B83D8[k - 1].mask)
        {
            PlaySfx_80031494(0x7F);
            return name_800B83D8[k - 1].result;
        }
    }
    if (old != (short)p->s6)
    {
        PlaySfx_80031494(0x7F);
    }
    return 0;
}

INCLUDE_OVERLAY_ASM(name, dword_800B8190);
