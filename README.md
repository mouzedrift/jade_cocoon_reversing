## Contributing
Anyone who likes to contribute to this project is welcome to do so, but keep in mind that, as of the time of writing this, it is a semi-matching project with no way to check if functions still match locally.
Currently I use [decomp.me](https://decomp.me/) for matching game functions. I do have an IDA Pro database I'm working on, so if you're interested, I'd recommend joining. [The Jade Cocoon Project](https://discord.gg/QUMyJmHYnc) Discord server and contacting me there.

## Building

### Prerequisites 
- Python

Clone the repository with the `--recursive` flag:

```
git clone --recursive https://github.com/mouzedrift/jade_cocoon_reversing.git
```

Install python dependencies and build:
```
python -r requirements.txt
python build.py
```

Objects and binaries will be output to the `build_psyq` directory.

## Main Executable

Based on `Jade Cocoon - Story of the Tamamayu (USA)`
| Exe | SHA256 | 
| --- | ------ |
| `SLUS_008.54` | `DF3A49452B17F70C1BC0E7559D851EF5FA6E96F8CBA0B55B242F25D915F8F5A3` |

## Overlays

The game has 31 overlays, which are 509 KB in total. You can find more info about each individual overlay below:

| Overlay | Size |
| ------- | ---- |
| BATTLE.BIN | 78 KB |
| BTEND.BIN | 1 KB |
| BTLEXEC.BIN | 1 KB |
| CHAPTER.BIN | 3 KB |
| COMBAT.BIN |  15 KB |
| COMBBTL.BIN | 18 KB |
| COMBCHUI.BIN | 2 KB |
| COMBCOM.BIN | 15 KB |
| COMBLOAD.BIN | 2 KB |
| COMBRSLT.BIN | 3 KB |
| COMBSEL.BIN | 7 KB |
| COMBSTRT.BIN | 4 KB |
| CONFIG.BIN | 12 KB |
| ENCOM.BIN | 1 KB |
| EQUIP.BIN | 13 KB |
| EVENTFNC.BIN | 25 KB |
| GAME.BIN | 72 KB |
| LOAD.BIN | 32 KB |
| MAP.BIN | 12 KB |
| MENU.BIN | 49 KB |
| NAME.BIN | 6 KB |
| PIERCE.BIN | 1 KB |
| PLCOM.BIN | 1 KB |
| SHOP.BIN | 40 KB |
| SHOPCTRL.BIN | 2 KB |
| SHOPENTR.BIN | 5 KB |
| SOUNDTST.BIN | 40 KB |
| TITLE.BIN | 9 KB |
| TSTCOMPO.BIN | 9 KB |
| TSTMODEL.BIN | 14 KB |
| WPNSHOP.BIN | 35 KB |

The overlays can be extracted from the DATA.001 archive using [Meos's Unpacker/Repacker](https://github.com/Meos4/Jade-Cocoon-Unpacker-Repacker).

After extracting the game files you'll find the overlays in the `Data/OVER` directory.
