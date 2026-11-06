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

extern void *unused_80086868[1];

void DrawText_8003E91C(int font, const char* str, short* pos, int ot);
void DrawColorText_8003EC2C(unsigned short* str, unsigned short* pos, int ot);
int GetCharWidth_8003E884(int idx, short c);
#endif
