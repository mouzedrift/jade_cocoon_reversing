#ifndef _TU_8003E884_H_
#define _TU_8003E884_H_

// a font's character code table (charTables_8008685C, per font)
typedef struct CharTable
{
    unsigned short* tbl;
    int lastChar_4; // codes up to this one are glyphs, the ones above are control codes
    int count;
} CharTable;
extern CharTable charTables_8008685C[];

extern void *dword_80086868[1];

#endif
