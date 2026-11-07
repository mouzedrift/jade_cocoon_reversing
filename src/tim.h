#ifndef TU_80028C60_H
#define TU_80028C60_H

/* ParseTim_80029708 output */
typedef struct TimInfo
{
    int mode_valid;
    int mode;
    int clut_len;
    RECT crect;
    u_long* caddr;
    int pix_len;
    RECT prect;
    u_long* paddr;
} TimInfo;

void LoadTim_80029674(void* tim);
int ParseTim_80029708(void* outTim, void* inTim);
void LoadTimToVram_800296A0(void* tim);
int GetTiyFileCount_80028E68(int* file);
void LoadTiyTimsRelocated_80028FDC(int sprts, int polys, int tpages, int file, int count, int reloc, int hue);
void InitPolyFT4_80029A10(void* polyArg, void* timArg);
void InitPolyFT4FromTimData_800299DC(void* poly, void* tim);
void InitSprtFromTim_800298AC(SPRT* sprt, DR_TPAGE* tpage, TimInfo* tim);
void LoadTiy_80028E74(SPRT** sprts, POLY_FT4** polys, DR_TPAGE** tpages, int* file, void* heap);
void InitSprtFromTimData_80029868(int sprt, int tim, int tpage);
void TintVramImage_800292D0(void* rect, void* dst, short* tint);
void InitRoomCamera_80028DC0(void);
void OnRoomDataLoaded_80028C60(int req, char* data);
void AllocTiyPrims_800295D8(SPRT** sprts, POLY_FT4** polys, DR_TPAGE** tpages, int count, void* heap);
void LoadTiyTims_80028EEC(SPRT** sprts, POLY_FT4** polys, DR_TPAGE** tpages, int* file, int count);
void ShiftClutHue_80029D00(TimInfo* tim, unsigned int hue);
typedef struct
{
    unsigned short pixelDx_0;
    unsigned short pixelDy_2;
    unsigned short clut4Dx_4;
    unsigned short clut4Dy_6;
    unsigned short clut8Dx_8;
    unsigned short clut8Dy_A;
} TimReloc;
void RelocateTimInfo_800297C0(TimInfo* tim, TimReloc* reloc);
int Rgb555ToHsv_80029EA8(short* in, short* out);
int HsvToRgb555_8002A040(short* in, short* out);
void UnpackColor555_80029C68(unsigned short* dst, unsigned short* src);
void PackColor555_80029CB4(unsigned short* dst, unsigned short* src);
#endif
