
#ifdef _MSC_VER 

    #define BSS
    #define gap

#else

    #define SECTION(x) __attribute__((section(x)))
    #define BSS SECTION(".bss")
    #define gap char BSS

#endif

// simply add a new var at any random place below the line then run bss.py and it will automatically put it in then
// correct place and re-adjust the gaps, sizes, and byte size comments. the only thing allowed below the line are
// var declarations. put everything else in a header. all comments below the line will also be deleted.
// you must use "BSS" instead of SECTION, and for EVERY var.

// note: if any included headers has an extern to the same vars defined here, matches will fail. never put extern
// data in a header.

// --------------------------------------------------------------------------------------------------------------------

int BSS             dword_8008BD84[93]; // 0x174 (372) bytes

gap                                     gap_8008BEF8[0x59B8]; // 22968 bytes

int BSS             dword_800918B0; // 0x4 (4) bytes
