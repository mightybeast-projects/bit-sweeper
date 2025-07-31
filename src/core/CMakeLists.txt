file(GLOB_RECURSE CORE_SOURCES CONFIGURE_DEPENDS
    ${CMAKE_CURRENT_SOURCE_DIR}/src/*.c
)

add_library(bitsweeper-core STATIC
    ${CORE_SOURCES}
)

target_include_directories(bitsweeper-core PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/src
)

add_subdirectory(test)