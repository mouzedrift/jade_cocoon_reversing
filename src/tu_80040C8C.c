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
    char pad_8[2];
    short field_A;
    char pad_C[4];
    short field_10;
    short field_12;
    char pad_14[2];
    unsigned short field_16;
    MovieRect rect;
} MovieInfo;

typedef struct
{
    void* vlcbuf[2];
    int field_8;
    void* imgbuf[2];
    int field_14;
    MovieRect rect[2];
    int field_28;
    MovieRect slice;
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
    c->vlcbuf[0] = (void*)0x801B9250;
    c->vlcbuf[1] = (void*)0x801CA250;
    c->field_8 = 0;
    c->imgbuf[0] = (void*)0x801F0250;
    c->imgbuf[1] = (void*)0x801F2F50;
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
        c->slice.x = x;
        c->slice.y = y;
    }
    else
    {
        c->slice.x = x2;
        c->slice.y = y2;
    }
    c->slice.w = i->is24bpp ? 0x18 : 0x10;
    c->slice.h = i->field_16;
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
extern MovieCtx dword_800960C0;
extern int dword_800960F8;
extern int dword_80096100;
/* libcd's StCdIntrFlag lives in the PSY-Q .bss blob (0x8009AE6C), which has no symbols of its own */
extern char lib_bss[];
#define StCdIntrFlag (*(int*)(lib_bss + (0x8009AE6C - 0x8009AE60)))
extern void StCdInterrupt(void);
#if 0
// Not matched: slice-size product / rectid toggle scheduling differs (~60 lines)
void sub_80041424(void)
{
    MovieRect r;
    MovieRect r2;
    int id;
    int rem;
    if (dword_800960F8 && StCdIntrFlag)
    {
        StCdInterrupt();
        StCdIntrFlag = 0;
    }
    r = dword_800960C0.slice;
    id = dword_800960C0.field_14;
    dword_800960C0.field_14 = dword_800960C0.field_14 ? 0 : 1;
    if (dword_80096100 == 1 && (rem = dword_800960C0.rect[dword_800960C0.field_28].w % dword_800960C0.slice.w) != 0)
    {
        dword_80096100 = 0;
        dword_800960C0.slice.x += rem;
    }
    else
    {
        dword_800960C0.slice.x += dword_800960C0.slice.w;
    }
    if (dword_800960C0.slice.x < dword_800960C0.rect[dword_800960C0.field_28].x + dword_800960C0.rect[dword_800960C0.field_28].w)
    {
        DecDCTout(dword_800960C0.imgbuf[dword_800960C0.field_14], (dword_800960C0.slice.w * 16 * ((dword_800960C0.slice.h - 1) / 16 + 1)) >> 1);
    }
    else
    {
        dword_800960C0.field_34 = 1;
        dword_800960C0.field_28 = dword_800960C0.field_28 ? 0 : 1;
        dword_800960C0.slice.x = dword_800960C0.rect[dword_800960C0.field_28].x;
        dword_80096100 = 1;
        dword_800960C0.slice.y = dword_800960C0.rect[dword_800960C0.field_28].y;
    }
    LoadImage((RECT*)&r, dword_800960C0.imgbuf[id]);
}
#endif
INCLUDE_ASM(sub_80041424);
extern short movieWidth_80086F98;
extern short movieHeight_80086F9A;
// Matched
int sub_800415D8(MovieCtx* c, MovieInfo* m)
{
    u_long* addr;
    u_long* hdr;
    while (StGetNext(&addr, &hdr) == 1)
    {
    }
    if (hdr[2] >= m->field_A)
    {
        bMovieFinished_800960FC = 1;
    }
    if (movieWidth_80086F98 != ((u_short*)hdr)[8] || movieHeight_80086F9A != ((u_short*)hdr)[9])
    {
        sub_80040E28(m);
        movieWidth_80086F98 = ((u_short*)hdr)[8];
        movieHeight_80086F9A = ((u_short*)hdr)[9];
    }
    c->rect[0].w = c->rect[1].w = MOVIE_W(m, movieWidth_80086F98);
    c->rect[0].h = c->rect[1].h = movieHeight_80086F9A;
    c->slice.h = movieHeight_80086F9A;
    c->field_8 = c->field_8 == 0;
    DecDCTvlc2(addr, c->vlcbuf[c->field_8], mdecVLCBuffer_80086F94);
    StFreeRing(addr);
    return 1;
}
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
            c->slice.x = c->rect[c->field_28].x;
            c->slice.y = c->rect[c->field_28].y;
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
