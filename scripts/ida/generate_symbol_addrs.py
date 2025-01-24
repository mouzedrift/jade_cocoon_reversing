import idc
import idautils
import os
import ida_bytes

CURRENT_DIRECTORY = os.path.dirname(os.path.abspath(__file__))

symbols = list()

# get functions
for segment in idautils.Segments():
    for ea in idautils.Functions(segment, idc.get_segm_end(segment)):
        func_name = idc.get_func_name(ea)
        if func_name != "":
            symbols.append(f"{func_name}={hex(ea)};")

# get variables
for segment in idautils.Segments():
    for head in idautils.Heads(segment, idc.get_segm_end(segment)):
        is_data = idc.is_data(idc.get_full_flags(head))
        name = idc.get_name(head)
        if is_data and name != "" and not name.startswith("loc_") and not name.startswith("def_") and not name.startswith("jpt_"):
            symbols.append(f"{name}={hex(head)}; // size:{hex(ida_bytes.get_item_size(head))}")

outpath = f"{CURRENT_DIRECTORY}/../../symbol_addrs.txt"
with open(outpath, "w") as file:
    for symbol in symbols:
        file.write(f"{symbol}\n")

print(f"added {len(symbols)} symbols")
print(f"file written to {outpath}")