// COMBSEL.BIN
#include "common.h"
#include "funcs.h"
#include "globals.h"

typedef struct CombSelTask
{
    unsigned int flags_0;
    int field_4;
    void (*next_8)();
} CombSelTask;

typedef struct CombSelUnit
{
    char pad_0[0xF8];
} CombSelUnit;

typedef struct CombSelItem
{
    char pad_0[0x10];
    short field_10;
} CombSelItem;

extern short* dword_800A566C[3];
extern short* dword_800A57E4[6];
extern short* dword_800A5930[5];
extern unsigned char byte_800A38D9;
extern void sub_800A4E4C();
typedef struct CombSelState
{
    char pad_0[8];
    short field_8;
} CombSelState;

extern CombSelState dword_800A1BBC;
extern short word_800A5968;
extern short word_800A5974;
extern CombSelUnit dword_800A1BC8[][15];
extern short word_800A1BC4;
extern CombSelUnit dword_800A3AA0[2][3];
extern int dword_800A3A94;
extern unsigned char byte_800A38DB;
extern char dword_800A5978[];
extern char dword_800A596C[];
extern void sub_800A16FC();
extern int sub_800A1934(void*);
extern void sub_800A4D64(CombSelUnit*);
extern void sub_800A197C(void*);
extern void sub_800A5538();
extern int sub_800A5560(CombSelUnit*, int);
extern int GetMenuCursorIndex_8003DA54(void*);
extern void PlaySfx_80031494(int);

INCLUDE_OVERLAY_ASM(combsel, dword_800A4088);

INCLUDE_OVERLAY_ASM(combsel, sub_800A4360);

void sub_800A4C74()
{
    short v[2];
    int i;
    for (i = 0; i < 3; i++)
    {
        v[0] = 0xA;
        v[1] = 0xA6;
        dword_800A566C[i][8] = v[*(volatile unsigned char*)&byte_800A38D9];
    }
    for (i = 0; i < 6; i++)
    {
        v[0] = 0x9B;
        v[1] = 0x15;
        dword_800A57E4[i][8] = v[*(volatile unsigned char*)&byte_800A38D9];
    }
    for (i = 0; i < 5; i++)
    {
        v[0] = 0xA;
        v[1] = 0xCA;
        dword_800A5930[i][8] = v[*(volatile unsigned char*)&byte_800A38D9];
    }
}

void sub_800A4D64(CombSelUnit* base)
{
    int i;
    int j;
    for (i = 0; i < 2; i++)
    {
        if (sub_800A1934(&base[i]) == 1)
        {
            for (j = i + 1; j < 3; j++)
            {
                if (sub_800A1934(&base[j]) == 0)
                {
                    MemCopy_800403E8((unsigned int*)&base[i], (unsigned int*)&base[j], 0xF8);
                    sub_800A197C(&base[j]);
                    break;
                }
            }
            if (j >= 3)
            {
                return;
            }
        }
    }
}

void sub_800A4E4C()
{
    int i;
    for (i = 0; i < 2; i++)
    {
        sub_800A4D64(dword_800A3AA0[i]);
    }
}

extern short word_800A5980;

void sub_800A4E94(CombSelTask* t, int a)
{
    if (IsConfirmPressed_8003D288(0, dword_800A3A94))
    {
        switch (word_800A1BC4)
        {
        case 0:
            PlaySfx_80031494(0x7E);
            t->next_8 = sub_800A16FC;
            t->next_8(t, a);
            break;
        case 1:
            if (sub_800A5560(dword_800A1BC8[byte_800A38D9], 6) == 1)
            {
                PlaySfx_80031494(0x7C);
            }
            else
            {
                PlaySfx_80031494(0x7E);
                byte_800A38DB = 2;
            }
            break;
        case 2:
            if (sub_800A5560(dword_800A3AA0[byte_800A38D9], 3) == 1)
            {
                PlaySfx_80031494(0x7C);
            }
            else
            {
                PlaySfx_80031494(0x7E);
                byte_800A38DB = 1;
            }
            break;
        case 3:
            sub_800A5080(t, a);
            break;
        case 4:
            PlaySfx_80031494(0x7E);
            byte_800A38DB = 3;
            word_800A5980 = 1;
            break;
        }
    }
    else if (IsCancelPressed_8003D3C0(1, dword_800A3A94))
    {
        switch (byte_800A38D9)
        {
        case 0:
            word_800A1BC4 = 4;
            break;
        case 1:
            word_800A1BC4 = 1;
            word_800A5968 = 0;
            byte_800A38D9 = 0;
            word_800A5974 = 0;
            break;
        }
    }
}

// Near miss: store order of the case 0 assignments
#if 0
void sub_800A5080(CombSelTask* t, int a)
{
    if (sub_800A5560(dword_800A3AA0[byte_800A38D9], 3) == 1)
    {
        PlaySfx_80031494(0x7C);
    }
    else
    {
        byte_800A38DB = 0;
        dword_800A1BBC.field_8 = 3;
        PlaySfx_80031494(0x7E);
        switch (byte_800A38D9)
        {
        case 0:
            dword_800A1BBC.field_8 = 0;
            word_800A5968 = 0;
            byte_800A38D9 = 1;
            word_800A5974 = 0;
            break;
        case 1:
            sub_800A4E4C();
            t->next_8 = sub_800A16FC;
            t->next_8(t, a);
            break;
        }
    }
}
#endif
INCLUDE_OVERLAY_ASM(combsel, sub_800A5080);

extern char dword_800A5960[];

void sub_800A5188()
{
    if (IsConfirmPressed_8003D288(0, dword_800A3A94))
    {
        switch (word_800A1BC4)
        {
        case 1:
        {
            CombSelUnit* a = &dword_800A3AA0[byte_800A38D9][(short)GetMenuCursorIndex_8003DA54(dword_800A5960)];
            CombSelUnit* b = &dword_800A1BC8[byte_800A38D9][(short)GetMenuCursorIndex_8003DA54(dword_800A596C)];
            MemCopy_800403E8((unsigned int*)a, (unsigned int*)b, 0xF8);
            byte_800A38DB = 2;
            PlaySfx_80031494(0x7E);
            break;
        }
        case 2:
            if (sub_800A1934(&dword_800A3AA0[byte_800A38D9][(short)GetMenuCursorIndex_8003DA54(dword_800A5960)]) == 1)
            {
                PlaySfx_80031494(0x7C);
            }
            else
            {
                PlaySfx_80031494(0x7E);
                sub_800A197C(&dword_800A3AA0[byte_800A38D9][(short)GetMenuCursorIndex_8003DA54(dword_800A5960)]);
                byte_800A38DB = 0;
            }
            break;
        }
    }
    else if (IsCancelPressed_8003D3C0(1, dword_800A3A94))
    {
        switch (word_800A1BC4)
        {
        case 1:
            byte_800A38DB = 2;
            break;
        case 2:
            byte_800A38DB = 0;
            break;
        }
    }
}

void sub_800A53B0()
{
    short s;
    if (IsConfirmPressed_8003D288(0, dword_800A3A94))
    {
        s = word_800A1BC4;
        if (s == 1)
        {
            short r = GetMenuCursorIndex_8003DA54(dword_800A596C);
            if (sub_800A1934(&dword_800A1BC8[byte_800A38D9][r]) == 1)
            {
                PlaySfx_80031494(0x7C);
            }
            else
            {
                byte_800A38DB = 1;
                PlaySfx_80031494(0x7E);
            }
        }
    }
    else if (IsCancelPressed_8003D3C0(1, dword_800A3A94))
    {
        byte_800A38DB = 0;
        if (sub_800A1AAC(byte_800A38D9))
        {
            word_800A1BC4 = 3;
        }
    }
}

void sub_800A54A0(CombSelTask* t)
{
    if (IsConfirmPressed_8003D288(0, dword_800A3A94))
    {
        PlaySfx_80031494(0x7E);
        if ((short)GetMenuCursorIndex_8003DA54(dword_800A5978) == 0)
        {
            XaRequestPlay_80043564(1, 0x678, 0x1F);
            t->next_8 = sub_800A5538;
        }
        else
        {
            byte_800A38DB = 0;
        }
    }
    else if (IsCancelPressed_8003D3C0(1, dword_800A3A94))
    {
        byte_800A38DB = 0;
    }
}

void sub_800A5538(CombSelTask* t)
{
    t->next_8 = sub_800A16FC;
    t->next_8(t);
}

int sub_800A5560(CombSelUnit* p, int n)
{
    int i;
    for (i = 0; i < n; i++)
    {
        if (sub_800A1934(p + i) == 0)
        {
            return 0;
        }
    }
    return 1;
}

INCLUDE_OVERLAY_ASM(combsel, dword_800A55C4);
