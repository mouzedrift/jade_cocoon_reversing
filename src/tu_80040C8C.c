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
/* the game calls SsSetSerialVol without the header's short prototype (no sign extension) */
#define SsSetSerialVol SsSetSerialVol_proto
#include "LIBSND.H"
#undef SsSetSerialVol
#include "LIBMCX.H"
#include "LIBPRESS.H"
#include "LIBETC.H"
#include "LIBMCRD.H"
#include "sound.h"
#include "data_decls.h"
#include "LIBCD.H"
#include "tu_80040C8C.h"

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
    int fileId;
    int is24bpp;
    char pad_8[2];
    short field_A;
    char pad_C[4];
    short field_10;
    short field_12;
    char pad_14[2];
    unsigned short field_16;
    MovieRect rect;
    RECT screen;
    int skipMask;
    unsigned short volL;
    unsigned short volR;
    int doubleSpeed;
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
extern unsigned short padPressed_8009194C[];

extern MovieInfo strMovies_80086A4C[];
extern MovieCtx movieCtx_800960C0;
extern void SsSetSerialVol();
extern DISPENV* SetDefDispEnv(DISPENV* env, int x, int y, int w, int h);
void MovieDctOutCallback_80041424(void);
int MovieDecodeNextFrame_800415D8(MovieCtx* c, MovieInfo* m);
void MovieWaitFrameDone_80041724(MovieCtx* c, int unused);
void MovieStartCdStream_800417BC(DslLOC* loc, MovieParams* p);
void InitMovieCtx_80041240(MovieCtx* c, MovieInfo* i);
void InitMovieStream_80041358(int a0, int ring, int* stream);
int SkipMovieButtonPressed_800413BC(MovieParams* c);

#define MOVIE_W(i, v) ((i)->is24bpp ? (v) * 3 / 2 : (v))




extern enum GameStates (*overlayCallbacks_800869D0[])(void);

// Matched
void ShowDemoDisclaimer_80040C8C(void)
{
    EndFade_8001C290();
    drawEnvRed_8008D448[2] = 0;
    drawEnvRed_8008D448[1] = 0;
    drawEnvRed_8008D448[0] = 0;
    DrawIntroMovie_8001AF64(demoDisclaimer_800869A8);
}
// Matched
void PlayAnimeMovie_80040CCC(void)
{
    EndFade_8001C290();
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
void StartIntroAnime_80040D34(EventEntry* p)
{
    if (!(unknownFlags_8008D678 & 0x20))
    {
        p->cb_8 = (EventEntryFn)PlayAnimeMovie_80040D0C;
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
void ClearMovieRect_80040E28(MovieInfo* m)
{
    RECT r;
    r.x = m->rect.x;
    r.y = m->rect.y;
    r.w = MOVIE_W(m, m->rect.w);
    r.h = m->rect.h * 2;
    ClearImage(&r, 0, 0, 0);
}
// Matched
int PlayMovie_80040EB4(int idx)
{
    MovieInfo* m;
    DISPENV env;
    Data001File f;
    RECT unused_40; /* unused locals: the original frame has room for them */
    DslLOC loc;
    RECT unused_50;
    int n;
    int top;
    int x;
    int y;

    SetDispMask(0);
    m = &strMovies_80086A4C[idx];
    ClearMovieRect_80040E28(m);
    DATA_GetFile_8003C7CC(&f, m->fileId);
    SsSetSerialAttr(0, 0, 1);
    SsSetSerialVol(0, m->volL * 0x70 / 0x1000, m->volR * 0x70 / 0x1000);
    InitMovieCtx_80041240(&movieCtx_800960C0, m);
    AllocMdecVLCBuffer_80041848();
    ringBufferStart_800960B0 = (unsigned long*)0x801DB250;
    InitMovieStream_80041358((int)&f, (int)MovieDctOutCallback_80041424, (int*)m);
    bMovieFinished_800960FC = 0;
    do
    {
        loc = f.field_0_position;
        MovieStartCdStream_800417BC(&loc, (MovieParams*)m);
    } while (!MovieDecodeNextFrame_800415D8(&movieCtx_800960C0, m));
    while (!SkipMovieButtonPressed_800413BC((MovieParams*)m))
    {
        DecDCTin(movieCtx_800960C0.vlcbuf[movieCtx_800960C0.field_8], m->is24bpp ? 3 : 2);
        DecDCTout(movieCtx_800960C0.imgbuf[movieCtx_800960C0.field_14], ((movieCtx_800960C0.slice.w << 4) * ((movieCtx_800960C0.slice.h - 1) / 16 + 1)) >> 1);
        while (!MovieDecodeNextFrame_800415D8(&movieCtx_800960C0, m))
        {
            n = StGetBackloc(&loc);
            if (m->field_A < n || n <= 0)
            {
                loc = f.field_0_position;
            }
            MovieStartCdStream_800417BC(&loc, (MovieParams*)m);
        }
        MovieWaitFrameDone_80041724(&movieCtx_800960C0, 0);
        VSync(0);
        top = movieCtx_800960C0.field_28 == 0;
        x = MOVIE_W(m, m->rect.x);
        y = m->rect.y;
        if (top)
        {
            y += m->rect.h;
        }
        SetDefDispEnv(&env, x, y, MOVIE_W(m, m->rect.w), m->rect.h);
        if (m->is24bpp)
        {
            env.isrgb24 = m->is24bpp;
            env.disp.w = env.disp.w * 2 / 3;
        }
        env.screen.x = m->screen.x;
        env.screen.y = m->screen.y;
        env.screen.w = m->screen.w;
        env.screen.h = m->screen.h;
        PutDispEnv(&env);
        SetDispMask(1);
    }
    DecDCToutCallback(0);
    StUnSetRing();
    DsControlB(9, 0, 0);
    SsSetSerialVol(0, 0, 0);
    ClearMovieRect_80040E28(m);
    FreeMdecBuffer_800418CC();
    mdecVLCBuffer_80086F94 = 0;
    RestartDisplay_8001B230();
    return 1;
}
// Matched
void InitMovieCtx_80041240(MovieCtx* c, MovieInfo* i)
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
void InitMovieStream_80041358(int a0, int ring, int* stream)
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
        if (padPressed_8009194C[0] & c->skipMask)
        {
            return 1;
        }
    }
    return 0;
}
extern MovieCtx movieCtx_800960C0;
extern int dword_80096100;
extern int StCdIntrFlag;
extern void StCdInterrupt(void);
#if 0
// Not matched: field_14/dword_80096100 loads are hoisted above the slice copy, field_14 straight into s0 (orig: after the copy, lw v0 + move s0); 1 instruction short
void MovieDctOutCallback_80041424(void)
{
    MovieRect r;
    MovieRect r2;
    int id;
    int rem;
    if (movieCtx_800960C0.field_38 && StCdIntrFlag)
    {
        StCdInterrupt();
        StCdIntrFlag = 0;
    }
    r = movieCtx_800960C0.slice;
    id = movieCtx_800960C0.field_14;
    movieCtx_800960C0.field_14 = (movieCtx_800960C0.field_14 + 1) & 1;
    if (dword_80096100 == 1 && (rem = movieCtx_800960C0.rect[movieCtx_800960C0.field_28].w % movieCtx_800960C0.slice.w) != 0)
    {
        dword_80096100 = 0;
        movieCtx_800960C0.slice.x += rem;
    }
    else
    {
        movieCtx_800960C0.slice.x += movieCtx_800960C0.slice.w;
    }
    if (movieCtx_800960C0.slice.x < movieCtx_800960C0.rect[movieCtx_800960C0.field_28].x + movieCtx_800960C0.rect[movieCtx_800960C0.field_28].w)
    {
        DecDCTout(movieCtx_800960C0.imgbuf[movieCtx_800960C0.field_14], ((movieCtx_800960C0.slice.w << 4) * ((movieCtx_800960C0.slice.h - 1) / 16 + 1)) >> 1);
    }
    else
    {
        movieCtx_800960C0.field_34 = 1;
        movieCtx_800960C0.field_28 = movieCtx_800960C0.field_28 ? 0 : 1;
        movieCtx_800960C0.slice.x = movieCtx_800960C0.rect[movieCtx_800960C0.field_28].x;
        dword_80096100 = 1;
        movieCtx_800960C0.slice.y = movieCtx_800960C0.rect[movieCtx_800960C0.field_28].y;
    }
    LoadImage((RECT*)&r, movieCtx_800960C0.imgbuf[id]);
}
#endif
INCLUDE_ASM(MovieDctOutCallback_80041424);
extern short movieWidth_80086F98;
extern short movieHeight_80086F9A;
// Matched
int MovieDecodeNextFrame_800415D8(MovieCtx* c, MovieInfo* m)
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
        ClearMovieRect_80040E28(m);
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
void MovieWaitFrameDone_80041724(MovieCtx* c, int unused)
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
void MovieStartCdStream_800417BC(DslLOC* loc, MovieParams* p)
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
void AllocMdecVLCBufferInFileBuffer_8004188C(void)
{
    if (!mdecVLCBuffer_80086F94)
    {
        mdecVLCBuffer_80086F94 = SetFileBufferInUse_8003BFB8(1);
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
void ReleaseMdecVLCFileBuffer_800418FC(void)
{
    SetFileBufferInUse_8003BFB8(0);
    mdecVLCBuffer_80086F94 = 0;
}
// Matched
void DecodeMdec_80041920(unsigned long* bs, unsigned long* buf, int mode)
{
    DecDCTvlc2(bs, buf, mdecVLCBuffer_80086F94);
    DecDCTinSync(0);
    DecDCTin(buf, mode);
}
// Matched
int InterpolateWindowRect_8004196C(RECT* d, RECT* s, int cur, int max, int mode)
{
    if (cur < 0 || max < cur)
    {
        cur = max;
    }
    switch (mode)
    {
    case 0:
        d->w = s->w * cur / max;
        d->h = s->h * cur / max;
        d->x = s->x + s->w / 2 - d->w / 2;
        d->y = s->y + s->h / 2 - d->h / 2;
        break;
    case 1:
        d->w = s->w * cur / max;
        d->h = s->h * cur / max;
        d->x = s->x;
        d->y = s->y;
        break;
    case 2:
        d->w = s->w * cur / max;
        d->h = s->h * cur / max;
        d->x = s->x;
        d->y = s->y + s->h - d->h;
        break;
    case 3:
        d->w = s->w * cur / max;
        d->h = s->h * cur / max;
        d->x = s->x + s->w - d->w;
        d->y = s->y;
        break;
    case 4:
        d->w = s->w * cur / max;
        d->h = s->h * cur / max;
        d->x = s->x + s->w - d->w;
        d->y = s->y + s->h - d->h;
        break;
    case 5:
        d->x = s->x;
        d->y = s->y;
        d->w = s->w;
        d->h = s->h * cur / max;
        break;
    case 6:
        d->w = s->w;
        d->h = s->h * cur / max;
        d->x = s->x;
        d->y = s->y + s->h - d->h;
        break;
    case 7:
        d->w = s->w * cur / max;
        d->h = s->h;
        d->x = s->x;
        d->y = s->y;
        break;
    case 8:
        d->w = s->w * cur / max;
        d->h = s->h;
        d->x = s->x + s->w - d->w;
        d->y = s->y;
        break;
    case 9:
        d->w = s->w;
        d->h = s->h * cur / max;
        d->x = s->x;
        d->y = s->y + s->h / 2 - d->h / 2;
        break;
    case 10:
        d->w = s->w * cur / max;
        d->h = s->h;
        d->x = s->x + s->w / 2 - d->w / 2;
        d->y = s->y;
        break;
    }
    return max == cur;
}

char demoDisclaimer_800869A8[8] = { 144, 105, 8, 128 };
int introAnimeData_800869B0[6] = { 1, 1, 0, 0x8008D3E4, 0x80040D34 };
char introAnime_800869C8[8] = { 176, 105, 8, 128 };
enum GameStates (*overlayCallbacks_800869D0[31])(void) = { sub_800A0EF0, sub_800A1324, sub_800A51AC, sub_800A1B24, sub_800A200C, sub_800A7574 };
MovieInfo strMovies_80086A4C[26] = {
    {
        0x43A,
        1,
        { 1 },
        103,
        { 9, 0, 224, 39 },
        0,
        0,
        { 64, 1 },
        240,
        { 0, 0, 0x140, 240 },
        { 0, 0, 0x100, 240 },
        0,
        0x1000,
        0x1000,
        1,
    },
    {
        0x453,
        1,
        { 1 },
        0x87D,
        { 9, 0, 0, 53 },
        16,
        40,
        { 224, 1 },
        160,
        { 0, 0, 0x200, 240 },
        { 0, 0, 0x100, 240 },
        0x800,
        0x1000,
        0x1000,
        1,
    },
    {
        0x44B,
        0,
        { 1 },
        0xA45,
        { 8, 0, 192, 46 },
        0,
        32,
        { 64, 1 },
        160,
        { 0, 0, 0x140, 240 },
        { 0, 0, 0x100, 240 },
        0x800,
        0x1000,
        0x1000,
    },
    {
        0x44D,
        0,
        { 1 },
        0x809,
        { 8, 0, 64, 47 },
        0,
        32,
        { 64, 1 },
        160,
        { 0, 0, 0x140, 240 },
        { 0, 0, 0x100, 240 },
        0x800,
        0x1000,
        0x1000,
    },
    {
        0x44C,
        0,
        { 1 },
        0x28C,
        { 8, 0, 0, 47 },
        0,
        32,
        { 64, 1 },
        160,
        { 0, 0, 0x140, 240 },
        { 0, 0, 0x100, 240 },
        0x800,
        0x1000,
        0x1000,
    },
    {
        0x44E,
        0,
        { 1 },
        0x245,
        { 8, 0, 32, 45 },
        0,
        32,
        { 64, 1 },
        160,
        { 0, 0, 0x140, 240 },
        { 0, 0, 0x100, 240 },
        0x800,
        0x1000,
        0x1000,
    },
    {
        0x44F,
        0,
        { 1 },
        229,
        { 8, 0, 96, 40 },
        0,
        0,
        { 64, 1 },
        240,
        { 0, 0, 0x140, 240 },
        { 0, 0, 0x100, 240 },
        0x800,
        0x1000,
        0x1000,
    },
    {
        0x450,
        0,
        { 1 },
        126,
        { 8, 0, 96, 38 },
        0,
        0,
        { 64, 1 },
        240,
        { 0, 0, 0x140, 240 },
        { 0, 0, 0x100, 240 },
        0x800,
        0x1000,
        0x1000,
    },
    {
        0x451,
        0,
        { 1 },
        0x31B,
        { 8, 0, 96, 40 },
        0,
        0,
        { 64, 1 },
        240,
        { 0, 0, 0x140, 240 },
        { 0, 0, 0x100, 240 },
        0x800,
        0x1000,
        0x1000,
    },
    {
        0x452,
        0,
        { 1 },
        136,
        { 8, 0, 160, 39 },
        0,
        0,
        { 64, 1 },
        240,
        { 0, 0, 0x140, 240 },
        { 0, 0, 0x100, 240 },
        0x800,
        0x1000,
        0x1000,
    },
    {
        0x43E,
        0,
        { 1 },
        135,
        { 8, 0, 160, 24 },
        0,
        16,
        { 64, 1 },
        240,
        { 0, 16, 0x140, 240 },
        { 0, 0, 0x100, 240 },
        0x800,
        0x1000,
        0x1000,
    },
    {
        0x43F,
        0,
        { 1 },
        186,
        { 8, 0, 32, 31 },
        0,
        16,
        { 64, 1 },
        240,
        { 0, 16, 0x140, 240 },
        { 0, 0, 0x100, 240 },
        0x800,
        0x1000,
        0x1000,
    },
    {
        0x440,
        0,
        { 1 },
        23,
        { 8, 0, 32, 9 },
        0,
        16,
        { 64, 1 },
        240,
        { 0, 16, 0x140, 240 },
        { 0, 0, 0x100, 240 },
        0x800,
    },
    {
        0x441,
        0,
        { 1 },
        107,
        { 8, 0, 192, 20 },
        0,
        16,
        { 64, 1 },
        240,
        { 0, 16, 0x140, 240 },
        { 0, 0, 0x100, 240 },
        0x800,
        0x1000,
        0x1000,
    },
    {
        0x442,
        0,
        { 1 },
        135,
        { 8, 0, 128, 28 },
        0,
        16,
        { 64, 1 },
        240,
        { 0, 16, 0x140, 240 },
        { 0, 0, 0x100, 240 },
        0x800,
        0x1000,
        0x1000,
    },
    {
        0x443,
        0,
        { 1 },
        110,
        { 8, 0, 160, 18 },
        0,
        16,
        { 64, 1 },
        240,
        { 0, 16, 0x140, 240 },
        { 0, 0, 0x100, 240 },
        0x800,
        0x1000,
        0x1000,
    },
    {
        0x444,
        0,
        { 1 },
        96,
        { 8, 0, 32, 19 },
        0,
        16,
        { 64, 1 },
        240,
        { 0, 16, 0x140, 240 },
        { 0, 0, 0x100, 240 },
        0x800,
        0x1000,
        0x1000,
    },
    {
        0x445,
        0,
        { 1 },
        32,
        { 8, 0, 96, 10 },
        0,
        16,
        { 64, 1 },
        240,
        { 0, 16, 0x140, 240 },
        { 0, 0, 0x100, 240 },
        0x800,
    },
    {
        0x446,
        0,
        { 1 },
        150,
        { 8, 0, 192, 30 },
        0,
        16,
        { 64, 1 },
        240,
        { 0, 16, 0x140, 240 },
        { 0, 0, 0x100, 240 },
        0x800,
        0x1000,
        0x1000,
    },
    {
        0x447,
        0,
        { 1 },
        31,
        { 8, 0, 192, 11 },
        0,
        16,
        { 64, 1 },
        240,
        { 0, 16, 0x140, 240 },
        { 0, 0, 0x100, 240 },
        0x800,
    },
    {
        0x448,
        0,
        { 1 },
        200,
        { 8, 0, 64, 25 },
        0,
        16,
        { 64, 1 },
        240,
        { 0, 16, 0x140, 240 },
        { 0, 0, 0x100, 240 },
        0x800,
        0x1000,
        0x1000,
    },
    {
        0x449,
        0,
        { 1 },
        94,
        { 8, 0, 32, 22 },
        0,
        16,
        { 64, 1 },
        240,
        { 0, 16, 0x140, 240 },
        { 0, 0, 0x100, 240 },
        0x800,
        0x1000,
        0x1000,
    },
    {
        0x44A,
        0,
        { 1 },
        120,
        { 8, 0, 32, 27 },
        0,
        16,
        { 64, 1 },
        240,
        { 0, 16, 0x140, 240 },
        { 0, 0, 0x100, 240 },
        0x800,
        0x1000,
        0x1000,
    },
    {
        0x43C,
        1,
        { 1 },
        0x8E5,
        { 9, 0, 32, 49 },
        0,
        32,
        { 64, 1 },
        160,
        { 0, 0, 0x140, 240 },
        { 0, 0, 0x100, 240 },
        0,
        0x1000,
        0x1000,
        1,
    },
    {
        0x43D,
        1,
        { 1 },
        0x7AB,
        { 9, 0, 32, 48 },
        0,
        32,
        { 64, 1 },
        160,
        { 0, 0, 0x140, 240 },
        { 0, 0, 0x100, 240 },
        0,
        0x1000,
        0x1000,
        1,
    },
    {
        0x43B,
        1,
        { 1 },
        171,
        { 9, 0, 128, 45 },
        0,
        0,
        { 64, 1 },
        240,
        { 0, 0, 0x140, 240 },
        { 0, 0, 0x100, 240 },
        0,
        0x1000,
        0x1000,
        1,
    },
};
void *mdecVLCBuffer_80086F94 = 0;
short movieWidth_80086F98 = 0;
short movieHeight_80086F9A = 0;

unsigned long *ringBufferStart_800960B0 BSS = 0;
int dword_800960B4[3] BSS = { 0 };
MovieCtx movieCtx_800960C0 BSS = { 0 };
int bMovieFinished_800960FC BSS = 0;
int dword_80096100 BSS = 0;
int dword_80096104 BSS = 0;
