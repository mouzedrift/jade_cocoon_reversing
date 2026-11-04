// SOUNDTST.BIN
#include "common.h"
#include "funcs.h"
#include "globals.h"
#include "sound.h"
#include <LIBSND.H>

INCLUDE_OVERLAY_ASM(soundtst, dword_800A05A0);

extern char name_800AA340[];
// Matched
int sub_800A51AC()
{
    EndFade_8001C290();
    DrawIntroMovie_8001AF64(name_800AA340);
    return 6;
}

// the sound test's state (sub_800A51D8 sets it up); v[row_0 + 1] is the value the cursor row edits
typedef union SndTest
{
    struct
    {
        short row_0;    // cursor row (0..4)
        short seq_2;    // sound file to play (0..0x9A, 10 = none)
        short f4;
        short note_6;   // 0..0x7F
        short reverb_8; // 0..0x7F
        short xa_A;     // XA track (0..0x647)
        short voice_C;  // SsUtKeyOn voice, -1 = none
        short prog_E;   // note of voice_C
    } f;
    short v[8];
} SndTest;

extern void sub_800A5238();
void sub_800A51D8(int* a, SndTest* b)
{
    b->f.note_6 = 0x7F;
    b->f.reverb_8 = 0x32;
    b->f.row_0 = 0;
    b->f.seq_2 = 0;
    b->f.f4 = 0;
    b->f.xa_A = 0;
    a[2] = (int)sub_800A5238;
    FreeSound_80030D00((int)&systemSound_80091D40);
    LoadSound_80030A84(0x1B, &bgmSound_80091CE0);
}

extern unsigned short padPressed_8009194C;
extern unsigned short word_800918CC; // pad, with key repeat
extern short dword_800A70F0[][4]; // XA tracks: file, channel, start sector
extern char* name_800AA350[];
extern void PlayMusicSeq_80031260(void* a0, int a1, int a2);
extern void DrawBobbingCursorHand_8003D090(short x, short y, int a2, int a3, int idx);
extern void DrawText_8003E91C(int mode, void* str, void* pos, int z);
extern void DrawNumber_8003EF74(void* pos, int val, int ot);
// Matched
void sub_800A5238(int* a, SndTest* b)
{
    SVECTOR pos[12];
    SoundStruct* ss;
    int id;
    if (padPressed_8009194C & 0x40)
    {
        ss = &bgmSound_80091CE0;
        if (ss->field_4_seq_num >= 0)
        {
            SsSepStop(ss->field_C_sep_access_num, ss->field_4_seq_num);
            ss->field_4_seq_num = -1;
        }
        FreeSound_80030D00(ss);
        BeginFade_8001C260();
        bStopDrawingMovie_8008D45C = 1;
    }
    else if (padPressed_8009194C & 0x20)
    {
        if (b->f.row_0 == 0)
        {
            id = b->f.seq_2;
            if (id != 10)
            {
                ss = &bgmSound_80091CE0;
                if (ss->field_4_seq_num >= 0)
                {
                    SsSepStop(ss->field_C_sep_access_num, ss->field_4_seq_num);
                    ss->field_4_seq_num = -1;
                }
                FreeSound_80030D00(ss);
                LoadSound_80030A84(id, ss);
                PlayMusicSeq_80031260(ss, id, 1);
            }
        }
        else if (b->f.row_0 == 1)
        {
        }
        else if (b->f.row_0 == 2)
        {
            if (b->f.voice_C >= 0)
            {
                SsUtKeyOff(b->f.voice_C, bgmSound_80091CE0.field_0_vab_id, b->f.prog_E, 0x3f, 0);
            }
            b->f.prog_E = b->f.note_6;
            b->f.voice_C = SsUtKeyOn(bgmSound_80091CE0.field_0_vab_id, b->f.prog_E, 0, 0x3f, 0,
                                   saveData_8008B570.settings_1C.bits.sfxVol_14, saveData_8008B570.settings_1C.bits.sfxVol_14);
        }
        else
        {
            XaRequestPlay_80043564(dword_800A70F0[b->f.xa_A][1], dword_800A70F0[b->f.xa_A][2], dword_800A70F0[b->f.xa_A][3]);
        }
    }
    else if (padPressed_8009194C & 0x10)
    {
        ss = &bgmSound_80091CE0;
        if (ss->field_4_seq_num >= 0)
        {
            SsSepSetDecrescendo(ss->field_C_sep_access_num, ss->field_4_seq_num, 0x7f, 0x78);
            ss->field_4_seq_num = -1;
        }
        if (b->f.voice_C >= 0)
        {
            SsUtKeyOff(b->f.voice_C, bgmSound_80091CE0.field_0_vab_id, b->f.prog_E, 0x3f, 0);
        }
        b->f.voice_C = -1;
    }
    else if (word_800918CC & 0x1000)
    {
        b->f.row_0--;
    }
    else if (word_800918CC & 0x4000)
    {
        b->f.row_0++;
    }
    else if (word_800918CC & 0x8000)
    {
        b->v[b->f.row_0 + 1]--;
    }
    else if (word_800918CC & 0x2000)
    {
        b->v[b->f.row_0 + 1]++;
    }
    else if (word_800918CC & 4)
    {
        b->v[b->f.row_0 + 1] -= 10;
    }
    else if (word_800918CC & 8)
    {
        b->v[b->f.row_0 + 1] += 10;
    }
    if (b->f.row_0 >= 5)
    {
        b->f.row_0 = 4;
    }
    if (b->f.row_0 < 0)
    {
        b->f.row_0 = 0;
    }
    if (b->f.seq_2 >= 0x9b)
    {
        b->f.seq_2 = 0;
    }
    if (b->f.seq_2 < 0)
    {
        b->f.seq_2 = 0x9a;
    }
    if (b->f.note_6 >= 0x80)
    {
        b->f.note_6 = 0;
    }
    if (b->f.note_6 < 0)
    {
        b->f.note_6 = 0x7f;
    }
    if (b->f.reverb_8 >= 0x80)
    {
        b->f.reverb_8 = 0x7f;
    }
    if (b->f.reverb_8 < 0)
    {
        b->f.reverb_8 = 0;
    }
    if (b->f.xa_A >= 0x648)
    {
        b->f.xa_A = 0;
    }
    if (b->f.xa_A < 0)
    {
        b->f.xa_A = 0x647;
    }
    SsUtSetReverbDepth(b->f.reverb_8, b->f.reverb_8);
    DrawBobbingCursorHand_8003D090(0x12, b->f.row_0 * 16 + 0x46, 0, 0, 0);
    pos[0].vx = 0x14;
    pos[0].vy = 0x3c;
    DrawText_8003E91C(2, name_800AA350[0], &pos[0], 0);
    pos[1].vx = 0x78;
    pos[1].vy = 0x3c;
    DrawNumber_8003EF74(&pos[1], b->f.seq_2, 0);
    pos[2].vx = 0x14;
    pos[2].vy = 0x4c;
    DrawText_8003E91C(2, name_800AA350[1], &pos[2], 0);
    pos[3].vx = 0x14;
    pos[3].vy = 0x5c;
    DrawText_8003E91C(2, name_800AA350[2], &pos[3], 0);
    pos[4].vx = 0x78;
    pos[4].vy = 0x5c;
    DrawNumber_8003EF74(&pos[4], b->f.note_6, 0);
    pos[5].vx = 0x14;
    pos[5].vy = 0x6c;
    DrawText_8003E91C(2, name_800AA350[3], &pos[5], 0);
    pos[6].vx = 0x78;
    pos[6].vy = 0x6c;
    DrawNumber_8003EF74(&pos[6], b->f.reverb_8, 0);
    pos[7].vx = 0x14;
    pos[7].vy = 0x7c;
    DrawText_8003E91C(2, name_800AA350[4], &pos[7], 0);
    pos[8].vx = 0x78;
    pos[8].vy = 0x7c;
    DrawNumber_8003EF74(&pos[8], b->f.xa_A, 0);
    pos[9].vx = 0x14;
    pos[9].vy = 0xac;
    DrawText_8003E91C(2, name_800AA350[5], &pos[9], 0);
    pos[10].vx = 0x14;
    pos[10].vy = 0xbc;
    DrawText_8003E91C(2, name_800AA350[6], &pos[10], 0);
    pos[11].vx = 0x14;
    pos[11].vy = 0xcc;
    DrawText_8003E91C(2, name_800AA350[7], &pos[11], 0);
}

INCLUDE_OVERLAY_ASM(soundtst, dword_800A57D4);
