
extern int dword_800918B0;
extern int dword_8008BD84[93];

static const char* overlays[31] =
{
    "BATTLE.BIN",
    "BTEND.BIN",
    "BTLEXEC.BIN",
    "CHAPTER.BIN",
    "COMBAT.BIN",
    "COMBBTL.BIN",
    "COMBCHUI.BIN",
    "COMBCOM.BIN",
    "COMBLOAD.BIN",
    "COMBRSLT.BIN",
    "COMBSEL.BIN",
    "COMBSTRT.BIN",
    "CONFIG.BIN",
    "ENCOM.BIN",
    "EQUIP.BIN",
    "EVENTFNC.BIN",
    "GAME.BIN",
    "LOAD.BIN",
    "MAP.BIN",
    "MENU.BIN",
    "NAME.BIN",
    "PIERCE.BIN",
    "PLCOM.BIN",
    "SHOP.BIN",
    "SHOPCTRL.BIN",
    "SHOPENTR.BIN",
    "SOUNDTST.BIN",
    "TITLE.BIN",
    "TSTCOMPO.BIN",
    "TSTMODEL.BIN",
    "WPNSHOP.BIN"
};


int dword_8008BD84[93];


int sub_80012178(int arg0)
{
    return (arg0 * 3) + 20;
}

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

int sub_8001C2FC()
{
    return (dword_800918B0 & 3) == 0;
}
