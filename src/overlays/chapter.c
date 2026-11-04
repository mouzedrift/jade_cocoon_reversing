// CHAPTER.BIN
#include "common.h"
#include "funcs.h"
#include "globals.h"
#include "sound.h"
#include "chapter.h"

typedef struct ChapterVec
{
    short x;
    short y;
    short z;
} ChapterVec;

extern int dword_800B0624[6];
extern int dword_80091C54;
extern int dword_80091C94;
extern int eventDispatchHalt_8008B540;
extern void sub_800AD16C(int, int);
extern void sub_800ADC5C(ChapterVec*, int);
extern void sub_800ADCEC(ChapterVec*, int);
extern void sub_800A6D30(int);
extern void sub_800B69BC(int**);
extern void sub_800B6A94(short*);

int dword_800B66C0 SDATA = 28;


extern int PlayMusic_800300E0(int idx, int a1);

typedef struct ChapterTask
{
    int flags_0;
    int f4_4;
    void (*next_8)();
} ChapterTask;

extern void sub_800B68A8();
extern void sub_800B6900();
extern void EnterChapterMap_800B6B18();
extern void sub_800A7690();
extern void SsSepSetDecrescendo(short, short, short, long);
void ChapterIntroTask_800B66F4(ChapterTask* t, int* st);

void ChapterStartTask_800B66DC(ChapterTask* t, int* st)
{
    st[0] = 0;
    st[1] = 0;
    t->next_8 = ChapterIntroTask_800B66F4;
}

void ChapterIntroTask_800B66F4(ChapterTask* t, int* st)
{
    switch (st[0])
    {
    case 0:
        PlayMusic_800300E0(chapterTable_800B6FE0[saveData_8008B570.chapter_2DC].music_8, 1);
        sub_800315D8(chapterTable_800B6FE0[saveData_8008B570.chapter_2DC].music_8);
        st[0]++;
        break;
    case 1:
        if (!IsSoundTaskReady_800306B0())
        {
            break;
        }
        st[0]++;
        break;
    case 2:
    case 3:
        st[0]++;
        break;
    case 4:
        PlayMovie_80040EB4(chapterTable_800B6FE0[saveData_8008B570.chapter_2DC].movie_10);
        if (chapterTable_800B6FE0[saveData_8008B570.chapter_2DC].fadeBgm_C)
        {
            if (bgmSound_80091CE0.field_4_seq_num >= 0)
            {
                SsSepSetDecrescendo(bgmSound_80091CE0.field_C_sep_access_num, bgmSound_80091CE0.field_4_seq_num, 0x7F, 0x78);
                bgmSound_80091CE0.field_4_seq_num = -1;
            }
            st[1] = 0x3C;
        }
        else
        {
            st[1] = 0;
        }
        st[0]++;
        break;
    case 5:
        if (--st[1] < 0)
        {
            sub_800B68A8();
            sub_800B6900();
            EnterChapterMap_800B6B18();
            t->next_8 = sub_800A7690;
        }
        break;
    }
}

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

void sub_800B6900()
{
    int i;
    if (saveData_8008B570.chapterNext_2DE < 0)
    {
        saveData_8008B570.chapterNext_2DE = 0;
    }
    for (i = saveData_8008B570.chapterNext_2DE; i <= saveData_8008B570.chapter_2DC; i++)
    {
        sub_800B69BC(chapterTable_800B6FE0[i].field_14);
        sub_800B6A94(chapterTable_800B6FE0[i].field_18);
    }
    saveData_8008B570.chapterNext_2DE = saveData_8008B570.chapter_2DC + 1;
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

void EnterChapterMap_800B6B18()
{
    SaveData* s = &saveData_8008B570;
    ChapterEntry* e = &chapterTable_800B6FE0[s->chapter_2DC];
    ChapterVec v;
    sub_800ADCEC(&v, e->field_4);
    dword_80091C54 = 0;
    s->chapterNext_2DE = s->chapter_2DC + 1;
    s->field_2E0 = e->field_0;
    dword_80091C94 = 1;
    s->mapId_2E4[0].field_0 = v.x;
    s->mapId_2E4[1].field_0 = v.y;
    s->mapId_2E4[2].field_0 = v.z;
    s->mapId_2E4[3].field_0 = 0;
    sub_800A6D30(1);
    eventDispatchHalt_8008B540 = 1;
}

int dword_800B6BC4[12] = {
    67, -1, -1, -1, 78, 83, -1, -1,
    -1, 94, 96, 98,
};
int *dword_800B6BF4[6] = { 0, 0, dword_800B6BC4 };
short dword_800B6C0C[8] = { 2, 4, 1, 80, 0, 0, 0, -1 };
int dword_800B6C1C[12] = {
    3, 10, 16, 20, 24, 32, 37, 50,
    54, 58, 62, 66,
};
int dword_800B6C4C[5] = { 105, -1, -1, -1, -1 };
int *dword_800B6C60[6] = { 0, dword_800B6C1C, 0, 0, dword_800B6C4C };
short dword_800B6C78[20] = {
    1, 4, 1, 28, 1, 6, 3, 41,
    1, 6, 4, 45, 4, 1, 6, 113,
    0, 0, 0, -1,
};
int dword_800B6CA0[12] = {
    4, 12, 17, 21, 25, 33, 37, 51,
    55, 59, 63, 66,
};
int dword_800B6CD0[5] = { 100, 106, -1, -1, -1 };
int *dword_800B6CE4[6] = { 0, dword_800B6CA0, 0, 0, dword_800B6CD0 };
short dword_800B6CFC[28] = {
    4, 1, 6, 112, 1, 4, 1, 29,
    1, 6, 3, 42, 1, 6, 4, 46,
    4, 2, 13, 133, 4, 2, 14, 135,
    0, 0, 0, -1,
};
int dword_800B6D34[12] = {
    5, 13, 18, 22, 26, 34, 37, 52,
    56, 60, 64, 66,
};
int dword_800B6D64[5] = { 100, 106, 118, -1, -1 };
int *dword_800B6D78[6] = { 0, dword_800B6D34, 0, 0, dword_800B6D64 };
short dword_800B6D90[20] = {
    1, 4, 1, 30, 1, 6, 3, 43,
    1, 6, 4, 47, 4, 3, 3, 141,
    0, 0, 0, -1,
};
int dword_800B6DB8[12] = {
    6, 14, 19, 23, 27, 35, 37, 53,
    57, 61, 65, 66,
};
int dword_800B6DE8[5] = { 100, 106, 118, 137, -1 };
int *dword_800B6DFC[6] = { 0, dword_800B6DB8, 0, 0, dword_800B6DE8 };
short dword_800B6E14[32] = {
    1, 4, 1, 31, 1, 6, 3, 44,
    1, 6, 4, 48, 4, 3, 11, 150,
    4, 3, 12, 152, 4, 3, 13, 154,
    4, 3, 14, 156, 0, 0, 0, -1,
};
int dword_800B6E54[12] = {
    -1, 70, 74, 76, -1, -1, 86, -1,
    -1, -1, -1, -1,
};
int dword_800B6E84[5] = { 104, 106, 118, 163, -1 };
int *dword_800B6E98[6] = { 0, 0, dword_800B6E54, 0, dword_800B6E84 };
short dword_800B6EB0[116] = {
    2, 6, 1, 87, 2, 6, 2, 91,
    4, 1, 9, 117, 4, 2, 14, 134,
    4, 2, 7, 126, 4, 3, 0, 163,
    4, 3, 1, 164, 4, 3, 2, 165,
    4, 3, 3, 166, 4, 3, 4, 167,
    4, 3, 5, 168, 4, 3, 6, 169,
    4, 3, 7, 170, 4, 3, 8, 171,
    4, 3, 9, 172, 4, 3, 10, 173,
    4, 3, 11, 174, 4, 3, 12, 175,
    4, 3, 13, 176, 4, 3, 14, 177,
    4, 3, 15, 178, 4, 3, 16, 179,
    4, 3, 17, 180, 4, 3, 18, 181,
    4, 3, 19, 182, 4, 3, 20, 183,
    4, 3, 21, 185, 4, 4, 9, 196,
    0, 0, 0, -1,
};
int *dword_800B6F98[6] = { 0 };
short dword_800B6FB0[24] = {
    5, 1, 7, 217, 5, 2, 7, 228,
    5, 3, 11, 249, 5, 3, 12, 251,
    5, 3, 13, 253, 0, 0, 0, -1,
};
ChapterEntry chapterTable_800B6FE0[7] = {
    { 1, 0, 84, 126, 0, 10, dword_800B6BF4, dword_800B6C0C },
    { 0, 0, 3, 128, 1, 13, dword_800B6C60, dword_800B6C78 },
    { 0, 0, 12, 128, 1, 14, dword_800B6CE4, dword_800B6CFC },
    { 0, 0, 13, 128, 1, 15, dword_800B6D78, dword_800B6D90 },
    { 0, 0, 14, 128, 1, 16, dword_800B6DFC, dword_800B6E14 },
    { 1, 0, 70, 145, 0, 18, dword_800B6E98, dword_800B6EB0 },
    { 1, 0, 206, 33, 0, 20, dword_800B6F98, dword_800B6FB0 },
};
int dword_800B70A4[4] = { 7, 8, 9, 20 };
