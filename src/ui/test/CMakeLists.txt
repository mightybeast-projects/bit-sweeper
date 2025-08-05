cmake_minimum_required(VERSION 3.12)

file(GLOB_RECURSE SOURCE_FILES CONFIGURE_DEPENDS
    src/*.tests.c
) 
 
add_executable(bitsweeper-ui-tests ${SOURCE_FILES})

target_link_libraries(bitsweeper-ui-tests PRIVATE
    bitsweeper-ui
    unity
)

file(GLOB_RECURSE INCLUDE_DIRS LIST_DIRECTORIES true "${CMAKE_CURRENT_SOURCE_DIR}/src/*")

foreach(dir ${INCLUDE_DIRS})
	if(IS_DIRECTORY ${dir})
		target_include_directories(bitsweeper-ui-tests PUBLIC ${dir})
	endif()
endforeach()