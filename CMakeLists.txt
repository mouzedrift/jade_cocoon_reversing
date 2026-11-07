# PC build with PSY-Z (external/psyz). The PlayStation build is build.py; this one does not change it.
#
#   cmake -B build_pc -G Ninja && cmake --build build_pc
#
# One binary: the executable's code and every overlay. The executable calls into the overlays and reads their
# data by name (on the PlayStation, at the addresses they load to), so they are linked together. What loading
# an overlay does to its data (fresh .data from the file) is done by src/pc/overlays.c: each overlay's data is in
# sections of its own (jc_NAME_data / jc_NAME_bss, renamed below), saved at start and put back when the game
# loads that overlay.
cmake_minimum_required(VERSION 3.21..3.31)

project(jade_cocoon LANGUAGES C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_EXTENSIONS ON)
set(CMAKE_POSITION_INDEPENDENT_CODE OFF)

add_subdirectory(external/psyz/psyz psyz EXCLUDE_FROM_ALL)
target_compile_definitions(psyz PRIVATE __psyz)

set(GAME_DEFINES __psyz)
set(GAME_OPTIONS -fno-strict-aliasing -fwrapv -funsigned-char -fno-pie -fno-common)

# the executable's translation units, config/tus.txt (lines "name address")
file(STRINGS config/tus.txt TU_LINES REGEX "^[a-z0-9_]+ [0-9a-fA-F]+")
set(EXE_SOURCES)
foreach(line ${TU_LINES})
    string(REGEX REPLACE " .*" "" tu "${line}")
    if(EXISTS ${CMAKE_SOURCE_DIR}/src/${tu}.c)  # not the SN start-up object
        list(APPEND EXE_SOURCES src/${tu}.c)
    endif()
endforeach()
file(GLOB PC_SOURCES src/pc/*.c)

# overlays: src/overlays/NAME.c and NAME_2.c, ... (the objects one overlay was linked from), linked into one
# object each, with its data sections renamed
set(OVERLAYS
    TITLE SOUNDTST TSTMODEL TSTCOMPO GAME COMBAT COMBCOM COMBCHUI COMBSEL COMBLOAD COMBSTRT COMBBTL COMBRSLT
    BATTLE MAP MENU SHOPCTRL SHOP SHOPENTR WPNSHOP CONFIG LOAD NAME EQUIP CHAPTER EVENTFNC) # not PIERCE (unused, linked against an older build)
set(OVERLAY_OBJECTS)
foreach(ovl ${OVERLAYS})
    string(TOLOWER ${ovl} name)
    file(GLOB sources src/overlays/${name}.c src/overlays/${name}_[0-9].c)
    add_library(ovl_${name} OBJECT ${sources})
    target_include_directories(ovl_${name} PRIVATE src src/overlays)
    target_compile_definitions(ovl_${name} PRIVATE ${GAME_DEFINES})
    target_compile_options(ovl_${name} PRIVATE ${GAME_OPTIONS})
    target_link_libraries(ovl_${name} PRIVATE psyz)
    set(out ${CMAKE_CURRENT_BINARY_DIR}/overlay_${name}.o)
    add_custom_command(
        OUTPUT ${out}
        COMMAND ${CMAKE_LINKER} -r -o ${out}.tmp $<TARGET_OBJECTS:ovl_${name}>
        COMMAND ${CMAKE_OBJCOPY} --rename-section .data=jc_${ovl}_data --rename-section .bss=jc_${ovl}_bss
                ${out}.tmp ${out}
        DEPENDS $<TARGET_OBJECTS:ovl_${name}>
        COMMAND_EXPAND_LISTS
        VERBATIM)
    list(APPEND OVERLAY_OBJECTS ${out})
endforeach()

add_executable(jade_cocoon ${EXE_SOURCES} ${PC_SOURCES} ${OVERLAY_OBJECTS})
target_include_directories(jade_cocoon PRIVATE src)
target_compile_definitions(jade_cocoon PRIVATE ${GAME_DEFINES})
target_compile_options(jade_cocoon PRIVATE ${GAME_OPTIONS})
target_link_libraries(jade_cocoon PRIVATE psyz)
target_link_options(jade_cocoon PRIVATE -no-pie)
