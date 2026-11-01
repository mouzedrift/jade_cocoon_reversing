# Prints, for every function in the game code area, the rodata / data / bss addresses it
# references through lui+load/store pairs. Data of one translation unit is laid out
# contiguously and in link order, so a function's references tell you which TU it is in.
# usage: python3 scripts/tu_hints.py SLUS_008.54 > tu_hints.txt  (run from the repo root)
import re,struct,bisect,sys
exe=open(sys.argv[1],'rb').read()[0x800:]
syms=[]
for l in open('symbol_addrs.txt'):
    m=re.match(r'(\w+)=0x([0-9a-fA-F]+);',l)
    if m: syms.append((int(m.group(2),16),m.group(1)))
syms.sort()
funcs=[(a,n) for a,n in syms if 0x80010000<=a<0x80044000 and n.startswith(('sub_','nullsub'))or (0x80010000<=a<0x80044000 and not re.match(r'(dword|byte|word|stru|a[A-Z_]|off|unk|jpt|loc|flt|dbl|[a-z]+_[0-9A-F]{8}$)',n) and not n.isupper())]
fa=[a for a,n in funcs]
GP=0x8008B484
cur=None; lui={}
info={}
for pc in range(0x80010000,0x80044000,4):
    w=struct.unpack('<I',exe[pc-0x80010000:][:4])[0]
    if pc in fa: lui={}
    op=w>>26; rs=(w>>21)&31; rt=(w>>16)&31; imm=w&0xffff
    s=imm-0x10000 if imm>=0x8000 else imm
    i=bisect.bisect_right(fa,pc)-1
    f=funcs[i][1]; d=info.setdefault(f,{'ro':[],'data':[],'gp':[],'bss':[]})
    if op==15: lui[rt]=imm<<16; continue
    if op in (9,35,36,32,33,37,43,40,41,34,38):
        if rs in lui:
            a=lui[rs]+s
            if 0x80070000<=a<0x80075600: d['ro'].append(a)
            elif 0x80075600<=a<0x8008B000: d['data'].append(a)
            elif a>=0x8008B000: d['bss'].append(a)
        elif rs==28: d['gp'].append(GP+s)
    # clear lui reg on write
    if op==0:
        rd=(w>>11)&31
        lui.pop(rd,None)
    elif op not in (43,40,41,42,46,4,5,6,7,1,2,3): lui.pop(rt,None) if not (op==9 and rs==rt and rs in lui and False) else None
for a,n in funcs:
    d=info[n]
    def r(x): return f"{hex(min(x))[2:]}-{hex(max(x))[2:]}" if x else '-'
    print(hex(a),n[:34].ljust(34),'ro',r(d['ro']).ljust(15),'data',r(d['data']).ljust(15),'gp',r(d['gp']).ljust(15),'bss',r(d['bss']))
