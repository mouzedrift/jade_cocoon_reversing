
local function createOverlay(name, address)
    return {name = name, address = address}
end

OVERLAY_ADDRESS_1 = 0x800C9E88
OVERLAY_ADDRESS_2_ARENA_BATTLE_PAGE = 0x800A4088
OVERLAY_ADDRESS_3_MAIN = 0x800A05A0
OVERLAY_ADDRESS_4 = 0x800B66C0
OVERLAY_ADDRESS_5 = 0x800C29D0
OVERLAY_ADDRESS_6 = 0x800B6D00

LOADED_OVERLAYS = {
    createOverlay("No overlay", OVERLAY_ADDRESS_1),
    createOverlay("No overlay", OVERLAY_ADDRESS_2_ARENA_BATTLE_PAGE),
    createOverlay("No overlay", OVERLAY_ADDRESS_3_MAIN),
    createOverlay("No overlay", OVERLAY_ADDRESS_4),
    createOverlay("No overlay", OVERLAY_ADDRESS_5),
    createOverlay("No overlay", OVERLAY_ADDRESS_6)
}

OVERLAYS = {
    createOverlay("TITLE.BIN", OVERLAY_ADDRESS_3_MAIN),
    createOverlay("COMBAT.BIN", OVERLAY_ADDRESS_3_MAIN),
    createOverlay("SOUNDTST.BIN", OVERLAY_ADDRESS_3_MAIN),
    createOverlay("TSTMODEL.BIN", OVERLAY_ADDRESS_3_MAIN),
    createOverlay("TSTCOMPO.BIN", OVERLAY_ADDRESS_3_MAIN),
    createOverlay("GAME.BIN", OVERLAY_ADDRESS_3_MAIN),
    createOverlay("BATTLE.BIN", OVERLAY_ADDRESS_4),
    createOverlay("MENU.BIN", OVERLAY_ADDRESS_4),
    createOverlay("PLCOM.BIN", OVERLAY_ADDRESS_1),
    createOverlay("ENCOM.BIN", OVERLAY_ADDRESS_1),
    createOverlay("MAP.BIN", OVERLAY_ADDRESS_4),
    createOverlay("MENU.BIN", OVERLAY_ADDRESS_4),
    createOverlay("SHOPCTRL.BIN", OVERLAY_ADDRESS_4),
    createOverlay("SHOP.BIN", OVERLAY_ADDRESS_6),
    createOverlay("WPNSHOP.BIN", OVERLAY_ADDRESS_4),
    createOverlay("CONFIG.BIN", OVERLAY_ADDRESS_5),
    createOverlay("LOAD.BIN", OVERLAY_ADDRESS_4),
    createOverlay("NAME.BIN", OVERLAY_ADDRESS_6),
    createOverlay("EQUIP.BIN", OVERLAY_ADDRESS_5),
    createOverlay("SHOPENTR.BIN", OVERLAY_ADDRESS_6),
    createOverlay("CHAPTER.BIN", OVERLAY_ADDRESS_4),
    createOverlay("PIERCE.BIN", OVERLAY_ADDRESS_4),
    createOverlay("COMBCHUI.BIN", OVERLAY_ADDRESS_2_ARENA_BATTLE_PAGE),
    createOverlay("COMBSEL.BIN", OVERLAY_ADDRESS_2_ARENA_BATTLE_PAGE),
    createOverlay("COMBLOAD.BIN", OVERLAY_ADDRESS_2_ARENA_BATTLE_PAGE),
    createOverlay("COMBCOM.BIN", OVERLAY_ADDRESS_1),
    createOverlay("COMBSTRT.BIN", OVERLAY_ADDRESS_2_ARENA_BATTLE_PAGE),
    createOverlay("COMBBTL.BIN", OVERLAY_ADDRESS_2_ARENA_BATTLE_PAGE),
    createOverlay("COMBRSLT.BIN", OVERLAY_ADDRESS_2_ARENA_BATTLE_PAGE),
    createOverlay("EVENTFNC.BIN", OVERLAY_ADDRESS_6),
    createOverlay("BTLEXEC.BIN", OVERLAY_ADDRESS_1)
}

local function onOverlayLoad()
  local regs = PCSX.getRegisters()
  local overlay_idx = regs.GPR.n.a1

  -- in lua the first index starts at 1...
  overlay_idx = overlay_idx + 1
  if overlay_idx > #OVERLAYS then
      print("Overlay idx was out of bounds: " .. overlay_idx)
      return
  end

  local load_target_overlay = OVERLAYS[overlay_idx]
  if load_target_overlay == 0 then
    print("Couldn't find overlay in overlay table")
    return
  end

  for i, overlay in pairs(LOADED_OVERLAYS) do
    if overlay.address == load_target_overlay.address then
        LOADED_OVERLAYS[i].name = load_target_overlay.name
    end
  end
  print("Loading overlay " .. load_target_overlay.name .. " at address: " .. string.format("0x%x", load_target_overlay.address))
end

local function doOverlayText(overlay)
    imgui.TextUnformatted("Overlay at " .. string.format("0x%x", overlay.address) .. " is: " .. overlay.name)
end

function DrawImguiFrame()
    imgui.safe.Begin("Overlay Observer", function()
    imgui.TextUnformatted("Loaded overlays:")
    
    for _, overlay in pairs(LOADED_OVERLAYS) do
        doOverlayText(overlay)
    end
    end)
end

bp = PCSX.addBreakpoint(0x80020bf8, "Exec", 4, "Load overlay called", onOverlayLoad)
