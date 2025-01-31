import idc
import idautils
import os
import idaapi
import ida_ida
import ida_kernwin
from enum import IntEnum
import ida_auto

CURRENT_DIRECTORY = os.path.dirname(os.path.abspath(__file__))

# change this to your own overlay directory
OVERLAYS_DIR = r"C:\Users\mouzedrift\Documents\jade cocoon\release\DATA\DATA\OVER"

OVERLAY_ADDRESS_1 = 0x800C9E88
OVERLAY_ADDRESS_2_ARENA_BATTLE_PAGE = 0x800A4088
OVERLAY_ADDRESS_3_MAIN = 0x800A05A0
OVERLAY_ADDRESS_4 = 0x800B66C0
OVERLAY_ADDRESS_5 = 0x800C29D0
OVERLAY_ADDRESS_6 = 0x800B6D00

# MENU.BIN has 2 entries for some reason
OVERLAYS = {
    "TITLE.BIN": OVERLAY_ADDRESS_3_MAIN,
    "COMBAT.BIN": OVERLAY_ADDRESS_3_MAIN,
    "SOUNDTST.BIN": OVERLAY_ADDRESS_3_MAIN,
    "TSTMODEL.BIN": OVERLAY_ADDRESS_3_MAIN,
    "TSTCOMPO.BIN": OVERLAY_ADDRESS_3_MAIN,
    "GAME.BIN": OVERLAY_ADDRESS_3_MAIN,
    "BATTLE.BIN": OVERLAY_ADDRESS_4,
    "MENU.BIN": OVERLAY_ADDRESS_4,
    "PLCOM.BIN": OVERLAY_ADDRESS_1,
    "ENCOM.BIN": OVERLAY_ADDRESS_1,
    "MAP.BIN": OVERLAY_ADDRESS_4,
    #"MENU.BIN": OVERLAY_ADDRESS_4,
    "SHOPCTRL.BIN": OVERLAY_ADDRESS_4,
    "SHOP.BIN": OVERLAY_ADDRESS_6,
    "WPNSHOP.BIN": OVERLAY_ADDRESS_4,
    "CONFIG.BIN": OVERLAY_ADDRESS_5,
    "LOAD.BIN": OVERLAY_ADDRESS_4,
    "NAME.BIN": OVERLAY_ADDRESS_6,
    "EQUIP.BIN": OVERLAY_ADDRESS_5,
    "SHOPENTR.BIN": OVERLAY_ADDRESS_6,
    "CHAPTER.BIN": OVERLAY_ADDRESS_4,
    "PIERCE.BIN": OVERLAY_ADDRESS_4,
    "COMBCHUI.BIN": OVERLAY_ADDRESS_2_ARENA_BATTLE_PAGE,
    "COMBSEL.BIN": OVERLAY_ADDRESS_2_ARENA_BATTLE_PAGE,
    "COMBLOAD.BIN": OVERLAY_ADDRESS_2_ARENA_BATTLE_PAGE,
    "COMBCOM.BIN": OVERLAY_ADDRESS_1,
    "COMBSTRT.BIN": OVERLAY_ADDRESS_2_ARENA_BATTLE_PAGE,
    "COMBBTL.BIN": OVERLAY_ADDRESS_2_ARENA_BATTLE_PAGE,
    "COMBRSLT.BIN": OVERLAY_ADDRESS_2_ARENA_BATTLE_PAGE,
    "EVENTFNC.BIN": OVERLAY_ADDRESS_6,
    "BTLEXEC.BIN": OVERLAY_ADDRESS_1
}

class OverlayLoadType(IntEnum):
    IdbEndAddress = 0,
    OverlayStartAddress = 1

def get_lowest_overlay_address():
    result = OVERLAY_ADDRESS_1
    for address in OVERLAYS.values():
        if address < result:
            result = address

    return result

def get_highest_overlay_address():
    result = OVERLAY_ADDRESS_1
    for address in OVERLAYS.values():
        if address > result:
            result = address

    return result

def get_non_overlapping_overlay_size(overlay_address):
    result_size = 0
    for address in OVERLAYS.values():
        if address <= overlay_address:
            continue
        
        size = address - overlay_address
        if size > result_size:
            result_size = size

    return result_size

def all_overlays_exist():
    for overlay_name in OVERLAYS.keys():
        overlay_path = os.path.join(OVERLAYS_DIR, overlay_name)
        if not os.path.exists(overlay_path):
            ida_kernwin.warning(f"Could not find {overlay_path}")
            return False
        
    return True

def add_overlay(overlay_name, overlay_address, load_type: OverlayLoadType):
    overlay_path = os.path.join(OVERLAYS_DIR, overlay_name)
    overlay_size = os.stat(overlay_path).st_size
    li = idaapi.open_linput(overlay_path, False)

    if load_type == OverlayLoadType.OverlayStartAddress:
        idaapi.load_binary_file(overlay_path, li, 0, 0, 0, overlay_address , 0)
        idaapi.add_segm(0, start=overlay_address, end=overlay_address + overlay_size, name=overlay_name, sclass="CODE")
        idc.set_segm_attr(overlay_address, idc.SEGATTR_PERM, idaapi.SEGPERM_MAXVAL)
        print(f"Loaded overlay {overlay_name} into the idb ({overlay_size} bytes) at {hex(overlay_address)}")
    elif load_type == OverlayLoadType.IdbEndAddress:
        idb_end_ea = ida_ida.inf_get_max_ea()
        idaapi.load_binary_file(overlay_path, li, 0, 0, 0, idb_end_ea , 0)
        idaapi.add_segm(0, start=idb_end_ea, end=idb_end_ea + overlay_size, name=overlay_name, sclass="CODE")
        idc.set_segm_attr(idb_end_ea, idc.SEGATTR_PERM, idaapi.SEGPERM_MAXVAL)
        #idaapi.add_mapping(idb_end_ea, idb_end_ea + overlay_size, overlay_size)
        print(f"Loaded overlay {overlay_name} into the idb ({overlay_size} bytes) at {hex(idb_end_ea)}")

def add_all_overlays(load_type: OverlayLoadType):
    if not all_overlays_exist():
        return
    
    for overlay_name, overlay_address in OVERLAYS.items():
        add_overlay(overlay_name, overlay_address, load_type)
    
def rename_overlay_funcs():
    for segment_ea in idautils.Segments():
        segment_name = idc.get_segm_name(segment_ea)
        if ".BIN" not in segment_name:
            continue

        for func_ea in idautils.Functions(segment_ea, idc.get_segm_end(segment_ea)):
            func_name = idc.get_func_name(func_ea)
            overlay_name = segment_name.split(".BIN")[0]
            print(f"rename func {func_name}")
            idc.set_name(func_ea, f"OVER_{overlay_name}_{func_name}")

print(f"lowest overlay address: {hex(get_lowest_overlay_address())}")
print(f"highest overlay address: {hex(get_highest_overlay_address())}")

#add_all_overlays(load_type=OverlayLoadType.OverlayStartAddress)
#ida_auto.auto_wait()
#rename_overlay_funcs()

add_overlay("EVENTFNC.BIN", OVERLAY_ADDRESS_6, OverlayLoadType.OverlayStartAddress)
add_overlay("TITLE.BIN", OVERLAY_ADDRESS_3_MAIN, OverlayLoadType.OverlayStartAddress)
