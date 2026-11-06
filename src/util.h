#ifndef _TU_8003EF74_H_
#define _TU_8003EF74_H_

#include "event.h" // EventDesc

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

extern int unused_8008686C[3];
extern int unused_80086878[8];
extern int unused_80086928[2];
extern EventDesc copyrightData_80086930;

extern int unused_80086928[2];

void* malloc3_8003FC4C(unsigned int size);
void free3_8003FC6C(void* block);
void GameLoop_8004047C(void);
void SetGameBootState_80040470(void);
int CopyPlayerName_8003F860(unsigned char* pPlayerIn, unsigned short* pPlayerOut);
void ReadBytesInto_80040388(int* pOut, int* pSource, int count);
void CopyDoubleWords_80040360(int *pOut, int *pDataToWrite, int fileSize);
void MemCopy_800403E8(void *overlayAddr, void *fileBuffer, unsigned int fileSize);
void CopyBytes_800403C8(char *pOut, unsigned char *fileBuffer, int fileSize);
void ListFreeAll_8003FEC8(List* l);
void SetFontClutOffset_8003F900(int idx, int val);
void ListFree_8003FE38(List* l, void* ptr);
void HeapFree_8003FD18(void* ptr, int heap);
void* AddPrimCopy_80040298(void* ot, void* prim, int words);
void ListInit_8003FDB0(List* list);
int IsPoolBlock_80040274(Pool* pool, void* ptr);
void ClearUnusedWord_8004028C(void);
/* heap: 0 = defaultAllocList_80096090, 1 = malloc3, else the address of a Pool (magic 0x8FFFFFFF) or of a List */
void* HeapAlloc_8003FC8C(int size, int heap);
void PoolSetInited_80040148(Pool* pool, int inited);
unsigned short* EncodeText_8003F684(int mode, unsigned short* text);
void SetFontAbr_8003F9E8(int idx, int abr);
void* ListAlloc_8003FDC0(List* list, int size);
void DrawNumberRightAlignedFont1_8003F264(short* pos, int val, int ot);
void DrawNumberRightAligned_8003EFBC(short* pos, int val, int ot);
void EncodeName_8003F7C8(void* text, unsigned char* out);
void DrawNumber_8003EF74(short* pos, int val, int ot);
void PoolInit_8003FF1C(Pool* pool, unsigned int size);
void PoolDestroy_8003FF7C(Pool* pool);
void IntToText_8003F610(unsigned short* out, int val);
void UppercaseSjisName_8003F89C(unsigned short* name);
unsigned short* DecodeText_8003F748(int mode, unsigned short* text);
void IntToSjisReversed_8003F58C(unsigned char* buf, int val);
int WStrLen_8003FB60(unsigned short* str);
PoolBlock* PoolFindFreeSpace_80040150(Pool* pool, unsigned int size);
void* PoolAlloc_8003FFD0(Pool* pool, unsigned int size);
void PoolFree_800400B4(Pool* pool, void* ptr);
#endif
