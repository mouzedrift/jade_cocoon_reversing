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

INCLUDE_DATA(dword_80098198);
INCLUDE_DATA(dword_80098688);

INCLUDE_ASM(sub_8003EF74);
INCLUDE_ASM(sub_8003EFBC);
INCLUDE_ASM(sub_8003F264);
INCLUDE_ASM(sub_8003F544);
INCLUDE_ASM(sub_8003F58C);
INCLUDE_ASM(sub_8003F610);
#if 0
unsigned short* sub_8003F684(int a0, int a1)
{
    return 0;
}
#endif
INCLUDE_ASM(sub_8003F684);
INCLUDE_ASM(sub_8003F748);
INCLUDE_ASM(sub_8003F7C8);
// Matched
int CopyPlayerName_8003F860(unsigned char* pPlayerIn, unsigned short* pPlayerOut)
{
    int i;

    if (*pPlayerOut == 0xFFFF)
    {
        for (i = 0; i < MAX_PLAYER_NAME_LENGTH; i++)
        {
            pPlayerOut[i] = pPlayerIn[i];
        }
        return 1;
    }

    return 0;
}
INCLUDE_ASM(sub_8003F89C);
// Matched
void sub_8003F900(int idx, short val)
{
    struct_2C* p = &dword_80095FB0[idx];
    p->field_2A = val;
}
INCLUDE_ASM(sub_8003F928);
// Matched
void sub_8003F9E8(int idx, int v)
{
    struct_2C* p = &dword_80095FB0[idx];
    sub_80033048(p->field_14, v);
}
INCLUDE_ASM(sub_8003FA2C);
INCLUDE_ASM(sub_8003FB60);
INCLUDE_ASM(sub_8003FBD4);
#if 0
void* malloc3_8003FC4C(unsigned int s)
{
    return malloc3(s);
}
#endif
INCLUDE_ASM(malloc3_8003FC4C);
#if 0
void free3_8003FC6C(void* block)
{
    free3(block);
}
#endif
INCLUDE_ASM(free3_8003FC6C);
#if 0
int sub_8003FC8C(int a0, int a1)
{
    return 0;
}
#endif
INCLUDE_ASM(sub_8003FC8C);
#if 0
void sub_8003FD18(int arg0)
{
}
#endif
INCLUDE_ASM(sub_8003FD18);
// Matched
void sub_8003FDB0(int* p)
{
    p[0] = 0;
    p[1] = 0;
    p[2] = 0;
}
INCLUDE_ASM(sub_8003FDC0);
#if 0
void sub_8003FE38(void* arg0, int arg1)
{
}
#endif
INCLUDE_ASM(sub_8003FE38);
#if 0
void sub_8003FEC8(void* arg0)
{
}
#endif
INCLUDE_ASM(sub_8003FEC8);
INCLUDE_ASM(sub_8003FF1C);
INCLUDE_ASM(sub_8003FF7C);
INCLUDE_ASM(sub_8003FFD0);
INCLUDE_ASM(sub_800400B4);
// Matched
void sub_80040148(int* p, int v)
{
    p[1] = v;
}
INCLUDE_ASM(sub_80040150);
// Matched
int sub_80040274(int a0, int* a1)
{
    return a1[-4] == 0x8FFFFFFF;
}
// Matched
void sub_8004028C(void)
{
    dword_80098688 = 0;
}
#if 0
void sub_80040298(void* arg0, void* arg1, int arg2)
{
}
#endif
INCLUDE_ASM(sub_80040298);
// Matched
void sub_80040360(int *pOut, int *pDataToWrite, int fileSize)
{
  int result; // $v0
  int v4; // $v1

  do
  {
    result = *pDataToWrite;
    v4 = pDataToWrite[1];
    pDataToWrite += 2;
    --fileSize;
    *pOut = result;
    pOut[1] = v4;
    pOut += 2;
  }
  while ( fileSize );
}
// Matched
void ReadBytesInto_80040388(int* pOut, int* pSource, int count)
{
    int dataToCopy;

    do
    {
        dataToCopy = *pSource++;
        *pOut++ = dataToCopy;
        --count;
    } while (count);
}
INCLUDE_ASM(sub_800403A8);
// Matched
void sub_800403C8(char *a1, unsigned char *fileBuffer, int fileSize)
{
  do
  {
    *a1++ = *fileBuffer++;
    --fileSize;
  }
  while ( fileSize );
}
// Matched
void sub_800403E8(unsigned int *overlayAddr, unsigned int *fileBuffer, unsigned int fileSize)
{
  unsigned int *overlayAddr_copy; // $s2
  unsigned char *pFileBuffer; // $s3
  unsigned int fileSize_copy; // $s1
  unsigned int alignedFileSize; // $s0

  overlayAddr_copy = overlayAddr;
  pFileBuffer = (unsigned char *)fileBuffer;
  fileSize_copy = fileSize;
  if ( fileSize )
  {
    if ( ((unsigned char)overlayAddr & 3) == 0 )
    {
      alignedFileSize = fileSize >> 3;
      if ( ((unsigned char)fileBuffer & 3) == 0 )
      {
        fileSize_copy = fileSize & 7;
        if ( alignedFileSize )
        {
          sub_80040360(overlayAddr, (int *)fileBuffer, alignedFileSize);
          overlayAddr_copy += 2 * alignedFileSize;
          pFileBuffer += 8 * alignedFileSize;
        }
      }
    }
    if ( fileSize_copy )
      sub_800403C8(overlayAddr_copy, pFileBuffer, fileSize_copy);
  }
}
// Matched
void SetGameBootState_80040470(void)
{
    currentGameState_8008D4B4 = eGameBoot_0;
}
// Matched
void GameLoop_8004047C(void)
{
    do
    {
        switch (currentGameState_8008D4B4)
        {
            case eGameBoot_0:
                sub_80040718();
                LoadPublicTiyAndFtg_800407D0();
                currentGameState_8008D4B4 = eIntroCopyright_1;
                break;
            case eIntroCopyright_1:
                sub_80040658(3);
                ShowCopyright_80040A84();
                currentGameState_8008D4B4 = eCraveEntertainmentMovie_3;
                break;
            case eGenkiMovie_2:
                sub_80040658(1);
                PlayGenkiMovie_80040AEC();
                currentGameState_8008D4B4 = eIntroAnime_5;
                break;
            case eCraveEntertainmentMovie_3:
                sub_80040658(1);
                PlayCraveEntertainmentMovie_80040B54();
                currentGameState_8008D4B4 = eGenkiMovie_2;
                break;
            case eUnknown_4:
                sub_80040658(1);
                ShowDemoDisclaimer_80040C8C();
                currentGameState_8008D4B4 = eIntroAnime_5;
                break;
            case eIntroAnime_5:
                sub_80040658(1);
                PlayAnimeMovie_80040CCC();
                word_8008B558[1] = 1;
                word_8008B558[0] = 0;
                currentGameState_8008D4B4 = eMainMenu_6;
            case eMainMenu_6:
                sub_80040658(1);
                currentGameState_8008D4B4 = ExecOverlay_80040DDC(eTitle);
                break;
            case eUnknown_7:
                sub_80040658(2);
                currentGameState_8008D4B4 = sub_80040D5C();
                break;
            case eBattleArenaMenu_8:
                sub_80040658(2);
                currentGameState_8008D4B4 = ExecOverlay_80040DDC(eCombat);
                break;
            case eSoundTst_9:
                sub_80040658(2);
                currentGameState_8008D4B4 = ExecOverlay_80040DDC(eSoundTst);
                break;
            case eTstModel_10:
                sub_80040658(2);
                currentGameState_8008D4B4 = ExecOverlay_80040DDC(eTstModel);
                break;
            case eTstCompo_11:
                sub_80040658(2);
                currentGameState_8008D4B4 = ExecOverlay_80040DDC(eTstCompo);
                break;
            case eIngame_12:
                sub_80040658(2);
                LoadOverlay_80020BF8(2, eEventFnc_29);
                currentGameState_8008D4B4 = ExecOverlay_80040DDC(eGame);
                break;
            case eQuitToIntroAnime_13:
                currentGameState_8008D4B4 = eIntroAnime_5;
                break;
            case eToMainMenu_14:
                currentGameState_8008D4B4 = eMainMenu_6;
                break;

            case eUnknown_15:
            default:
                break;
        }
    } while ((unknownFlags_8008D678 & 4) == 0);
}
