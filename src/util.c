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
#include "util.h"
#include "main.h"
#include "font.h"






// Matched
void DrawNumber_8003EF74(short* pos, int val, int ot)
{
    unsigned short buf[12];
    IntToText_8003F610(buf, val);
    DrawText_8003E91C(2, (int*)buf, pos, ot);
}
// Matched
void DrawNumberRightAligned_8003EFBC(short* pos, int val, int ot)
{
    unsigned short buf[12];
    Font* font;
    short x = pos[0];
    short y = pos[1];
    unsigned short* text;
    int ch;
    unsigned short page;
    int cell;
    int col;

    IntToSjisReversed_8003F58C((unsigned char*)buf, val);
    text = EncodeText_8003F684(2, buf);
    font = &fonts_80095FB0[2];
    ch = *text;
    while (ch != 0)
    {
        text++;
        x -= font->w_10;
        if (ch <= charTables_8008685C[2].lastChar_4)
        {
            page = ch - 1;
            cell = (short)(page % (unsigned short)font->charsPerClut_28);
            page = page / (unsigned short)font->charsPerClut_28;
            col = cell % (unsigned short)font->columns_1C;
            cell = cell / (unsigned short)font->columns_1C;
            font->x0_8 = x;
            font->y0_A = y;
            font->clut_E = getClut(font->clutX_20, font->clutOffset_2A + (font->clutY_22 + page));
            font->u_C = font->u0_18 + font->w_10 * col;
            font->v_D = font->v0_1A + font->h_12 * cell;
            ((u_long*)primAllocPtr_800960A8[bDoubleBuffer_8008D428])[0] = ((u_long*)font)[0];
            ((u_long*)primAllocPtr_800960A8[bDoubleBuffer_8008D428])[1] = ((u_long*)font)[1];
            ((u_long*)primAllocPtr_800960A8[bDoubleBuffer_8008D428])[2] = ((u_long*)font)[2];
            ((u_long*)primAllocPtr_800960A8[bDoubleBuffer_8008D428])[3] = ((u_long*)font)[3];
            ((u_long*)primAllocPtr_800960A8[bDoubleBuffer_8008D428])[4] = ((u_long*)font)[4];
            addPrim(&pOT_8008D454[ot], primAllocPtr_800960A8[bDoubleBuffer_8008D428]);
            primAllocPtr_800960A8[bDoubleBuffer_8008D428] += 0x14;
        }
        ch = *text;
    }
    ((u_long*)primAllocPtr_800960A8[bDoubleBuffer_8008D428])[0] = ((u_long*)font->tpage_14)[0];
    ((u_long*)primAllocPtr_800960A8[bDoubleBuffer_8008D428])[1] = ((u_long*)font->tpage_14)[1];
    addPrim(&pOT_8008D454[ot], primAllocPtr_800960A8[bDoubleBuffer_8008D428]);
    primAllocPtr_800960A8[bDoubleBuffer_8008D428] += 8;
}
extern int charWidthThresholds_80086898[][12];
// Matched
void DrawNumberRightAlignedFont1_8003F264(short* pos, int val, int ot)
{
    unsigned short buf[12];
    Font* font;
    short x = pos[0];
    short y = pos[1];
    unsigned short* text;
    unsigned short ch;
    short k;
    int cell;
    int col;

    IntToSjisReversed_8003F58C((unsigned char*)buf, val);
    text = EncodeText_8003F684(1, buf);
    font = &fonts_80095FB0[1];
    while (*text != 0)
    {
        ch = *text++;
        x -= font->w_10;
        for (k = 12; k != 0; k--)
        {
            if (ch - 1 < charWidthThresholds_80086898[0][k - 1])
            {
                x += k;
                break;
            }
        }
        if (ch <= charTables_8008685C[1].lastChar_4)
        {
            ch = ch - 1;
            cell = (short)(ch % (unsigned short)font->charsPerClut_28);
            ch = ch / (unsigned short)font->charsPerClut_28;
            col = cell % (unsigned short)font->columns_1C;
            cell = cell / (unsigned short)font->columns_1C;
            font->x0_8 = x;
            font->y0_A = y;
            font->clut_E = getClut(font->clutX_20, font->clutOffset_2A + (font->clutY_22 + ch));
            font->u_C = font->u0_18 + font->w_10 * col;
            font->v_D = font->v0_1A + font->h_12 * cell;
            ((u_long*)primAllocPtr_800960A8[bDoubleBuffer_8008D428])[0] = ((u_long*)font)[0];
            ((u_long*)primAllocPtr_800960A8[bDoubleBuffer_8008D428])[1] = ((u_long*)font)[1];
            ((u_long*)primAllocPtr_800960A8[bDoubleBuffer_8008D428])[2] = ((u_long*)font)[2];
            ((u_long*)primAllocPtr_800960A8[bDoubleBuffer_8008D428])[3] = ((u_long*)font)[3];
            ((u_long*)primAllocPtr_800960A8[bDoubleBuffer_8008D428])[4] = ((u_long*)font)[4];
            addPrim(&pOT_8008D454[ot], primAllocPtr_800960A8[bDoubleBuffer_8008D428]);
            primAllocPtr_800960A8[bDoubleBuffer_8008D428] += 0x14;
        }
    }
    ((u_long*)primAllocPtr_800960A8[bDoubleBuffer_8008D428])[0] = ((u_long*)font->tpage_14)[0];
    ((u_long*)primAllocPtr_800960A8[bDoubleBuffer_8008D428])[1] = ((u_long*)font->tpage_14)[1];
    addPrim(&pOT_8008D454[ot], primAllocPtr_800960A8[bDoubleBuffer_8008D428]);
    primAllocPtr_800960A8[bDoubleBuffer_8008D428] += 8;
}
// Matched
void DrawNumber_8003F544(short* pos, int val, int ot)
{
    unsigned short buf[12];
    IntToText_8003F610(buf, val);
    DrawText_8003E91C(1, (int*)buf, pos, ot);
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
        int quot;
        *buf++ = 0x82;
        quot = val / 10;
        *buf++ = 0x4F + (quot * 10 - val);
        val = quot;
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
    unsigned short reversed[12];
    unsigned short* start = out;
    int len;
    IntToSjisReversed_8003F58C((unsigned char*)reversed, val);
    len = WStrLen_8003FB60(reversed);
    do
    {
        len--;
        *out++ = reversed[len];
    } while (len);
    *out = 0;
    EncodeText_8003F684(2, start);
}
// Matched
unsigned short* EncodeText_8003F684(int mode, unsigned short* text)
{
    unsigned short* cur = text;
    unsigned short j;
    if (text && *text > 0x2080 && *(unsigned char*)text)
    {
        while (*(unsigned char*)cur)
        {
            unsigned short* tbl = charTables_8008685C[mode].tbl;
            unsigned short c = *cur;
            for (j = 0; j < charTables_8008685C[mode].count; j++, tbl++)
            {
                if (c == *tbl)
                {
                    *cur = j + 1;
                    break;
                }
            }
            cur++;
        }
    }
    return text;
}
// Matched
unsigned short* DecodeText_8003F748(int mode, unsigned short* text)
{
    unsigned short* tbl = charTables_8008685C[mode].tbl;
    unsigned short* cur = text;
    if (text && *(unsigned char*)text)
    {
        while (*(unsigned char*)cur)
        {
            if (*cur <= 0x2080)
            {
                *cur = tbl[*cur - 1];
            }
            cur++;
        }
    }
    return text;
}
// Matched
void EncodeName_8003F7C8(void* text, unsigned char* out)
{
    unsigned short buf[11];
    unsigned short* encoded;
    int ended = 0;
    int i;
    MemCopy_800403E8(buf, text, 0x16);
    encoded = EncodeText_8003F684(1, DecodeText_8003F748(2, buf));
    for (i = 0; i < 10; i++)
    {
        int c = 0;
        if (!ended)
        {
            c = *(unsigned char*)&encoded[i];
            if (!c)
            {
                ended = 1;
            }
        }
        out[i] = c;
    }
    out[10] = 0;
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
// Matched
void UppercaseSjisName_8003F89C(unsigned short* name)
{
    int i;
    unsigned short ch;
    for (i = 0; i < 10; i++, name++)
    {
        ch = (*name >> 8) + ((*name & 0xFF) << 8);
        if ((unsigned short)(ch + 0x7D7F) < 0x1A)
        {
            ch += 0xFFDF;
            *name = (ch >> 8) + ((ch % 256) << 8);
        }
    }
}

// Matched
void SetFontClutOffset_8003F900(int idx, int val)
{
    Font* font = &fonts_80095FB0[idx];
    font->clutOffset_2A = val;
}
// Matched
void SetFontClutRow_8003F928(int idx, int dy)
{
    Font* font = &fonts_80095FB0[idx];
    font->clut_E = GetClut(font->clutX_20, font->clutY_22 + dy);
}
// Matched
void SetFontGrey_8003F978(int idx, int val)
{
    Font* font = &fonts_80095FB0[idx];
    font->r_4 = val;
    font->g_5 = val;
    font->b_6 = val;
}
// Matched
void SetFontColor_8003F9A8(int idx, unsigned char* rgb)
{
    Font* font = &fonts_80095FB0[idx];
    font->r_4 = rgb[0];
    font->g_5 = rgb[1];
    font->b_6 = rgb[2];
}
// Matched
void SetFontAbr_8003F9E8(int idx, int abr)
{
    Font* font = &fonts_80095FB0[idx];
    SetDrTPageAbr_80033048(font->tpage_14, abr);
}
// Matched
void SetFontSemiTrans_8003FA2C(int idx, int abe)
{
    Font* font = &fonts_80095FB0[idx];
    SetSemiTrans(font->tpage_14, abe);
}
// Matched
int MeasureText_8003FA70(int idx, unsigned char* str)
{
    int sum = 0;
    int i = 0;
    int c = str[0];
    Font* font = &fonts_80095FB0[idx];
    if (c)
    {
        int base = font->firstChar_1E - 0x20;
        unsigned char* tbl = font->widths_24;
        do
        {
            c += base;
            if (tbl)
            {
                sum += tbl[c];
            }
            else
            {
                sum += font->w_10;
            }
            i++;
            c = str[i];
        } while (c);
    }
    return sum;
}
// Matched
int StrLen_8003FAF0(unsigned char* str)
{
    int len = 0;
    while (str[len])
    {
        len++;
    }
    return len;
}
// Matched
int SjisStrLen_8003FB24(unsigned char* str)
{
    int len = 0;
    while (str[len])
    {
        len += 2;
    }
    return len / 2;
}
// Matched
int WStrLen_8003FB60(unsigned short* str)
{
    int len = 0;
    while (*str)
    {
        str++;
        len++;
    }
    return len;
}
// Matched
void StrCopy_8003FB8C(char* dst, char* src)
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
void DecodeNames_8003FBD4(int mode)
{
    int count;
    int i;
    DecodeText_8003F748(mode, playerName_8008BD48);
    count = CountMinions_80010548(3);
    for (i = 0; i < count; i++)
    {
        DecodeText_8003F748(mode, GetMinionName_800106F8(3, i));
    }
}
// Matched
void* malloc3_8003FC4C(unsigned int size)
{
    return malloc3(size);
}
// Matched
void free3_8003FC6C(void* block)
{
    free3(block);
}
// Matched
void* HeapAlloc_8003FC8C(int size, int heap)
{
    Pool* pool = (Pool*)heap;
    switch (heap)
    {
    case 0:
        return ListAlloc_8003FDC0(&defaultAllocList_80096090, size);
    case 1:
        return malloc3_8003FC4C(size);
    default:
        if (pool->magic == (int)0x8FFFFFFF)
        {
            if (pool->inited != 0)
            {
                return PoolAlloc_8003FFD0(pool, size);
            }
            return malloc3_8003FC4C(size);
        }
        break;
    }
    return ListAlloc_8003FDC0((List*)pool, size);
}
// Matched
void HeapFree_8003FD18(void* ptr, int heap)
{
    Pool* pool = (Pool*)heap;
    switch (heap)
    {
    case 0:
        ListFree_8003FE38(&defaultAllocList_80096090, ptr);
        break;
    case 1:
        free3_8003FC6C(ptr);
        break;
    default:
        if (pool->magic == (int)0x8FFFFFFF)
        {
            if (IsPoolBlock_80040274(pool, ptr))
            {
                PoolFree_800400B4(pool, ptr);
            }
            else
            {
                free3_8003FC6C(ptr);
            }
        }
        else
        {
            ListFree_8003FE38((List*)pool, ptr);
        }
        break;
    }
}
// Matched
void ListInit_8003FDB0(List* list)
{
    list->count = 0;
    list->head = 0;
    list->tail = 0;
}
// Matched
void* ListAlloc_8003FDC0(List* list, int size)
{
    ListNode* node = malloc3_8003FC4C(size + 8);
    node->prev = 0;
    node->next = 0;
    if (list->count == 0)
    {
        list->head = node;
    }
    else
    {
        node->prev = list->tail;
        list->tail->next = node;
    }
    list->tail = node;
    list->count++;
    return node + 1;
}
// Matched
void ListFree_8003FE38(List* l, void* ptr)
{
    ListNode* node = ptr;
    node--;
    if (l->count)
    {
        if (node->prev == 0)
        {
            l->head = node->next;
        }
        else
        {
            node->prev->next = node->next;
        }
        if (node->next == 0)
        {
            l->tail = node->prev;
        }
        else
        {
            node->next->prev = node->prev;
        }
        l->count--;
        free3_8003FC6C(node);
    }
}
// Matched
void ListFreeAll_8003FEC8(List* l)
{
    ListNode* node = l->tail;
    while (node)
    {
        ListNode* cur = node;
        node = node->prev;
        free3_8003FC6C(cur);
    }
    ListInit_8003FDB0(l);
}
// Matched
void PoolInit_8003FF1C(Pool* pool, unsigned int size)
{
    void* buf = malloc3_8003FC4C(size);
    pool->magic = 0x8FFFFFFF;
    pool->inited = 1;
    pool->buffer = buf;
    pool->size = size;
    pool->used = 0;
    pool->count = 0;
    pool->head = 0;
    pool->tail = 0;
}
// Matched
void PoolDestroy_8003FF7C(Pool* pool)
{
    free3_8003FC6C(pool->buffer);
    pool->magic = 0x8FFFFFFF;
    pool->inited = 0;
    pool->buffer = 0;
    pool->size = 0;
    pool->count = 0;
    pool->used = 0;
    pool->head = 0;
    pool->tail = 0;
}
// Matched
void* PoolAlloc_8003FFD0(Pool* pool, unsigned int size)
{
    PoolBlock* block = 0;
    unsigned int align = 4;
    size = (size & 3) ? size + align - (size & 3) : size;
    if (!(pool->size - pool->used < size))
    {
        block = PoolFindFreeSpace_80040150(pool, size + 0x10);
    }
    block->magic = 0x8FFFFFFF;
    block->size = size + 0x10;
    block->next = 0;
    block->prev = 0;
    if (pool->count == 0)
    {
        pool->head = block;
    }
    else
    {
        block->prev = pool->tail;
        pool->tail->next = block;
    }
    pool->tail = block;
    pool->used += block->size;
    pool->count++;
    return block + 1;
}
// Matched
void PoolFree_800400B4(Pool* pool, void* ptr)
{
    PoolBlock* block;
    if (pool->count)
    {
        block = (PoolBlock*)ptr - 1;
        if (block->prev == 0)
        {
            pool->head = block->next;
        }
        else
        {
            block->prev->next = block->next;
        }
        if (block->next == 0)
        {
            pool->tail = block->prev;
        }
        else
        {
            block->next->prev = block->prev;
        }
        block->magic = 0x08070F01;
        pool->used -= block->size;
        pool->count--;
    }
}
// Matched
void PoolSetInited_80040148(Pool* pool, int inited)
{
    pool->inited = inited;
}
// Matched
PoolBlock* PoolFindFreeSpace_80040150(Pool* pool, unsigned int size)
{
    char* best = 0;
    char* pos = (char*)pool->buffer;
    unsigned int bestsz;
    unsigned int total = pool->size;
    PoolBlock* blk = pool->head;
    char* end;
    PoolBlock* b;
    unsigned int i;
    int j;
    unsigned int gap;
    end = pos + total;
    bestsz = total;
    if (pool->count == 0)
    {
        if (end >= pos + size)
        {
            best = pos;
        }
    }
    else
    {
        for (i = 0; i <= pool->count; i++)
        {
            if (end >= pos + size)
            {
                j = 0;
                for (b = pool->head; b; b = b->next, j++)
                {
                    if (pos < (char*)b + b->size && (char*)b < pos + size)
                    {
                        break;
                    }
                }
                if (j == pool->count)
                {
                    gap = pool->size;
                    for (b = pool->head; b; b = b->next)
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
int IsPoolBlock_80040274(Pool* pool, void* ptr)
{
    return ((PoolBlock*)ptr)[-1].magic == 0x8FFFFFFF;
}
// Matched
void sub_8004028C(void)
{
    dword_80098688 = 0;
}
extern unsigned long* primAllocPtrs_800960A8[];
// Matched
void* AddPrimCopy_80040298(void* ot, void* prim, int words)
{
    int cur = primAllocPtr_800960A8[bDoubleBuffer_8008D428];
    ReadBytesInto_80040388((int*)cur, (int*)prim, words);
    addPrim(ot, primAllocPtr_800960A8[bDoubleBuffer_8008D428]);
    primAllocPtr_800960A8[bDoubleBuffer_8008D428] += words * 4;
    return (void*)cur;
}
// Matched
void CopyDoubleWords_80040360(int *pOut, int *pDataToWrite, int fileSize)
{
  int first; // $v0
  int second; // $v1

  do
  {
    first = *pDataToWrite;
    second = pDataToWrite[1];
    pDataToWrite += 2;
    --fileSize;
    *pOut = first;
    pOut[1] = second;
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
void CopyBytes_800403C8(char *pOut, unsigned char *fileBuffer, int fileSize)
{
  do
  {
    *pOut++ = *fileBuffer++;
    --fileSize;
  }
  while ( fileSize );
}
// Matched
void MemCopy_800403E8(void *overlayAddr, void *fileBuffer, unsigned int fileSize)
{
  unsigned int *overlayAddr_copy; // $s2
  unsigned char *pFileBuffer; // $s3
  unsigned int fileSize_copy; // $s1
  unsigned int alignedFileSize; // $s0

  overlayAddr_copy = overlayAddr;
  pFileBuffer = fileBuffer;
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
          CopyDoubleWords_80040360(overlayAddr, fileBuffer, alignedFileSize);
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
                titleMenuState_8008B558[1] = 1;
                titleMenuState_8008B558[0] = 0;
                currentGameState_8008D4B4 = eMainMenu_6;
            case eMainMenu_6:
                SetDisplayMode_80040658(1);
                currentGameState_8008D4B4 = ExecOverlay_80040DDC(eTitle);
                break;
            case eUnknown_7:
                SetDisplayMode_80040658(2);
                currentGameState_8008D4B4 = SelectIngameOrTitle_80040D5C();
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

int dword_8008686C[3] = { 112, 138, 0x800866D4 };
int dword_80086878[8] = { 126, 194, 0x808080, 0x8080, 0x404040, 128, 0x8000, 0x800000 };
int charWidthThresholds_80086898[3][12] = {
    { 112, 112, 96, 48, 32 },
    {
        126, 126, 126, 126, 108, 90, 72, 54,
        36, 36, 18,
    },
};
int dword_80086928[2] = { 0 };
int copyrightData_80086930[6] = { 1, 1, 0, 0, 0x80040A10 };
