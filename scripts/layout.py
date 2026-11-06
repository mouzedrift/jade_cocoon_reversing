"""Section layout of the main executable (SLUS_008.54)."""
BASE = 0x80010000
GAME_TEXT_END = 0x8004DDC8
LIB_TEXT_END = 0x80071B0C       # padding up to the first game .rdata follows
RDATA_START = 0x80071B18
RDATA_GAME_END = 0x80074BEC     # PSY-Q .rdata follows (strings of libcd, libgpu, ...)
DATA_START = 0x80075AA0         # Data001Files, first game .data
DATA_GAME_END = 0x80087154      # PSY-Q .data / .sdata follows
DATA_END = 0x8008B450           # .bss starts
SBSS_START = 0x8008B450         # PSY-Q .sbss
BSS_START = 0x8008B484          # = $gp, game .bss
BSS_GAME_END = 0x8009AAE0       # PSY-Q .bss follows (FREE3: _r_bp is the first)
BSS_END = 0x800A05A0
