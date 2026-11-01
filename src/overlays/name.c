// NAME.BIN - player name selection screen, loaded at 0x800B6D00
#include "funcs.h"
#include "globals.h"

typedef struct
{
    unsigned short flags_0;
    char pad_2[6];
    short field_8;
    short pad_A;
    short field_C;
    short pad_E;
    short name_10[10]; // SJIS characters, the first byte of a full-width character is >= 0x81
    short buffer_24[2];
    short field_28[10];
    short pad_3C[4];
    short length_44; // length of name_10 in bytes
} NameEntry;

extern int dword_800B83F8;
extern char defaultName_800B83B8[0x14];
extern unsigned short word_8009194C;
extern void sub_800B7AB4(NameEntry* p);
extern void sub_800B7F08(NameEntry* p);
extern void sub_800B7CA4(NameEntry* p);

// Matched
int sub_800B6FC8(void)
{
    return dword_800B83F8;
}

// Matched
void sub_800B7A88(NameEntry* p)
{
    sub_800B7AB4(p);
    sub_800B7CA4(p);
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

// Not matched: the original adds the byte offset first (addu $v0,$v0,$a0)
void sub_800B7C68(NameEntry* p)
{
    if (p->length_44)
    {
        *(short*)((char*)p + p->length_44 + 0x10) = 0;
        p->length_44 -= 2;
        *(short*)((char*)p + p->length_44 + 0x10) = 0;
    }
}

// Not matched: the original keeps a separate pointer and rotates the loop differently
int sub_800B7F70(NameEntry* p)
{
    int n = 0;
    short* q = p->field_28;
    do
    {
        if (*q == 0)
        {
            break;
        }
        n++;
        q++;
    } while (n < 10);
    return n * 2;
}

// Matched
void sub_800B7FA0(NameEntry* p)
{
    sub_800403E8((unsigned int*)p->name_10, (unsigned int*)defaultName_800B83B8, 0x14);
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
void sub_800B7D60(NameEntry* p)
{
    if (word_8009194C & 0x800)
    {
        p->field_8 = 2;
        p->field_C = 2;
    }
    if (word_8009194C & 0x100)
    {
        if (p->flags_0 & 8)
        {
            sub_800B7F08(p);
        }
    }
}
