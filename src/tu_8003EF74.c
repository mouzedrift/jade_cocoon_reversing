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

extern void IntToText_8003F610(unsigned short* buf, int val);
extern void DrawText_8003E91C(int mode, int* buf, int a, int b);

typedef struct CharTable
{
    unsigned short* tbl;
    int field_4;
    int count;
} CharTable;
extern CharTable charTables_8008685C[];
extern unsigned short* DecodeText_8003F748(int mode, unsigned short* s);
extern void IntToSjisReversed_8003F58C(unsigned char* buf, int val);
extern int WStrLen_8003FB60(unsigned short* s);

typedef struct ListNode { struct ListNode* prev; struct ListNode* next; } ListNode;
typedef struct List { int count; ListNode* head; ListNode* tail; } List;

struct Pool;
typedef struct PoolBlock
{
    int magic;
    unsigned int size;
    struct PoolBlock* prev;
    struct PoolBlock* next;
} PoolBlock;

typedef struct Pool
{
    int magic;
    int inited;
    unsigned int size;
    int count;
    int field_10;
    unsigned int used;
    void* buffer;
    PoolBlock* head;
    PoolBlock* tail;
} Pool;

extern PoolBlock* PoolFindFreeSpace_80040150(Pool* h, unsigned int size);
extern void* PoolAlloc_8003FFD0(Pool* h, unsigned int size);
extern void PoolFree_800400B4(Pool* h, void* p);
extern void* ListAlloc_8003FDC0(List* l, int size);
extern void ListFree_8003FE38(void* arg0, void* arg1);

INCLUDE_DATA(dword_80098198);
INCLUDE_DATA(dword_80098688);

// Matched
void DrawNumber_8003EF74(int a0, int a1, int a2)
{
    unsigned short buf[12];
    IntToText_8003F610(buf, a1);
    DrawText_8003E91C(2, (int*)buf, a0, a2);
}
// Matched
void sub_8003EFBC(short* pos, int val, int ot)
{
    unsigned short buf[12];
    Font* p;
    short x = pos[0];
    short y = pos[1];
    unsigned short* s;
    int c;
    unsigned short u;
    int v;
    int col;

    IntToSjisReversed_8003F58C((unsigned char*)buf, val);
    s = EncodeText_8003F684(2, buf);
    p = &fonts_80095FB0[2];
    c = *s;
    while (c != 0)
    {
        s++;
        x -= p->w_10;
        if (c <= charTables_8008685C[2].field_4)
        {
            u = c - 1;
            v = (short)(u % (unsigned short)p->field_28);
            u = u / (unsigned short)p->field_28;
            col = v % (unsigned short)p->field_1C;
            v = v / (unsigned short)p->field_1C;
            p->x0_8 = x;
            p->y0_A = y;
            p->clut_E = getClut(p->clutX_20, p->field_2A + (p->clutY_22 + u));
            p->u_C = p->field_18 + p->w_10 * col;
            p->v_D = p->field_1A + p->h_12 * v;
            ((u_long*)primAllocPtr_800960A8[bDoubleBuffer_8008D428])[0] = ((u_long*)p)[0];
            ((u_long*)primAllocPtr_800960A8[bDoubleBuffer_8008D428])[1] = ((u_long*)p)[1];
            ((u_long*)primAllocPtr_800960A8[bDoubleBuffer_8008D428])[2] = ((u_long*)p)[2];
            ((u_long*)primAllocPtr_800960A8[bDoubleBuffer_8008D428])[3] = ((u_long*)p)[3];
            ((u_long*)primAllocPtr_800960A8[bDoubleBuffer_8008D428])[4] = ((u_long*)p)[4];
            addPrim(&pOT_8008D454[ot], primAllocPtr_800960A8[bDoubleBuffer_8008D428]);
            primAllocPtr_800960A8[bDoubleBuffer_8008D428] += 0x14;
        }
        c = *s;
    }
    ((u_long*)primAllocPtr_800960A8[bDoubleBuffer_8008D428])[0] = ((u_long*)p->tpage_14)[0];
    ((u_long*)primAllocPtr_800960A8[bDoubleBuffer_8008D428])[1] = ((u_long*)p->tpage_14)[1];
    addPrim(&pOT_8008D454[ot], primAllocPtr_800960A8[bDoubleBuffer_8008D428]);
    primAllocPtr_800960A8[bDoubleBuffer_8008D428] += 8;
}
extern int dword_80086898[][12];
// Matched
void sub_8003F264(short* pos, int val, int ot)
{
    unsigned short buf[12];
    Font* p;
    short x = pos[0];
    short y = pos[1];
    unsigned short* s;
    unsigned short c;
    short k;
    int v;
    int col;

    IntToSjisReversed_8003F58C((unsigned char*)buf, val);
    s = EncodeText_8003F684(1, buf);
    p = &fonts_80095FB0[1];
    while (*s != 0)
    {
        c = *s++;
        x -= p->w_10;
        for (k = 12; k != 0; k--)
        {
            if (c - 1 < dword_80086898[0][k - 1])
            {
                x += k;
                break;
            }
        }
        if (c <= charTables_8008685C[1].field_4)
        {
            c = c - 1;
            v = (short)(c % (unsigned short)p->field_28);
            c = c / (unsigned short)p->field_28;
            col = v % (unsigned short)p->field_1C;
            v = v / (unsigned short)p->field_1C;
            p->x0_8 = x;
            p->y0_A = y;
            p->clut_E = getClut(p->clutX_20, p->field_2A + (p->clutY_22 + c));
            p->u_C = p->field_18 + p->w_10 * col;
            p->v_D = p->field_1A + p->h_12 * v;
            ((u_long*)primAllocPtr_800960A8[bDoubleBuffer_8008D428])[0] = ((u_long*)p)[0];
            ((u_long*)primAllocPtr_800960A8[bDoubleBuffer_8008D428])[1] = ((u_long*)p)[1];
            ((u_long*)primAllocPtr_800960A8[bDoubleBuffer_8008D428])[2] = ((u_long*)p)[2];
            ((u_long*)primAllocPtr_800960A8[bDoubleBuffer_8008D428])[3] = ((u_long*)p)[3];
            ((u_long*)primAllocPtr_800960A8[bDoubleBuffer_8008D428])[4] = ((u_long*)p)[4];
            addPrim(&pOT_8008D454[ot], primAllocPtr_800960A8[bDoubleBuffer_8008D428]);
            primAllocPtr_800960A8[bDoubleBuffer_8008D428] += 0x14;
        }
    }
    ((u_long*)primAllocPtr_800960A8[bDoubleBuffer_8008D428])[0] = ((u_long*)p->tpage_14)[0];
    ((u_long*)primAllocPtr_800960A8[bDoubleBuffer_8008D428])[1] = ((u_long*)p->tpage_14)[1];
    addPrim(&pOT_8008D454[ot], primAllocPtr_800960A8[bDoubleBuffer_8008D428]);
    primAllocPtr_800960A8[bDoubleBuffer_8008D428] += 8;
}
// Matched
void DrawNumber_8003F544(int a0, int a1, int a2)
{
    unsigned short buf[12];
    IntToText_8003F610(buf, a1);
    DrawText_8003E91C(1, (int*)buf, a0, a2);
}
// Matched
void IntToSjisReversed_8003F58C(unsigned char* buf, int val)
{
    int neg = 1;
    if (val >= 0)
    {
        val = -val;
        neg = 0;
    }
    do
    {
        int q;
        *buf++ = 0x82;
        q = val / 10;
        *buf++ = 0x4F + (q * 10 - val);
        val = q;
    } while (val);
    if (neg)
    {
        *buf++ = 0x81;
        *buf++ = 0x7C;
    }
    buf[0] = 0;
    buf[1] = 0;
}
// Matched
void IntToText_8003F610(unsigned short* out, int val)
{
    unsigned short tmp[12];
    unsigned short* start = out;
    int n;
    IntToSjisReversed_8003F58C((unsigned char*)tmp, val);
    n = WStrLen_8003FB60(tmp);
    do
    {
        n--;
        *out++ = tmp[n];
    } while (n);
    *out = 0;
    EncodeText_8003F684(2, start);
}
// Matched
unsigned short* EncodeText_8003F684(int mode, unsigned short* s)
{
    unsigned short* p = s;
    unsigned short j;
    if (s && *s > 0x2080 && *(unsigned char*)s)
    {
        while (*(unsigned char*)p)
        {
            unsigned short* tbl = charTables_8008685C[mode].tbl;
            unsigned short c = *p;
            for (j = 0; j < charTables_8008685C[mode].count; j++, tbl++)
            {
                if (c == *tbl)
                {
                    *p = j + 1;
                    break;
                }
            }
            p++;
        }
    }
    return s;
}
// Matched
unsigned short* DecodeText_8003F748(int mode, unsigned short* s)
{
    unsigned short* tbl = charTables_8008685C[mode].tbl;
    unsigned short* p = s;
    if (s && *(unsigned char*)s)
    {
        while (*(unsigned char*)p)
        {
            if (*p <= 0x2080)
            {
                *p = tbl[*p - 1];
            }
            p++;
        }
    }
    return s;
}
// Matched
void EncodeName_8003F7C8(void* a0, unsigned char* a1)
{
    unsigned short tmp[11];
    unsigned short* p;
    int flag = 0;
    int i;
    MemCopy_800403E8(tmp, a0, 0x16);
    p = EncodeText_8003F684(1, DecodeText_8003F748(2, tmp));
    for (i = 0; i < 10; i++)
    {
        int c = 0;
        if (!flag)
        {
            c = *(unsigned char*)&p[i];
            if (!c)
            {
                flag = 1;
            }
        }
        a1[i] = c;
    }
    a1[10] = 0;
}
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
void sub_8003F89C(unsigned short* p)
{
    int i;
    for (i = 0; i < 10; i++)
    {
        unsigned short v = p[i];
        unsigned short t = (v >> 8) + ((v & 0xFF) << 8);
        if ((unsigned short)(t + 0x7D7F) < 0x1A)
        {
            t = t + 0xFFDF;
            p[i] = (t >> 8) + ((t & 0xFF) << 8);
        }
    }
}
#endif
INCLUDE_ASM(sub_8003F89C);

// Matched
void sub_8003F900(int idx, int val)
{
    Font* p = &fonts_80095FB0[idx];
    p->field_2A = val;
}
// Matched
void SetFontClutRow_8003F928(int idx, int dy)
{
    Font* p = &fonts_80095FB0[idx];
    p->clut_E = GetClut(p->clutX_20, p->clutY_22 + dy);
}
// Matched
void SetFontGrey_8003F978(int idx, int val)
{
    Font* p = &fonts_80095FB0[idx];
    p->r_4 = val;
    p->g_5 = val;
    p->b_6 = val;
}
// Matched
void SetFontColor_8003F9A8(int idx, unsigned char* rgb)
{
    Font* p = &fonts_80095FB0[idx];
    p->r_4 = rgb[0];
    p->g_5 = rgb[1];
    p->b_6 = rgb[2];
}
// Matched
void sub_8003F9E8(int idx, int v)
{
    Font* p = &fonts_80095FB0[idx];
    sub_80033048(p->tpage_14, v);
}
// Matched
void SetFontSemiTrans_8003FA2C(int idx, int abe)
{
    Font* p = &fonts_80095FB0[idx];
    SetSemiTrans(p->tpage_14, abe);
}
// Matched
int MeasureText_8003FA70(int idx, unsigned char* str)
{
    int sum = 0;
    int i = 0;
    int c = str[0];
    Font* p = &fonts_80095FB0[idx];
    if (c)
    {
        int base = p->firstChar_1E - 0x20;
        unsigned char* tbl = p->widths_24;
        do
        {
            c += base;
            if (tbl)
            {
                sum += tbl[c];
            }
            else
            {
                sum += p->w_10;
            }
            i++;
            c = str[i];
        } while (c);
    }
    return sum;
}
// Matched
int StrLen_8003FAF0(unsigned char* s)
{
    int n = 0;
    while (s[n])
    {
        n++;
    }
    return n;
}
// Matched
int SjisStrLen_8003FB24(unsigned char* s)
{
    int n = 0;
    while (s[n])
    {
        n += 2;
    }
    return n / 2;
}
// Matched
int WStrLen_8003FB60(unsigned short* s)
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
void StrCopy_8003FB8C(char* d, char* s)
{
    int i = 0;
    while (s[i])
    {
        d[i] = s[i];
        i++;
    }
    d[i] = s[i];
}
// Matched
void DecodeNames_8003FBD4(int a0)
{
    int n;
    int i;
    DecodeText_8003F748(a0, playerName_8008BD48);
    n = CountMinions_80010548(3);
    for (i = 0; i < n; i++)
    {
        DecodeText_8003F748(a0, GetMinionName_800106F8(3, i));
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
int HeapAlloc_8003FC8C(int size, Pool* h)
{
    switch ((int)h)
    {
    case 0:
        return (int)ListAlloc_8003FDC0((List*)defaultAllocList_80096090, size);
    case 1:
        return (int)malloc3_8003FC4C(size);
    default:
        if (h->magic == (int)0x8FFFFFFF)
        {
            if (h->inited != 0)
            {
                return (int)PoolAlloc_8003FFD0(h, size);
            }
            return (int)malloc3_8003FC4C(size);
        }
        break;
    }
    return (int)ListAlloc_8003FDC0((List*)h, size);
}
// Matched
void HeapFree_8003FD18(int ptr, Pool* h)
{
    switch ((int)h)
    {
    case 0:
        ListFree_8003FE38(defaultAllocList_80096090, (void*)ptr);
        break;
    case 1:
        free3_8003FC6C((void*)ptr);
        break;
    default:
        if (h->magic == (int)0x8FFFFFFF)
        {
            if (IsPoolBlock_80040274((int)h, (int*)ptr))
            {
                PoolFree_800400B4(h, (void*)ptr);
            }
            else
            {
                free3_8003FC6C((void*)ptr);
            }
        }
        else
        {
            ListFree_8003FE38(h, (void*)ptr);
        }
        break;
    }
}
// Matched
void ListInit_8003FDB0(int* p)
{
    p[0] = 0;
    p[1] = 0;
    p[2] = 0;
}
// Matched
void* ListAlloc_8003FDC0(List* l, int size)
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
void ListFree_8003FE38(void* a0, void* a1)
{
    List* arg0 = (List*)a0;
    ListNode* n = (ListNode*)((char*)a1 - 8);
    if (arg0->count)
    {
        if (n->prev == 0)
        {
            arg0->head = n->next;
        }
        else
        {
            n->prev->next = n->next;
        }
        if (n->next == 0)
        {
            arg0->tail = n->prev;
        }
        else
        {
            n->next->prev = n->prev;
        }
        arg0->count = arg0->count - 1;
        free3_8003FC6C(n);
    }
}
#endif
INCLUDE_ASM(ListFree_8003FE38);
// Matched
void ListFreeAll_8003FEC8(void* arg0)
{
    List* l = (List*)arg0;
    ListNode* n = l->tail;
    while (n)
    {
        ListNode* cur = n;
        n = n->prev;
        free3_8003FC6C(cur);
    }
    ListInit_8003FDB0((int*)l);
}
// Matched
void PoolInit_8003FF1C(Pool* h, unsigned int size)
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
void PoolDestroy_8003FF7C(Pool* h)
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
void* PoolAlloc_8003FFD0(Pool* h, unsigned int size)
{
    PoolBlock* b = 0;
    unsigned int s;
    if (size & 3) s = size + 4 - (size & 3); else s = size;
    if (!(h->size - h->used < s))
    {
        b = PoolFindFreeSpace_80040150(h, s + 0x10);
    }
    b->magic = 0x8FFFFFFF;
    b->size = s + 0x10;
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
INCLUDE_ASM(PoolAlloc_8003FFD0);
// Matched
void PoolFree_800400B4(Pool* h, void* p)
{
    PoolBlock* b;
    if (h->count)
    {
        b = (PoolBlock*)p - 1;
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
PoolBlock* PoolFindFreeSpace_80040150(Pool* h, unsigned int size)
{
    char* best = 0;
    char* pos = (char*)h->buffer;
    unsigned int bestsz;
    unsigned int total = h->size;
    PoolBlock* blk = h->head;
    char* end;
    PoolBlock* b;
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
    return (PoolBlock*)best;
}
// Matched
int IsPoolBlock_80040274(int a0, int* a1)
{
    return a1[-4] == 0x8FFFFFFF;
}
// Matched
void sub_8004028C(void)
{
    dword_80098688 = 0;
}
extern unsigned long* primAllocPtrs_800960A8[];
#if 0
short* AddPrimCopy_80040298(void* arg0, void* arg1, int arg2)
{
    unsigned long* ot = (unsigned long*)arg0;
    unsigned long* cur = primAllocPtrs_800960A8[bDoubleBuffer_8008D428];
    unsigned long** p;
    ReadBytesInto_80040388((int*)cur, (int*)arg1, arg2);
    p = &primAllocPtrs_800960A8[bDoubleBuffer_8008D428];
    **p = (**p & 0xFF000000) | (*ot & 0xFFFFFF);
    *ot = (*ot & 0xFF000000) | ((unsigned long)*p & 0xFFFFFF);
    *p += arg2;
    return (short*)cur;
}
#endif
INCLUDE_ASM(AddPrimCopy_80040298);
// Matched
void CopyDoubleWords_80040360(int *pOut, int *pDataToWrite, int fileSize)
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
void CopyHalfwords_800403A8(unsigned short* pOut, unsigned short* pSource, int count)
{
    do
    {
        *pOut++ = *pSource++;
        --count;
    } while (count);
}
// Matched
void CopyBytes_800403C8(char *a1, unsigned char *fileBuffer, int fileSize)
{
  do
  {
    *a1++ = *fileBuffer++;
    --fileSize;
  }
  while ( fileSize );
}
// Matched
void MemCopy_800403E8(unsigned int *overlayAddr, unsigned int *fileBuffer, unsigned int fileSize)
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
          CopyDoubleWords_80040360(overlayAddr, (int *)fileBuffer, alignedFileSize);
          overlayAddr_copy += 2 * alignedFileSize;
          pFileBuffer += 8 * alignedFileSize;
        }
      }
    }
    if ( fileSize_copy )
      CopyBytes_800403C8(overlayAddr_copy, pFileBuffer, fileSize_copy);
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
                InitGameDefaults_80040718();
                LoadPublicTiyAndFtg_800407D0();
                currentGameState_8008D4B4 = eIntroCopyright_1;
                break;
            case eIntroCopyright_1:
                SetDisplayMode_80040658(3);
                ShowCopyright_80040A84();
                currentGameState_8008D4B4 = eCraveEntertainmentMovie_3;
                break;
            case eGenkiMovie_2:
                SetDisplayMode_80040658(1);
                PlayGenkiMovie_80040AEC();
                currentGameState_8008D4B4 = eIntroAnime_5;
                break;
            case eCraveEntertainmentMovie_3:
                SetDisplayMode_80040658(1);
                PlayCraveEntertainmentMovie_80040B54();
                currentGameState_8008D4B4 = eGenkiMovie_2;
                break;
            case eUnknown_4:
                SetDisplayMode_80040658(1);
                ShowDemoDisclaimer_80040C8C();
                currentGameState_8008D4B4 = eIntroAnime_5;
                break;
            case eIntroAnime_5:
                SetDisplayMode_80040658(1);
                PlayAnimeMovie_80040CCC();
                word_8008B558[1] = 1;
                word_8008B558[0] = 0;
                currentGameState_8008D4B4 = eMainMenu_6;
            case eMainMenu_6:
                SetDisplayMode_80040658(1);
                currentGameState_8008D4B4 = ExecOverlay_80040DDC(eTitle);
                break;
            case eUnknown_7:
                SetDisplayMode_80040658(2);
                currentGameState_8008D4B4 = sub_80040D5C();
                break;
            case eBattleArenaMenu_8:
                SetDisplayMode_80040658(2);
                currentGameState_8008D4B4 = ExecOverlay_80040DDC(eCombat);
                break;
            case eSoundTst_9:
                SetDisplayMode_80040658(2);
                currentGameState_8008D4B4 = ExecOverlay_80040DDC(eSoundTst);
                break;
            case eTstModel_10:
                SetDisplayMode_80040658(2);
                currentGameState_8008D4B4 = ExecOverlay_80040DDC(eTstModel);
                break;
            case eTstCompo_11:
                SetDisplayMode_80040658(2);
                currentGameState_8008D4B4 = ExecOverlay_80040DDC(eTstCompo);
                break;
            case eIngame_12:
                SetDisplayMode_80040658(2);
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
