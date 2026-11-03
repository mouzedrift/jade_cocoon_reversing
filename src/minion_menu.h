#ifndef MINION_MENU_H
#define MINION_MENU_H

/* cursor/state of the item/magic/ability list menus (tu_8002BE10.c, tu_8002CE28.c, tu_80031A94.c) */
typedef struct
{
    short field_0; // cursor row
    short field_2; // first shown row
    short field_4; // window
    short field_6; // ot index
    short field_8;
    short field_A;
    Minion* field_C_minion;
} struct_minion_ref;

#endif
