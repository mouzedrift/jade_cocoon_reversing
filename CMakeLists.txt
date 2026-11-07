# PC build with PSY-Z (external/psyz): the executable is the host, every overlay a module it loads in place
# of the overlay file (psyz_add_module). The PlayStation build is build.py; this one does not change it.
#
#   cmake -B build_pc && cmake --build build_pc
cmake_minimum_required(VERSION 3.21..3.31)

project(jade_cocoon LANGUAGES C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_EXTENSIONS ON)

add_subdirectory(external/psyz/psyz psyz EXCLUDE_FROM_ALL)
target_compile_definitions(psyz PRIVATE __psyz)

set(GAME_DEFINES __psyz)
set(GAME_OPTIONS -fno-strict-aliasing -fwrapv -funsigned-char)

# the executable's translation units, config/tus.txt (lines "name address")
file(STRINGS config/tus.txt TU_LINES REGEX "^[a-z0-9_]+ [0-9a-fA-F]+")
set(EXE_SOURCES)
foreach(line ${TU_LINES})
    string(REGEX REPLACE " .*" "" tu "${line}")
    if(EXISTS ${CMAKE_SOURCE_DIR}/src/${tu}.c)  # not the SN start-up object
        list(APPEND EXE_SOURCES src/${tu}.c)
    endif()
endforeach()

add_executable(jade_cocoon ${EXE_SOURCES})
target_include_directories(jade_cocoon PRIVATE src)
target_compile_definitions(jade_cocoon PRIVATE ${GAME_DEFINES})
target_compile_options(jade_cocoon PRIVATE ${GAME_OPTIONS})
target_link_libraries(jade_cocoon PRIVATE psyz)
psyz_exports(jade_cocoon)

# overlays: src/overlays/NAME.c and NAME_2.c, ... (the objects one overlay was linked from)
set(OVERLAYS
    TITLE SOUNDTST TSTMODEL TSTCOMPO GAME COMBAT COMBCOM COMBCHUI COMBSEL COMBLOAD COMBSTRT COMBBTL COMBRSLT
    BATTLE PLCOM ENCOM MAP MENU SHOPCTRL SHOP SHOPENTR WPNSHOP CONFIG LOAD NAME EQUIP CHAPTER PIERCE EVENTFNC)
foreach(ovl ${OVERLAYS})
    string(TOLOWER ${ovl} name)
    file(GLOB sources src/overlays/${name}.c src/overlays/${name}_[0-9].c)
    if(NOT sources)
        continue()
    endif()
    psyz_add_module(${ovl} HOST jade_cocoon SOURCES ${sources})
    target_include_directories(${ovl} PRIVATE src src/overlays external/psyz/psyz/include)
    target_compile_definitions(${ovl} PRIVATE ${GAME_DEFINES})
    target_compile_options(${ovl} PRIVATE ${GAME_OPTIONS})
endforeach()
