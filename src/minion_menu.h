#ifndef MINION_MENU_H
#define MINION_MENU_H

/* cursor/state of the item/magic/ability list menus (ui_sprites.c, ability_menu.c, unit_query.c) */
typedef struct
{
    short cursor_0; // cursor row
    short scroll_2; // first shown row
    short windowFlags_4; // MenuWindowList.flags_0
    short ot_6;     // ot index
    short field_8;
    short fieldMenu_A; // 0: battle menu, 1: field menu (CheckItemUsable_80033AFC)
    Minion* minion_C;
} ListMenuState;

#endif
