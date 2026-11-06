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
#include "movie.h"
#include "util.h"
#include "model.h"
#include "cd.h"
#include "engine.h"
#include "cdread.h"
#include "main.h"
#include "boot.h"

extern unsigned long* ringBufferStart_800960B0;


extern int bMovieFinished_800960FC;
extern unsigned short padPressed_8009194C[];

extern MovieInfo strMovies_80086A4C[];
extern MovieCtx movieCtx_800960C0;
extern void SsSetSerialVol();
extern DISPENV* SetDefDispEnv(DISPENV* env, int x, int y, int w, int h);

#define MOVIE_W(i, v) ((i)->is24bpp ? (v) * 3 / 2 : (v))




extern enum GameStates (*overlayCallbacks_800869D0[])(void);

void ShowDemoDisclaimer_80040C8C(void)
{
    EndFade_8001C290();
    drawEnvRed_8008D448[2] = 0;
    drawEnvRed_8008D448[1] = 0;
    drawEnvRed_8008D448[0] = 0;
    DrawIntroMovie_8001AF64(demoDisclaimer_800869A8);
}
void PlayAnimeMovie_80040CCC(void)
{
    EndFade_8001C290();
    drawEnvRed_8008D448[2] = 0;
    drawEnvRed_8008D448[1] = 0;
    drawEnvRed_8008D448[0] = 0;
    DrawIntroMovie_8001AF64(introAnime_800869C8);
}
void PlayAnimeMovie_80040D0C(void)
{
    PlayMovie_80040EB4(1);
    bStopDrawingMovie_8008D45C = 1;
}
void StartIntroAnime_80040D34(EventEntry* entry)
{
    if (!(unknownFlags_8008D678 & 0x20))
    {
        entry->cb_8 = (EventEntryFn)PlayAnimeMovie_80040D0C;
    }
}
int SelectIngameOrTitle_80040D5C(void)
{
    if (saveData_8008B570.flags_0 & 0x80)
    {
        unknownFlags_8008D678 &= ~0x10000000;
        titleMenuState_8008B558[1] = 4;
        unknownFlags_8008D678 |= 0x20000000;
        return eMainMenu_6;
    }
    unknownFlags_8008D678 &= ~0x10000000;
    titleMenuState_8008B558[1] = 1;
    return eIngame_12;
}
enum GameStates ExecOverlay_80040DDC(enum OverlayIds overlayId)
{
    LoadOverlay_80020BF8(2, overlayId);
    return overlayCallbacks_800869D0[overlayId]();
}
void ClearMovieRect_80040E28(MovieInfo* movie)
{
    RECT rect;
    rect.x = movie->rect.x;
    rect.y = movie->rect.y;
    rect.w = MOVIE_W(movie, movie->rect.w);
    rect.h = movie->rect.h * 2;
    ClearImage(&rect, 0, 0, 0);
}
int PlayMovie_80040EB4(int idx)
{
    MovieInfo* movie;
    DISPENV env;
    Data001File file;
    RECT unused_40; /* unused locals: the original frame has room for them */
    DslLOC loc;
    RECT unused_50;
    int backFrame;
    int top;
    int x;
    int y;

    SetDispMask(0);
    movie = &strMovies_80086A4C[idx];
    ClearMovieRect_80040E28(movie);
    DATA_GetFile_8003C7CC(&file, movie->fileId);
    SsSetSerialAttr(0, 0, 1);
    SsSetSerialVol(0, movie->volL * 0x70 / 0x1000, movie->volR * 0x70 / 0x1000);
    InitMovieCtx_80041240(&movieCtx_800960C0, movie);
    AllocMdecVLCBuffer_80041848();
    ringBufferStart_800960B0 = (unsigned long*)0x801DB250;
    InitMovieStream_80041358((int)&file, (int)MovieDctOutCallback_80041424, (int*)movie);
    bMovieFinished_800960FC = 0;
    do
    {
        loc = file.field_0_position;
        MovieStartCdStream_800417BC(&loc, (MovieParams*)movie);
    } while (!MovieDecodeNextFrame_800415D8(&movieCtx_800960C0, movie));
    while (!SkipMovieButtonPressed_800413BC((MovieParams*)movie))
    {
        DecDCTin(movieCtx_800960C0.vlcbuf[movieCtx_800960C0.vlcIdx_8], movie->is24bpp ? 3 : 2);
        DecDCTout(movieCtx_800960C0.imgbuf[movieCtx_800960C0.imgIdx_14], ((movieCtx_800960C0.slice.w << 4) * ((movieCtx_800960C0.slice.h - 1) / 16 + 1)) >> 1);
        while (!MovieDecodeNextFrame_800415D8(&movieCtx_800960C0, movie))
        {
            backFrame = StGetBackloc(&loc);
            if (movie->frameCount_A < backFrame || backFrame <= 0)
            {
                loc = file.field_0_position;
            }
            MovieStartCdStream_800417BC(&loc, (MovieParams*)movie);
        }
        MovieWaitFrameDone_80041724(&movieCtx_800960C0, 0);
        VSync(0);
        top = movieCtx_800960C0.rectIdx_28 == 0;
        x = MOVIE_W(movie, movie->rect.x);
        y = movie->rect.y;
        if (top)
        {
            y += movie->rect.h;
        }
        SetDefDispEnv(&env, x, y, MOVIE_W(movie, movie->rect.w), movie->rect.h);
        if (movie->is24bpp)
        {
            env.isrgb24 = movie->is24bpp;
            env.disp.w = env.disp.w * 2 / 3;
        }
        env.screen.x = movie->screen.x;
        env.screen.y = movie->screen.y;
        env.screen.w = movie->screen.w;
        env.screen.h = movie->screen.h;
        PutDispEnv(&env);
        SetDispMask(1);
    }
    DecDCToutCallback(0);
    StUnSetRing();
    DsControlB(9, 0, 0);
    SsSetSerialVol(0, 0, 0);
    ClearMovieRect_80040E28(movie);
    FreeMdecBuffer_800418CC();
    mdecVLCBuffer_80086F94 = 0;
    RestartDisplay_8001B230();
    return 1;
}
void InitMovieCtx_80041240(MovieCtx* ctx, MovieInfo* movie)
{
    int x;
    int y;
    int x2;
    int y2;
    ctx->vlcbuf[0] = (void*)0x801B9250;
    ctx->vlcbuf[1] = (void*)0x801CA250;
    ctx->vlcIdx_8 = 0;
    ctx->imgbuf[0] = (void*)0x801F0250;
    ctx->imgbuf[1] = (void*)0x801F2F50;
    ctx->imgIdx_14 = 0;
    x = MOVIE_W(movie, movie->decodeX_10);
    y = movie->decodeY_12;
    x2 = MOVIE_W(movie, movie->decodeX_10);
    y2 = movie->decodeY_12 + movie->rect.h;
    ctx->rect[0].x = x;
    ctx->rect[0].y = y;
    ctx->rect[1].x = x2;
    ctx->rectIdx_28 = 0;
    ctx->frameDone_34 = 0;
    ctx->rect[1].y = y2;
    ctx->is24bpp_38 = movie->is24bpp;
    if (ctx->rectIdx_28 == 0)
    {
        ctx->slice.x = x;
        ctx->slice.y = y;
    }
    else
    {
        ctx->slice.x = x2;
        ctx->slice.y = y2;
    }
    ctx->slice.w = movie->is24bpp ? 0x18 : 0x10;
    ctx->slice.h = movie->height_16;
}
void InitMovieStream_80041358(int file, int ring, int* stream)
{
    DecDCTReset(0);
    DecDCToutCallback((void (*)())ring);
    StSetRing(ringBufferStart_800960B0, 0x2A);
    StSetStream(stream[1], ((short*)stream)[4], -1, 0, 0);
}
int SkipMovieButtonPressed_800413BC(MovieParams* params)
{
    if (bMovieFinished_800960FC == 1)
    {
        return 1;
    }
    if (params->skipMask != 0)
    {
        ProcessPad_8001C8E8(0);
        if (padPressed_8009194C[0] & params->skipMask)
        {
            return 1;
        }
    }
    return 0;
}
extern MovieCtx movieCtx_800960C0;
extern int movieSliceFirst_80096100;
extern int StCdIntrFlag;
extern void StCdInterrupt(void);
void MovieDctOutCallback_80041424(void)
{
    MovieRect slice;
    MovieRect unusedRect; // unused, but needed for the original stack frame
    unsigned int id;
    int rem;
    if (movieCtx_800960C0.is24bpp_38 && StCdIntrFlag)
    {
        StCdInterrupt();
        StCdIntrFlag = 0;
    }
    id = movieCtx_800960C0.imgIdx_14;
    slice = movieCtx_800960C0.slice;
    movieCtx_800960C0.imgIdx_14 = movieCtx_800960C0.imgIdx_14 == 0;
    if (movieSliceFirst_80096100 == 1 && (rem = movieCtx_800960C0.rect[movieCtx_800960C0.rectIdx_28].w % movieCtx_800960C0.slice.w) != 0)
    {
        movieSliceFirst_80096100 = 0;
        movieCtx_800960C0.slice.x += rem;
    }
    else
    {
        movieCtx_800960C0.slice.x += movieCtx_800960C0.slice.w;
    }
    if (movieCtx_800960C0.slice.x < movieCtx_800960C0.rect[movieCtx_800960C0.rectIdx_28].x + movieCtx_800960C0.rect[movieCtx_800960C0.rectIdx_28].w)
    {
        DecDCTout(movieCtx_800960C0.imgbuf[movieCtx_800960C0.imgIdx_14], ((movieCtx_800960C0.slice.w << 4) * ((movieCtx_800960C0.slice.h - 1) / 16 + 1)) >> 1);
    }
    else
    {
        movieCtx_800960C0.frameDone_34 = 1;
        movieCtx_800960C0.rectIdx_28 = movieCtx_800960C0.rectIdx_28 ? 0 : 1;
        movieCtx_800960C0.slice.x = movieCtx_800960C0.rect[movieCtx_800960C0.rectIdx_28].x;
        movieSliceFirst_80096100 = 1;
        movieCtx_800960C0.slice.y = movieCtx_800960C0.rect[movieCtx_800960C0.rectIdx_28].y;
    }
    LoadImage((RECT*)&slice, movieCtx_800960C0.imgbuf[id]);
}
extern short movieWidth_80086F98;
extern short movieHeight_80086F9A;
int MovieDecodeNextFrame_800415D8(MovieCtx* ctx, MovieInfo* movie)
{
    u_long* addr;
    u_long* hdr;
    while (StGetNext(&addr, &hdr) == 1)
    {
    }
    if (hdr[2] >= movie->frameCount_A)
    {
        bMovieFinished_800960FC = 1;
    }
    if (movieWidth_80086F98 != ((u_short*)hdr)[8] || movieHeight_80086F9A != ((u_short*)hdr)[9])
    {
        ClearMovieRect_80040E28(movie);
        movieWidth_80086F98 = ((u_short*)hdr)[8];
        movieHeight_80086F9A = ((u_short*)hdr)[9];
    }
    ctx->rect[0].w = ctx->rect[1].w = MOVIE_W(movie, movieWidth_80086F98);
    ctx->rect[0].h = ctx->rect[1].h = movieHeight_80086F9A;
    ctx->slice.h = movieHeight_80086F9A;
    ctx->vlcIdx_8 = ctx->vlcIdx_8 == 0;
    DecDCTvlc2(addr, ctx->vlcbuf[ctx->vlcIdx_8], mdecVLCBuffer_80086F94);
    StFreeRing(addr);
    return 1;
}
void MovieWaitFrameDone_80041724(MovieCtx* ctx, int unused)
{
    volatile int timeout = 0x13880;
    while (!ctx->frameDone_34)
    {
        if (--timeout == 0)
        {
            ctx->frameDone_34 = 1;
            ctx->rectIdx_28 = (ctx->rectIdx_28 == 0);
            ctx->slice.x = ctx->rect[ctx->rectIdx_28].x;
            ctx->slice.y = ctx->rect[ctx->rectIdx_28].y;
        }
    }
    ctx->frameDone_34 = 0;
}
void MovieStartCdStream_800417BC(DslLOC* loc, MovieParams* params)
{
    unsigned char mode[8];
    if (params->doubleSpeed)
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
void AllocMdecVLCBuffer_80041848(void)
{
    if (!mdecVLCBuffer_80086F94)
    {
        mdecVLCBuffer_80086F94 = malloc3_8003FC4C(0x11000);
        DecDCTvlcBuild(mdecVLCBuffer_80086F94);
    }
}
void AllocMdecVLCBufferInFileBuffer_8004188C(void)
{
    if (!mdecVLCBuffer_80086F94)
    {
        mdecVLCBuffer_80086F94 = SetFileBufferInUse_8003BFB8(1);
        DecDCTvlcBuild(mdecVLCBuffer_80086F94);
    }
}
void FreeMdecBuffer_800418CC(void)
{
    free3_8003FC6C(mdecVLCBuffer_80086F94);
    mdecVLCBuffer_80086F94 = 0;
}
void ReleaseMdecVLCFileBuffer_800418FC(void)
{
    SetFileBufferInUse_8003BFB8(0);
    mdecVLCBuffer_80086F94 = 0;
}
void DecodeMdec_80041920(unsigned long* bs, unsigned long* buf, int mode)
{
    DecDCTvlc2(bs, buf, mdecVLCBuffer_80086F94);
    DecDCTinSync(0);
    DecDCTin(buf, mode);
}
int InterpolateWindowRect_8004196C(RECT* dst, RECT* src, int cur, int max, int mode)
{
    if (cur < 0 || max < cur)
    {
        cur = max;
    }
    switch (mode)
    {
    case 0:
        dst->w = src->w * cur / max;
        dst->h = src->h * cur / max;
        dst->x = src->x + src->w / 2 - dst->w / 2;
        dst->y = src->y + src->h / 2 - dst->h / 2;
        break;
    case 1:
        dst->w = src->w * cur / max;
        dst->h = src->h * cur / max;
        dst->x = src->x;
        dst->y = src->y;
        break;
    case 2:
        dst->w = src->w * cur / max;
        dst->h = src->h * cur / max;
        dst->x = src->x;
        dst->y = src->y + src->h - dst->h;
        break;
    case 3:
        dst->w = src->w * cur / max;
        dst->h = src->h * cur / max;
        dst->x = src->x + src->w - dst->w;
        dst->y = src->y;
        break;
    case 4:
        dst->w = src->w * cur / max;
        dst->h = src->h * cur / max;
        dst->x = src->x + src->w - dst->w;
        dst->y = src->y + src->h - dst->h;
        break;
    case 5:
        dst->x = src->x;
        dst->y = src->y;
        dst->w = src->w;
        dst->h = src->h * cur / max;
        break;
    case 6:
        dst->w = src->w;
        dst->h = src->h * cur / max;
        dst->x = src->x;
        dst->y = src->y + src->h - dst->h;
        break;
    case 7:
        dst->w = src->w * cur / max;
        dst->h = src->h;
        dst->x = src->x;
        dst->y = src->y;
        break;
    case 8:
        dst->w = src->w * cur / max;
        dst->h = src->h;
        dst->x = src->x + src->w - dst->w;
        dst->y = src->y;
        break;
    case 9:
        dst->w = src->w;
        dst->h = src->h * cur / max;
        dst->x = src->x;
        dst->y = src->y + src->h / 2 - dst->h / 2;
        break;
    case 10:
        dst->w = src->w * cur / max;
        dst->h = src->h;
        dst->x = src->x + src->w / 2 - dst->w / 2;
        dst->y = src->y;
        break;
    }
    return max == cur;
}

EventDesc* demoDisclaimer_800869A8[2] = { &demoDisclaimerData_80086990 };
EventDesc introAnimeData_800869B0 = { 1, 1, 0, (EventNode**)dword_8008D3E4, (EventEntryFn)StartIntroAnime_80040D34 };
EventDesc* introAnime_800869C8[2] = { &introAnimeData_800869B0 };
enum GameStates (*overlayCallbacks_800869D0[31])(void) = { TitleMain_800A0EF0, CombatMain_800A1324, SoundTestMain_800A51AC, TstModelMain_800A1B24, TstCompoMain_800A200C, GameShutdown_800A7574 };
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
int movieSliceFirst_80096100 BSS = 0;
int dword_80096104 BSS = 0;
