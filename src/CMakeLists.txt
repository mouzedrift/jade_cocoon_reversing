project(jade_cocoon_exe VERSION 1.0 LANGUAGES C)

set(SRC_FILES
    main.c
    funcs.h
    funcs.c
    globals.h
    globals.c
    enums.h
    common.h
)

add_executable(jade_cocoon_exe ${SRC_FILES})

set(psyq4.4 "${CMAKE_CURRENT_SOURCE_DIR}/../libs/psyq4.4")

message("psyq4.4: ${psyq4.4}")

target_include_directories(jade_cocoon_exe PUBLIC "${psyq4.4}/INCLUDE")
