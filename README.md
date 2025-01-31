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
pip install -r requirements.txt
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

| Overlay | Size | Description |
| ------- | ---- | ----------- |
| BATTLE.BIN | 78 KB | Battle scene |
| BTEND.BIN | 1 KB | Unused? |
| BTLEXEC.BIN | 1 KB | Sometimes loaded after loading `BATTLE.BIN` |
| CHAPTER.BIN | 3 KB | Chapter movies |
| COMBAT.BIN | 15 KB | (Arena Battle Stage) Entry |
| COMBBTL.BIN | 18 KB | (Arena Battle Stage) Battle scene |
| COMBCHUI.BIN | 2 KB | (Arena Battle Stage) Welcome UI |
| COMBCOM.BIN | 15 KB | (Arena Battle Stage) Main selection screen |
| COMBLOAD.BIN | 2 KB | (Arena Battle Stage) Load save |
| COMBRSLT.BIN | 3 KB | (Arena Battle Stage) Battle result screen |
| COMBSEL.BIN | 7 KB | (Arena Battle Stage) Minion selection |
| COMBSTRT.BIN | 4 KB | (Arena Battle Stage) Start fight screen |
| CONFIG.BIN | 12 KB | Options screen |
| ENCOM.BIN | 1 KB | Unused? |
| EQUIP.BIN | 13 KB | Levant equipment handler (Weapon, Armor, Other) |
| EVENTFNC.BIN | 25 KB | Event functions? |
| GAME.BIN | 72 KB | Overworld game logic |
| LOAD.BIN | 32 KB | Save screen for saving and loading saves |
| MAP.BIN | 12 KB | Syrus map |
| MENU.BIN | 49 KB | Levant's menu | 
| NAME.BIN | 6 KB | Player name selection screen |
| PIERCE.BIN | 1 KB | Unused? |
| PLCOM.BIN | 1 KB | Unused? |
| SHOP.BIN | 40 KB | Nagi magic logic despite its name |
| SHOPCTRL.BIN | 2 KB | Nagi magic logic despite its name |
| SHOPENTR.BIN | 5 KB | Unused?
| SOUNDTST.BIN | 40 KB | Sound tester |
| TITLE.BIN | 9 KB | Main menu title screen |
| TSTCOMPO.BIN | 9 KB | Character model tester |
| TSTMODEL.BIN | 14 KB | Minion model tester |
| WPNSHOP.BIN | 35 KB | Despite its name a generic shop handler |

The overlays can be extracted from the DATA.001 archive using [Meos's Unpacker/Repacker](https://github.com/Meos4/Jade-Cocoon-Unpacker-Repacker).

After extracting the game files you'll find the overlays in the `DATA/OVER` directory.
