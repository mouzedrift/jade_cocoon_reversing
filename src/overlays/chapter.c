// CHAPTER.BIN
#include "common.h"
#include "funcs.h"
#include "globals.h"

typedef struct ChapterVec
{
    short x;
    short y;
    short z;
} ChapterVec;

// view on saveData_8008B570 (+0x2DC)
typedef struct ChapterSave
{
    char pad_0[0x2DC];
    short cur_2DC;
    short next_2DE;
    short field_2E0;
    short pad_2E2;
    short x_2E4;
    short pad_2E6;
    short y_2E8;
    short pad_2EA;
    short z_2EC;
    short pad_2EE;
    short field_2F0;
} ChapterSave;

typedef struct ChapterEntry
{
    short field_0;
    short pad_2;
    int field_4;
    char pad_8[0xC];
    int field_14;
    int field_18;
} ChapterEntry;

extern int dword_800B0624[6];
extern int dword_800B70A4[];
extern ChapterEntry dword_800B6FE0[];
extern int dword_80091C54;
extern int dword_80091C94;
extern int eventDispatchHalt_8008B540;
extern void sub_800AD16C(int, int);
extern void sub_800ADC5C(ChapterVec*, int);
extern void sub_800ADCEC(ChapterVec*, int);
extern void sub_800A6D30(int);
extern void sub_800B69BC(int**);
extern void sub_800B6A94(short*);

INCLUDE_OVERLAY_ASM(chapter, dword_800B66C0);

INCLUDE_OVERLAY_ASM(chapter, sub_800B66F4);

void sub_800B68A8()
{
    int i = 0;
    int a = dword_800B70A4[0];
    while (a != 0x14)
    {
        sub_800AD16C(a, 0);
        a = dword_800B70A4[++i];
    }
}

#define CHAPTER_SAVE ((ChapterSave*)&saveData_8008B570)

void sub_800B6900()
{
    int i;
    if (CHAPTER_SAVE->next_2DE < 0)
    {
        CHAPTER_SAVE->next_2DE = 0;
    }
    for (i = CHAPTER_SAVE->next_2DE; i <= CHAPTER_SAVE->cur_2DC; i++)
    {
        sub_800B69BC((int**)dword_800B6FE0[i].field_14);
        sub_800B6A94((short*)dword_800B6FE0[i].field_18);
    }
    CHAPTER_SAVE->next_2DE = CHAPTER_SAVE->cur_2DC + 1;
}

void sub_800B69BC(int** p)
{
    ChapterVec v;
    int i;
    int j;
    for (i = 0; i < 6; i++)
    {
        int* arr = p[i];
        j = 0;
        if (arr)
        {
            while (j < dword_800B0624[i])
            {
                v.x = i;
                v.y = j;
                v.z = 0;
                sub_800ADC5C(&v, arr[j]);
                j++;
            }
        }
    }
}

void sub_800B6A94(short* p)
{
    ChapterVec v;
    while (p[3] != -1)
    {
        v.x = p[0];
        v.y = p[1];
        v.z = p[2];
        sub_800ADC5C(&v, p[3]);
        p += 4;
    }
}

void sub_800B6B18()
{
    ChapterSave* s = (ChapterSave*)&saveData_8008B570;
    ChapterEntry* e = &dword_800B6FE0[s->cur_2DC];
    ChapterVec v;
    sub_800ADCEC(&v, e->field_4);
    dword_80091C54 = 0;
    s->next_2DE = s->cur_2DC + 1;
    s->field_2E0 = e->field_0;
    dword_80091C94 = 1;
    s->x_2E4 = v.x;
    s->y_2E8 = v.y;
    s->z_2EC = v.z;
    s->field_2F0 = 0;
    sub_800A6D30(1);
    eventDispatchHalt_8008B540 = 1;
}

INCLUDE_OVERLAY_ASM(chapter, dword_800B6BC4);
