# Debug features

The retail game still holds some of the developers' tools, with nothing left that reaches them. A build with
the `JC_DEBUG` define hooks them back up. Without it the code is exactly the retail game's (the matching
build never defines it).

| What | Where it is | How to open it |
|---|---|---|
| Sound test | SOUNDTST overlay | title screen, "PRESS START": Start with **L1** held |
| Model viewer | TSTMODEL overlay | title screen: Start with **L2** held (Circle loads the selected model) |
| TSTCOMPO test | TSTCOMPO overlay | title screen: Start with **R2** held |
| Scene select | MAP: `SceneSelect_800B860C` | hold **Select** while the world map opens |
| Chapter select | MAP: `ChapterSelect_800B8B5C` | hold **L1** while the world map opens |

The three test overlays return to the title. The scene select picks a group, then a scene and an entrance
(Up/Down, Cross; Triangle goes back) and loads it. The chapter select sets the chapter and restarts GAME.
The test screens were written for the developers' font and some of their text is missing.

Still unused: `InitDebugSaveData_800A223C` / `GiveDebugStartItems_800A22FC` (TITLE: a save with the
Japanese name and a few items).

## Building

PC: `cmake -S . -B build_dbg -G Ninja -DJC_DEBUG=ON && cmake --build build_dbg`

PlayStation: `JC_DEFINES=JC_DEBUG python build.py` (the hash check then fails, as expected; see
[testing_in_emulator.md](testing_in_emulator.md) for putting the result on a disc image).
