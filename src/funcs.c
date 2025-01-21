#include "globals.h"
#include "stubs.h"

// Match
int sub_80012178(int arg0)
{
    return (arg0 * 3) + 20;
}

// Match
int sub_80012140(int arg0)
{
    int result;
    int var_v0;
    int i;

    result = 20;

    for (i = 0; i < arg0; i++)
    {
        var_v0 = result + 9;
        result = var_v0 + (arg0 / 2);
        var_v0 = 29;
    }
    return result;
}

// Match
int sub_8003BA58(int arg0)
{
    int result;
    int var_v0;
    int i;

    result = 0;
    for (i = 0; i < 32; i++)
    {
        var_v0 = 1 << i;
        if (arg0 & var_v0)
        {
            result += 1;
        }
    }
    return result;
}

int sub_800125B8()
{
    int i;
    int result;

    result = 0;
    for (i = 0; i < 7; i++)
    {
        result += sub_8003BA58(dword_8008BD84[i]);
    }
    return result;
}

// Matched
int sub_8001C2FC()
{
    return (dword_800918B0 & 3) == 0;
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
            sub_80040A84();
            currentGameState_8008D4B4 = eCraveEntertainmentMovie_3;
            break;
        case eGenkiMovie_2:
            sub_80040658(1);
            sub_80040AEC();
            currentGameState_8008D4B4 = eIntroAnime_5;
            break;
        case eCraveEntertainmentMovie_3:
            sub_80040658(1);
            sub_80040B54();
            currentGameState_8008D4B4 = eGenkiMovie_2;
            break;
        case eUnknown_4:
            sub_80040658(1);
            sub_80040C8C();
            currentGameState_8008D4B4 = eIntroAnime_5;
            break;
        case eIntroAnime_5:
            sub_80040658(1);
            sub_80040CCC();
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
