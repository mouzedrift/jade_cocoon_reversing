project(jade_cocoon_exe VERSION 1.0 LANGUAGES C)

set(SRC_FILES
    main.c
    funcs.c
    globals.h
    globals.c
)

add_executable(jade_cocoon_exe ${SRC_FILES})

set(psyq_4.4 "${CMAKE_CURRENT_SOURCE_DIR}/../libs/psyq_sdk/psyq_4.4")

message("psyq_4.4: ${psyq_4.4}")

target_include_directories(jade_cocoon_exe PUBLIC "${psyq_4.4}/include")
