-- Jade Cocoon helpers for PCSX-Redux (see docs/testing_in_emulator.md).
--
-- Load it from the Lua console with  Support.extra.dofile("path/to/pcsx.lua")  or start the emulator
-- with  -dofile path/to/pcsx.lua . Breakpoints need the debugger enabled (Configuration > Emulation >
-- Enable debugger, or -debugger) and the interpreter (no dynarec).
--
-- What it gives you:
--   * an "Overlay Observer" window and a log line whenever the game loads an overlay
--   * memory readers: u8 s8 u16 s16 u32 s32 (addr), str(addr [, max]), hexdump(addr, size)
--   * watch{...}: break on a function, print registers and fields of the struct an argument points to,
--     without stopping the game (or pausing it with pause = true)
--   * watchWrite{...}: report every write to an address range (who writes a field)
--   * dumpStruct(addr, fields): print fields at an address once (from the console)
--
-- Field lists are { name, offset, type } with type one of u8 s8 u16 s16 u32 s32 ptr str, e.g.
--   watch{ addr = 0x800C6F58, overlay = "PIERCE.BIN", name = "sub_800C6F58", arg = "a0",
--          fields = { {"next_8", 0x8, "ptr"}, {"x_31C", 0x31C, "s16"} } }
-- Overlays share load addresses, so give `overlay` for a breakpoint inside one: it then only reports
-- while that overlay is the one loaded at that address.

local function createOverlay(name, address)
    return {name = name, address = address}
end

OVERLAY_ADDRESS_1 = 0x800C9E88
OVERLAY_ADDRESS_2_ARENA_BATTLE_PAGE = 0x800A4088
OVERLAY_ADDRESS_3_MAIN = 0x800A05A0
OVERLAY_ADDRESS_4 = 0x800B66C0
OVERLAY_ADDRESS_5 = 0x800C29D0
OVERLAY_ADDRESS_6 = 0x800B6D00
OVERLAY_ADDRESS_PIERCE = 0x800C6F40

LOADED_OVERLAYS = {
    createOverlay("No overlay", OVERLAY_ADDRESS_1),
    createOverlay("No overlay", OVERLAY_ADDRESS_2_ARENA_BATTLE_PAGE),
    createOverlay("No overlay", OVERLAY_ADDRESS_3_MAIN),
    createOverlay("No overlay", OVERLAY_ADDRESS_4),
    createOverlay("No overlay", OVERLAY_ADDRESS_5),
    createOverlay("No overlay", OVERLAY_ADDRESS_6),
    createOverlay("No overlay", OVERLAY_ADDRESS_PIERCE)
}

-- index = enum OverlayIds (src/enums.h) + 1, address = scripts/overlays.py LOAD_ADDRESSES
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
    createOverlay("PIERCE.BIN", OVERLAY_ADDRESS_PIERCE),
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

-- ------------------------------------------------------------------------------------------------ memory

local function ram(addr)
    return PCSX.getMemPtr() + bit.band(addr, 0x1FFFFF)
end

function u8(addr) return ram(addr)[0] end
function s8(addr) return ffi.cast("int8_t*", ram(addr))[0] end
function u16(addr) return ffi.cast("uint16_t*", ram(addr))[0] end
function s16(addr) return ffi.cast("int16_t*", ram(addr))[0] end
function u32(addr) return tonumber(ffi.cast("uint32_t*", ram(addr))[0]) end
function s32(addr) return tonumber(ffi.cast("int32_t*", ram(addr))[0]) end

-- game strings are Shift-JIS, this prints the ASCII part and escapes the rest
function str(addr, max)
    local out = {}
    for i = 0, (max or 64) - 1 do
        local c = u8(addr + i)
        if c == 0 then break end
        out[#out + 1] = (c >= 32 and c < 127) and string.char(c) or string.format("\\x%02x", c)
    end
    return table.concat(out)
end

function hexdump(addr, size)
    for row = 0, size - 1, 16 do
        local words = {}
        for i = 0, math.min(16, size - row) - 1, 4 do
            words[#words + 1] = string.format("%08x", u32(addr + row + i))
        end
        print(string.format("%08x: %s", addr + row, table.concat(words, " ")))
    end
end

local READERS = {u8 = u8, s8 = s8, u16 = u16, s16 = s16, u32 = u32, s32 = s32}

local function field(base, f)
    local name, off, ty = f[1], f[2], f[3] or "u32"
    if ty == "str" then
        return string.format("%s=\"%s\"", name, str(base + off))
    elseif ty == "ptr" or ty == "u32" then
        return string.format("%s=0x%08x", name, u32(base + off))
    end
    return string.format("%s=%d", name, READERS[ty](base + off))
end

local function isRam(p)
    return p >= 0x80000000 and p < 0x80200000
end

function dumpStruct(addr, fields)
    local out = {}
    for _, f in ipairs(fields) do out[#out + 1] = field(addr, f) end
    print(string.format("[%08x] %s", addr, table.concat(out, " ")))
end

-- ------------------------------------------------------------------------------------------------ overlays

function overlayAt(address)
    for _, overlay in pairs(LOADED_OVERLAYS) do
        if overlay.address == address then return overlay.name end
    end
    return nil
end

local function overlayLoadedFor(name)
    for _, o in ipairs(OVERLAYS) do
        if o.name == name then return overlayAt(o.address) == name end
    end
    return false
end

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
  for i, overlay in pairs(LOADED_OVERLAYS) do
    if overlay.address == load_target_overlay.address then
        LOADED_OVERLAYS[i].name = load_target_overlay.name
    end
  end
  print("Loading overlay " .. load_target_overlay.name .. " at address: " .. string.format("0x%x", load_target_overlay.address))
end

-- ------------------------------------------------------------------------------------------------ watches

WATCHES = {}  -- keeps the breakpoint objects alive (a collected breakpoint is removed)

local REGS = {"a0", "a1", "a2", "a3"}

-- spec: addr, name, overlay (optional), arg (register holding the struct pointer, default a0),
--       fields (optional), regs (true: print a0..a3, ra), pause (true: pause the emulator),
--       every (print only every n-th hit, default 1), filter (function(ptr) -> bool, optional)
function watch(spec)
    local hits = 0
    local label = spec.name or string.format("%08x", spec.addr)
    local bp = PCSX.addBreakpoint(spec.addr, "Exec", 4, "watch " .. label, function()
        local ok, err = pcall(function()
            if spec.overlay and not overlayLoadedFor(spec.overlay) then return end
            local r = PCSX.getRegisters().GPR.n
            local p = r[spec.arg or "a0"]
            if spec.filter and not spec.filter(p) then return end
            hits = hits + 1
            if hits % (spec.every or 1) ~= 0 then return end
            local line = label
            if spec.regs ~= false then
                local rs = {}
                for _, n in ipairs(REGS) do rs[#rs + 1] = string.format("%s=%08x", n, r[n]) end
                line = line .. " " .. table.concat(rs, " ") .. string.format(" ra=%08x", r.ra)
            end
            if spec.fields and isRam(p) then
                local fs = {}
                for _, f in ipairs(spec.fields) do fs[#fs + 1] = field(p, f) end
                line = line .. " | " .. table.concat(fs, " ")
            end
            print(line)
            if spec.pause then PCSX.pauseEmulator() end
        end)
        if not ok then print("watch " .. label .. ": " .. tostring(err)) end
    end)
    WATCHES[#WATCHES + 1] = bp
    return bp
end

-- spec: addr, size (bytes, default 4), name, overlay (optional), pause
-- reports the pc of every write and the value before it (the write has not happened yet)
function watchWrite(spec)
    local label = spec.name or string.format("%08x", spec.addr)
    local bp = PCSX.addBreakpoint(spec.addr, "Write", spec.size or 4, "write " .. label, function(address, width)
        local ok, err = pcall(function()
            if spec.overlay and not overlayLoadedFor(spec.overlay) then return end
            local r = PCSX.getRegisters()
            print(string.format("write %s at %08x (%d bytes) from pc=%08x ra=%08x, was %08x",
                label, address or spec.addr, width or 0, r.pc, r.GPR.n.ra, u32(bit.band(address or spec.addr, 0xFFFFFFFC))))
            if spec.pause then PCSX.pauseEmulator() end
        end)
        if not ok then print("watchWrite " .. label .. ": " .. tostring(err)) end
    end)
    WATCHES[#WATCHES + 1] = bp
    return bp
end

function clearWatches()
    for _, bp in ipairs(WATCHES) do bp:remove() end
    WATCHES = {}
end

-- ------------------------------------------------------------------------------------------------ UI

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

bp = PCSX.addBreakpoint(0x80020bf8, "Exec", 4, "Load overlay called", onOverlayLoad)  -- LoadOverlay_80020BF8

-- Examples (paste into the Lua console after loading this file, or put them in your own file that
-- calls Support.extra.dofile on this one):
--
--   -- every call of the stage scenery draw in BATTLE, with the first fields of the struct in a0
--   watch{ addr = 0x800BC90C, overlay = "BATTLE.BIN", every = 60,
--          fields = { {"f0", 0x0, "u32"}, {"f4", 0x4, "s16"}, {"f6", 0x6, "s16"} } }
--
--   -- who writes the word at 0x8008B4D8
--   watchWrite{ addr = 0x8008B4D8, size = 4, name = "display_8008B4D8" }
--
--   dumpStruct(0x8008B4D8, { {"x", 0, "s16"}, {"y", 2, "s16"} })
--   hexdump(0x8008B4D8, 64)
