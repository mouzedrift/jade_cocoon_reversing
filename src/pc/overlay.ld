/* ld -r script for an overlay: its constant data goes with its data (the game edits strings in place, an overlay
   load gets the originals back), the sections are renamed jc_NAME_data / jc_NAME_bss by objcopy after this */
SECTIONS
{
    .data : { *(.data .data.* .rodata .rodata.*) }
    .bss : { *(.bss .bss.* COMMON) }
}
