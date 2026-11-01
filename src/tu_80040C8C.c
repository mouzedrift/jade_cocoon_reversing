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
#include "LIBCD.H"

extern unsigned long* ringBufferStart_800960B0;

typedef struct
{
    short x;
    short y;
    short w;
    short h;
} MovieRect;

typedef struct
{
    char pad_0[4];
    int is24bpp;
    char pad_8[8];
    short field_10;
    short field_12;
    char pad_14[2];
    unsigned short field_16;
    MovieRect rect;
} MovieInfo;

typedef struct
{
    void* buf0;
    void* buf1;
    int field_8;
    void* buf2;
    void* buf3;
    int field_14;
    MovieRect rect[2];
    int field_28;
    short cur_x;
    short cur_y;
    short field_30;
    unsigned short field_32;
    int field_34;
    int field_38;
} MovieCtx;

typedef struct
{
    char pad_0[0x28];
    unsigned int skipMask;
    char pad_2C[4];
    int doubleSpeed;
} MovieParams;

extern int bMovieFinished_800960FC;
extern unsigned short word_8009194C[];

#define MOVIE_W(i, v) ((i)->is24bpp ? (v) * 3 / 2 : (v))




extern enum GameStates (*overlayCallbacks_800869D0[])(void);

// Matched
void ShowDemoDisclaimer_80040C8C(void)
{
    sub_8001C290();
    drawEnvRed_8008D448[2] = 0;
    drawEnvRed_8008D448[1] = 0;
    drawEnvRed_8008D448[0] = 0;
    DrawIntroMovie_8001AF64(demoDisclaimer_800869A8);
}
// Matched
void PlayAnimeMovie_80040CCC(void)
{
    sub_8001C290();
    drawEnvRed_8008D448[2] = 0;
    drawEnvRed_8008D448[1] = 0;
    drawEnvRed_8008D448[0] = 0;
    DrawIntroMovie_8001AF64(introAnime_800869C8);
}
// Matched
void PlayAnimeMovie_80040D0C(void)
{
    PlayMovie_80040EB4(1);
    bStopDrawingMovie_8008D45C = 1;
}
// Matched
void sub_80040D34(struct_obj_D* p)
{
    if (!(unknownFlags_8008D678 & 0x20))
    {
        p->field_8 = PlayAnimeMovie_80040D0C;
    }
}
// Matched
int sub_80040D5C(void)
{
    if (saveData_8008B570.field_0 & 0x80)
    {
        unknownFlags_8008D678 &= ~0x10000000;
        word_8008B558[1] = 4;
        unknownFlags_8008D678 |= 0x20000000;
        return eMainMenu_6;
    }
    unknownFlags_8008D678 &= ~0x10000000;
    word_8008B558[1] = 1;
    return eIngame_12;
}
// Matched
enum GameStates ExecOverlay_80040DDC(enum OverlayIds overlayId)
{
    LoadOverlay_80020BF8(2, overlayId);
    return overlayCallbacks_800869D0[overlayId]();
}
// Matched
void sub_80040E28(MovieInfo* m)
{
    RECT r;
    r.x = m->rect.x;
    r.y = m->rect.y;
    r.w = MOVIE_W(m, m->rect.w);
    r.h = m->rect.h * 2;
    ClearImage(&r, 0, 0, 0);
}
#if 0
void PlayMovie_80040EB4(int arg0)
{
}
#endif
INCLUDE_ASM(PlayMovie_80040EB4);
// Matched
void sub_80041240(MovieCtx* c, MovieInfo* i)
{
    int x;
    int y;
    int x2;
    int y2;
    c->buf0 = (void*)0x801B9250;
    c->buf1 = (void*)0x801CA250;
    c->field_8 = 0;
    c->buf2 = (void*)0x801F0250;
    c->buf3 = (void*)0x801F2F50;
    c->field_14 = 0;
    x = MOVIE_W(i, i->field_10);
    y = i->field_12;
    x2 = MOVIE_W(i, i->field_10);
    y2 = i->field_12 + i->rect.h;
    c->rect[0].x = x;
    c->rect[0].y = y;
    c->rect[1].x = x2;
    c->field_28 = 0;
    c->field_34 = 0;
    c->rect[1].y = y2;
    c->field_38 = i->is24bpp;
    if (c->field_28 == 0)
    {
        c->cur_x = x;
        c->cur_y = y;
    }
    else
    {
        c->cur_x = x2;
        c->cur_y = y2;
    }
    c->field_30 = i->is24bpp ? 0x18 : 0x10;
    c->field_32 = i->field_16;
}
// Matched
void sub_80041358(int a0, int ring, int* stream)
{
    DecDCTReset(0);
    DecDCToutCallback((void (*)())ring);
    StSetRing(ringBufferStart_800960B0, 0x2A);
    StSetStream(stream[1], ((short*)stream)[4], -1, 0, 0);
}
// Matched
int SkipMovieButtonPressed_800413BC(MovieParams* c)
{
    if (bMovieFinished_800960FC == 1)
    {
        return 1;
    }
    if (c->skipMask != 0)
    {
        ProcessPad_8001C8E8(0);
        if (word_8009194C[0] & c->skipMask)
        {
            return 1;
        }
    }
    return 0;
}
INCLUDE_ASM(sub_80041424);
INCLUDE_ASM(sub_800415D8);
// Matched
void sub_80041724(MovieCtx* c)
{
    volatile int timeout = 0x13880;
    while (!c->field_34)
    {
        if (--timeout == 0)
        {
            c->field_34 = 1;
            c->field_28 = (c->field_28 == 0);
            c->cur_x = c->rect[c->field_28].x;
            c->cur_y = c->rect[c->field_28].y;
        }
    }
    c->field_34 = 0;
}
// Matched
void sub_800417BC(DslLOC* loc, MovieParams* p)
{
    unsigned char mode[8];
    if (p->doubleSpeed)
    {
        mode[0] = 0x80;
    }
    else
    {
        mode[0] = 0;
    }
    do
    {
        while (!DsControl(2, (unsigned char*)loc, 0))
        {
        }
        while (!DsControl(0xE, mode, 0))
        {
        }
        VSync(3);
    } while (!DsRead2(loc, mode[0] | 0x160));
}
// Matched
void AllocMdecVLCBuffer_80041848(void)
{
    if (!mdecVLCBuffer_80086F94)
    {
        mdecVLCBuffer_80086F94 = malloc3_8003FC4C(0x11000);
        DecDCTvlcBuild(mdecVLCBuffer_80086F94);
    }
}
// Matched
void sub_8004188C(void)
{
    if (!mdecVLCBuffer_80086F94)
    {
        mdecVLCBuffer_80086F94 = sub_8003BFB8(1);
        DecDCTvlcBuild(mdecVLCBuffer_80086F94);
    }
}
// Matched
void FreeMdecBuffer_800418CC(void)
{
    free3_8003FC6C(mdecVLCBuffer_80086F94);
    mdecVLCBuffer_80086F94 = 0;
}
// Matched
void sub_800418FC(void)
{
    sub_8003BFB8(0);
    mdecVLCBuffer_80086F94 = 0;
}
// Matched
void DecodeMdec_80041920(unsigned long* bs, unsigned long* buf, int mode)
{
    DecDCTvlc2(bs, buf, mdecVLCBuffer_80086F94);
    DecDCTinSync(0);
    DecDCTin(buf, mode);
}
INCLUDE_ASM(sub_8004196C);
