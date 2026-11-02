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

typedef struct { unsigned short* tbl; int f4; int f8; } FontTblEntry;
extern FontTblEntry dword_8008685C[];
void sub_8003F58C(unsigned char* out, int n);
int sub_8003FB60(unsigned short* s);
unsigned char* sub_8003F748(int idx, unsigned char* s);
void sub_8003F610(unsigned short* out, int n);
extern void sub_8003E91C(int mode, int* buf, int a, int b);

typedef struct ListNode { struct ListNode* prev; struct ListNode* next; } ListNode;
typedef struct List { int count; ListNode* head; ListNode* tail; } List;

struct Heap;
typedef struct HeapBlock
{
    int magic;
    unsigned int size;
    struct HeapBlock* prev;
    struct HeapBlock* next;
} HeapBlock;

typedef struct Heap
{
    int magic;
    int inited;
    unsigned int size;
    int count;
    int field_10;
    unsigned int used;
    void* buffer;
    HeapBlock* head;
    HeapBlock* tail;
} Heap;

extern HeapBlock* sub_80040150(Heap* h, unsigned int size);
extern void* sub_8003FFD0(Heap* h, unsigned int size);
extern void sub_800400B4(Heap* h, void* p);
extern void* sub_8003FDC0(List* l, int size);
extern void sub_8003FE38(void* arg0, int arg1);

INCLUDE_DATA(dword_80098198);
INCLUDE_DATA(dword_80098688);

#if 0
// Not matched: registers of a0/a2 swapped ($16/$17)
void sub_8003EF74(int a0, int a1, int a2)
{
    int buf[6];
    sub_8003F610(buf);
    sub_8003E91C(2, buf, a0, a2);
}
#endif
INCLUDE_ASM(sub_8003EF74);
INCLUDE_ASM(sub_8003EFBC);
INCLUDE_ASM(sub_8003F264);
#if 0
// Not matched: registers of a0/a2 swapped ($16/$17)
void sub_8003F544(int a0, int a1, int a2)
{
    int buf[6];
    sub_8003F610(buf);
    sub_8003E91C(1, buf, a0, a2);
}
#endif
INCLUDE_ASM(sub_8003F544);
// Matched
void sub_8003F58C(unsigned char* out, int n)
{
    int neg = 1;
    if (n >= 0)
    {
        n = -n;
        neg = 0;
    }
    do
    {
        *out++ = 0x82;
        *out++ = -(n % 10) + 0x4F;
        n /= 10;
    } while (n);
    if (neg)
    {
        *out++ = 0x81;
        *out++ = 0x7C;
    }
    out[0] = 0;
    out[1] = 0;
}
// Matched
void sub_8003F610(unsigned short* out, int n)
{
    unsigned short buf[12];
    unsigned short* start = out;
    int len;
    sub_8003F58C((unsigned char*)buf, n);
    len = sub_8003FB60(buf);
    do
    {
        *out++ = buf[--len];
    } while (len);
    *out = 0;
    sub_8003F684(2, (int)start);
}
#if 0
unsigned short* sub_8003F684(int a0, int a1)
{
    return 0;
}
#endif
INCLUDE_ASM(sub_8003F684);
// Matched
unsigned char* sub_8003F748(int idx, unsigned char* s)
{
    unsigned short* tbl = dword_8008685C[idx].tbl;
    unsigned short* p = (unsigned short*)s;
    if (s && *s)
    {
        do
        {
            if (*p < 0x2081)
            {
                *p = tbl[*p - 1];
            }
            p++;
        } while (*(unsigned char*)p);
    }
    return s;
}
#if 0
// Not matched: a0 (i) / a1 (p) moves before the loop swapped
void sub_8003F7C8(void* src, unsigned char* out)
{
    unsigned short buf[12];
    unsigned short* p;
    int done = 0;
    int i;
    unsigned char c;
    sub_800403E8((unsigned int*)buf, (unsigned int*)src, 0x16);
    p = sub_8003F684(1, (int)sub_8003F748(2, (unsigned char*)buf));
    for (i = 0; i < 10; i++)
    {
        c = 0;
        if (!done)
        {
            c = *(unsigned char*)p;
            if (c == 0)
            {
                done = 1;
            }
        }
        p++;
        out[i] = c;
    }
    out[10] = 0;
}
#endif
INCLUDE_ASM(sub_8003F7C8);
// Matched
int CopyPlayerName_8003F860(unsigned char* pPlayerIn, unsigned short* pPlayerOut)
{
    int i;

    if (*pPlayerOut == 0xFFFF)
    {
        for (i = 0; i < MAX_PLAYER_NAME_LENGTH; i++)
        {
            pPlayerOut[i] = pPlayerIn[i];
        }
        return 1;
    }

    return 0;
}
#if 0
// Not matched: second byte swap masks into a new reg (andi $v1 vs $v0, 2 instrs)
void sub_8003F89C(unsigned short* p)
{
    int i;
    unsigned short v;
    for (i = 0; i < 10; i++)
    {
        v = (*p >> 8) + ((*p & 0xFF) << 8);
        if ((unsigned short)(v - 0x8281) < 26)
        {
            v += 0xFFDF;
            *p = (v >> 8) + ((v & 0xFF) << 8);
        }
        p++;
    }
}
#endif
INCLUDE_ASM(sub_8003F89C);
// Matched
void sub_8003F900(int idx, short val)
{
    struct_2C* p = &dword_80095FB0[idx];
    p->field_2A = val;
}
// Matched
void sub_8003F928(int idx, int v)
{
    struct_2C* p = &dword_80095FB0[idx];
    p->field_E = GetClut(p->field_20, p->field_22 + v);
}
// Matched
void sub_8003F978(int idx, int c)
{
    struct_2C* p = &dword_80095FB0[idx];
    p->field_4 = c;
    p->field_5 = c;
    p->field_6 = c;
}
// Matched
void sub_8003F9A8(int idx, unsigned char* rgb)
{
    struct_2C* p = &dword_80095FB0[idx];
    p->field_4 = rgb[0];
    p->field_5 = rgb[1];
    p->field_6 = rgb[2];
}
// Matched
void sub_8003F9E8(int idx, int v)
{
    struct_2C* p = &dword_80095FB0[idx];
    sub_80033048(p->field_14, v);
}
// Matched
void sub_8003FA2C(int idx, int abe)
{
    struct_2C* p = &dword_80095FB0[idx];
    SetSemiTrans(p->field_14, abe);
}
// Matched
int sub_8003FA70(int idx, unsigned char* s)
{
    struct_2C* p = &dword_80095FB0[idx];
    int w = 0;
    int i = 0;
    int c;
    while ((c = s[i]) != 0)
    {
        c = c - 0x20 + p->field_1E;
        if (p->field_24)
        {
            w += p->field_24[c];
        }
        else
        {
            w += p->field_10;
        }
        i++;
    }
    return w;
}
// Matched
int sub_8003FAF0(unsigned char* s)
{
    int n = 0;
    while (s[n])
    {
        n++;
    }
    return n;
}
// Matched
int sub_8003FB24(unsigned char* s)
{
    int n = 0;
    while (s[n])
    {
        n += 2;
    }
    return n / 2;
}
// Matched
int sub_8003FB60(unsigned short* s)
{
    int n = 0;
    while (*s)
    {
        s++;
        n++;
    }
    return n;
}
// Matched
void sub_8003FB8C(unsigned char* dst, unsigned char* src)
{
    int i = 0;
    while (src[i])
    {
        dst[i] = src[i];
        i++;
    }
    dst[i] = src[i];
}
// Matched
void sub_8003FBD4(int idx)
{
    int n;
    int i;
    sub_8003F748(idx, playerName_8008BD48);
    n = sub_80010548(3);
    for (i = 0; i < n; i++)
    {
        sub_8003F748(idx, (unsigned char*)sub_800106F8(3, i));
    }
}
// Matched
void* malloc3_8003FC4C(unsigned int s)
{
    return malloc3(s);
}
// Matched
void free3_8003FC6C(void* block)
{
    free3(block);
}
// Matched
int sub_8003FC8C(int size, Heap* h)
{
    switch ((int)h)
    {
    case 0:
        return (int)sub_8003FDC0((List*)dword_80096090, size);
    case 1:
        return (int)malloc3_8003FC4C(size);
    default:
        if (h->magic == (int)0x8FFFFFFF)
        {
            if (h->inited != 0)
            {
                return (int)sub_8003FFD0(h, size);
            }
            return (int)malloc3_8003FC4C(size);
        }
        break;
    }
    return (int)sub_8003FDC0((List*)h, size);
}
// Matched
void sub_8003FD18(int ptr, Heap* h)
{
    switch ((int)h)
    {
    case 0:
        sub_8003FE38(dword_80096090, ptr);
        break;
    case 1:
        free3_8003FC6C((void*)ptr);
        break;
    default:
        if (h->magic == (int)0x8FFFFFFF)
        {
            if (sub_80040274((int)h, (int*)ptr))
            {
                sub_800400B4(h, (void*)ptr);
            }
            else
            {
                free3_8003FC6C((void*)ptr);
            }
        }
        else
        {
            sub_8003FE38(h, ptr);
        }
        break;
    }
}
// Matched
void sub_8003FDB0(int* p)
{
    p[0] = 0;
    p[1] = 0;
    p[2] = 0;
}
// Matched
void* sub_8003FDC0(List* l, int size)
{
    ListNode* n = (ListNode*)malloc3_8003FC4C(size + 8);
    n->prev = 0;
    n->next = 0;
    if (l->count == 0)
    {
        l->head = n;
    }
    else
    {
        n->prev = l->tail;
        l->tail->next = n;
    }
    l->tail = n;
    l->count++;
    return n + 1;
}
#if 0
// Not matched: arg1 register reused for prev (3 words)
void sub_8003FE38(void* arg0, int arg1)
{
    List* l = (List*)arg0;
    ListNode* n = (ListNode*)((char*)arg1 - 8);
    if (l->count)
    {
        if (n->prev == 0)
        {
            l->head = n->next;
        }
        else
        {
            n->prev->next = n->next;
        }
        if (n->next == 0)
        {
            l->tail = n->prev;
        }
        else
        {
            n->next->prev = n->prev;
        }
        l->count--;
        free3_8003FC6C(n);
    }
}
#endif
INCLUDE_ASM(sub_8003FE38);
// Matched
void sub_8003FEC8(void* arg0)
{
    List* l = (List*)arg0;
    ListNode* n = l->tail;
    while (n)
    {
        ListNode* cur = n;
        n = n->prev;
        free3_8003FC6C(cur);
    }
    sub_8003FDB0((int*)l);
}
// Matched
void sub_8003FF1C(Heap* h, unsigned int size)
{
    void* buf = malloc3_8003FC4C(size);
    h->magic = 0x8FFFFFFF;
    h->inited = 1;
    h->buffer = buf;
    h->size = size;
    h->used = 0;
    h->count = 0;
    h->head = 0;
    h->tail = 0;
}
// Matched
void sub_8003FF7C(Heap* h)
{
    free3_8003FC6C(h->buffer);
    h->magic = 0x8FFFFFFF;
    h->inited = 0;
    h->buffer = 0;
    h->size = 0;
    h->count = 0;
    h->used = 0;
    h->head = 0;
    h->tail = 0;
}
#if 0
// Not matched: align expr (size+4)-rem folded differently
void* sub_8003FFD0(Heap* h, unsigned int size)
{
    HeapBlock* b = 0;
    int rem = size & 3;
    unsigned int aligned;
    if (rem)
    {
        aligned = 4 + size;
        aligned -= rem;
    }
    else
    {
        aligned = size;
    }
    size = aligned;
    if (h->size - h->used >= size)
    {
        b = sub_80040150(h, size + 16);
    }
    b->magic = 0x8FFFFFFF;
    b->size = size + 16;
    b->next = 0;
    b->prev = 0;
    if (h->count == 0)
    {
        h->head = b;
    }
    else
    {
        b->prev = h->tail;
        h->tail->next = b;
    }
    h->tail = b;
    h->used += b->size;
    h->count++;
    return b + 1;
}
#endif
INCLUDE_ASM(sub_8003FFD0);
// Matched
void sub_800400B4(Heap* h, void* p)
{
    HeapBlock* b;
    if (h->count)
    {
        b = (HeapBlock*)p - 1;
        if (b->prev == 0)
        {
            h->head = b->next;
        }
        else
        {
            b->prev->next = b->next;
        }
        if (b->next == 0)
        {
            h->tail = b->prev;
        }
        else
        {
            b->next->prev = b->prev;
        }
        b->magic = 0x08070F01;
        h->used -= b->size;
        h->count--;
    }
}
// Matched
void sub_80040148(int* p, int v)
{
    p[1] = v;
}
// Matched
HeapBlock* sub_80040150(Heap* h, unsigned int size)
{
    char* best = 0;
    char* pos = (char*)h->buffer;
    unsigned int bestsz;
    unsigned int total = h->size;
    HeapBlock* blk = h->head;
    char* end;
    HeapBlock* b;
    unsigned int i;
    int j;
    unsigned int gap;
    end = pos + total;
    bestsz = total;
    if (h->count == 0)
    {
        if (end >= pos + size)
        {
            best = pos;
        }
    }
    else
    {
        for (i = 0; i <= h->count; i++)
        {
            if (end >= pos + size)
            {
                j = 0;
                for (b = h->head; b; b = b->next, j++)
                {
                    if (pos < (char*)b + b->size && (char*)b < pos + size)
                    {
                        break;
                    }
                }
                if (j == h->count)
                {
                    gap = h->size;
                    for (b = h->head; b; b = b->next)
                    {
                        if (pos < (char*)b && (unsigned int)((char*)b - pos) < gap)
                        {
                            gap = (char*)b - pos;
                        }
                    }
                    if (best == 0 || gap < bestsz)
                    {
                        best = pos;
                        bestsz = gap;
                    }
                }
            }
            pos += blk->size;
            if (blk->next)
            {
                blk = blk->next;
            }
        }
    }
    return (HeapBlock*)best;
}
// Matched
int sub_80040274(int a0, int* a1)
{
    return a1[-4] == 0x8FFFFFFF;
}
// Matched
void sub_8004028C(void)
{
    dword_80098688 = 0;
}
#if 0
void sub_80040298(void* arg0, void* arg1, int arg2)
{
}
#endif
INCLUDE_ASM(sub_80040298);
// Matched
void sub_80040360(int *pOut, int *pDataToWrite, int fileSize)
{
  int result; // $v0
  int v4; // $v1

  do
  {
    result = *pDataToWrite;
    v4 = pDataToWrite[1];
    pDataToWrite += 2;
    --fileSize;
    *pOut = result;
    pOut[1] = v4;
    pOut += 2;
  }
  while ( fileSize );
}
// Matched
void ReadBytesInto_80040388(int* pOut, int* pSource, int count)
{
    int dataToCopy;

    do
    {
        dataToCopy = *pSource++;
        *pOut++ = dataToCopy;
        --count;
    } while (count);
}
// Matched
void sub_800403A8(unsigned short* pOut, unsigned short* pSource, int count)
{
    do
    {
        *pOut++ = *pSource++;
        --count;
    } while (count);
}
// Matched
void sub_800403C8(char *a1, unsigned char *fileBuffer, int fileSize)
{
  do
  {
    *a1++ = *fileBuffer++;
    --fileSize;
  }
  while ( fileSize );
}
// Matched
void sub_800403E8(unsigned int *overlayAddr, unsigned int *fileBuffer, unsigned int fileSize)
{
  unsigned int *overlayAddr_copy; // $s2
  unsigned char *pFileBuffer; // $s3
  unsigned int fileSize_copy; // $s1
  unsigned int alignedFileSize; // $s0

  overlayAddr_copy = overlayAddr;
  pFileBuffer = (unsigned char *)fileBuffer;
  fileSize_copy = fileSize;
  if ( fileSize )
  {
    if ( ((unsigned char)overlayAddr & 3) == 0 )
    {
      alignedFileSize = fileSize >> 3;
      if ( ((unsigned char)fileBuffer & 3) == 0 )
      {
        fileSize_copy = fileSize & 7;
        if ( alignedFileSize )
        {
          sub_80040360(overlayAddr, (int *)fileBuffer, alignedFileSize);
          overlayAddr_copy += 2 * alignedFileSize;
          pFileBuffer += 8 * alignedFileSize;
        }
      }
    }
    if ( fileSize_copy )
      sub_800403C8(overlayAddr_copy, pFileBuffer, fileSize_copy);
  }
}
// Matched
void SetGameBootState_80040470(void)
{
    currentGameState_8008D4B4 = eGameBoot_0;
}
// Matched
void GameLoop_8004047C(void)
{
    do
    {
        switch (currentGameState_8008D4B4)
        {
            case eGameBoot_0:
                sub_80040718();
                LoadPublicTiyAndFtg_800407D0();
                currentGameState_8008D4B4 = eIntroCopyright_1;
                break;
            case eIntroCopyright_1:
                sub_80040658(3);
                ShowCopyright_80040A84();
                currentGameState_8008D4B4 = eCraveEntertainmentMovie_3;
                break;
            case eGenkiMovie_2:
                sub_80040658(1);
                PlayGenkiMovie_80040AEC();
                currentGameState_8008D4B4 = eIntroAnime_5;
                break;
            case eCraveEntertainmentMovie_3:
                sub_80040658(1);
                PlayCraveEntertainmentMovie_80040B54();
                currentGameState_8008D4B4 = eGenkiMovie_2;
                break;
            case eUnknown_4:
                sub_80040658(1);
                ShowDemoDisclaimer_80040C8C();
                currentGameState_8008D4B4 = eIntroAnime_5;
                break;
            case eIntroAnime_5:
                sub_80040658(1);
                PlayAnimeMovie_80040CCC();
                word_8008B558[1] = 1;
                word_8008B558[0] = 0;
                currentGameState_8008D4B4 = eMainMenu_6;
            case eMainMenu_6:
                sub_80040658(1);
                currentGameState_8008D4B4 = ExecOverlay_80040DDC(eTitle);
                break;
            case eUnknown_7:
                sub_80040658(2);
                currentGameState_8008D4B4 = sub_80040D5C();
                break;
            case eBattleArenaMenu_8:
                sub_80040658(2);
                currentGameState_8008D4B4 = ExecOverlay_80040DDC(eCombat);
                break;
            case eSoundTst_9:
                sub_80040658(2);
                currentGameState_8008D4B4 = ExecOverlay_80040DDC(eSoundTst);
                break;
            case eTstModel_10:
                sub_80040658(2);
                currentGameState_8008D4B4 = ExecOverlay_80040DDC(eTstModel);
                break;
            case eTstCompo_11:
                sub_80040658(2);
                currentGameState_8008D4B4 = ExecOverlay_80040DDC(eTstCompo);
                break;
            case eIngame_12:
                sub_80040658(2);
                LoadOverlay_80020BF8(2, eEventFnc_29);
                currentGameState_8008D4B4 = ExecOverlay_80040DDC(eGame);
                break;
            case eQuitToIntroAnime_13:
                currentGameState_8008D4B4 = eIntroAnime_5;
                break;
            case eToMainMenu_14:
                currentGameState_8008D4B4 = eMainMenu_6;
                break;

            case eUnknown_15:
            default:
                break;
        }
    } while ((unknownFlags_8008D678 & 4) == 0);
}
