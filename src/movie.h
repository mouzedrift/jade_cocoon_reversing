#ifndef _TU_80040C8C_H_
#define _TU_80040C8C_H_

#include "globals.h"

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
    short frameCount_A; // last frame: ends the movie (MovieDecodeNextFrame_800415D8)
    char pad_C[4];
    short decodeX_10;   // vram position of the decoded frames
    short decodeY_12;
    char pad_14[2];
    unsigned short height_16;
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
    int vlcIdx_8;
    void* imgbuf[2];
    int imgIdx_14;
    MovieRect rect[2];
    int rectIdx_28;     // the rect being decoded into
    MovieRect slice;
    int frameDone_34;
    int is24bpp_38;
} MovieCtx;

typedef struct
{
    char pad_0[0x28];
    unsigned int skipMask;
    char pad_2C[4];
    int doubleSpeed;
} MovieParams;

extern int introAnimeData_800869B0[6];

enum GameStates TitleMain_800A0EF0(void);
enum GameStates CombatMain_800A1324(void);
enum GameStates TstModelMain_800A1B24(void);
enum GameStates TstCompoMain_800A200C(void);
enum GameStates SoundTestMain_800A51AC(void);
enum GameStates GameShutdown_800A7574(void);

extern int dword_800960B4[3];

extern int dword_80096104;

int InterpolateWindowRect_8004196C(RECT* dst, RECT* src, int cur, int max, int mode);
void ShowDemoDisclaimer_80040C8C(void);
void PlayAnimeMovie_80040CCC(void);
int SelectIngameOrTitle_80040D5C(void);
void ReleaseMdecVLCFileBuffer_800418FC(void);
void StartIntroAnime_80040D34(EventEntry* entry);
int PlayMovie_80040EB4(int idx);
void PlayAnimeMovie_80040D0C(void);
void FreeMdecBuffer_800418CC(void);
void AllocMdecVLCBufferInFileBuffer_8004188C(void);
void AllocMdecVLCBuffer_80041848(void);
void DecodeMdec_80041920(unsigned long* bs, unsigned long* buf, int mode);
void MovieDctOutCallback_80041424(void);
int MovieDecodeNextFrame_800415D8(MovieCtx* ctx, MovieInfo* movie);
void MovieWaitFrameDone_80041724(MovieCtx* ctx, int unused);
void MovieStartCdStream_800417BC(DslLOC* loc, MovieParams* params);
void InitMovieCtx_80041240(MovieCtx* ctx, MovieInfo* movie);
void InitMovieStream_80041358(int file, int ring, int* stream);
int SkipMovieButtonPressed_800413BC(MovieParams* params);
#endif
