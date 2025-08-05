#ui-lib
file(GLOB_RECURSE CORE_SOURCES CONFIGURE_DEPENDS
    ${CMAKE_CURRENT_SOURCE_DIR}/src/*.c
)

add_library(bitsweeper-ui STATIC
    ${CORE_SOURCES}
)

target_link_libraries(bitsweeper-ui PRIVATE
	raylib
	bitsweeper-core
)
 
target_include_directories(bitsweeper-ui PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/src
)

file(GLOB_RECURSE INCLUDE_DIRS LIST_DIRECTORIES true "${CMAKE_CURRENT_SOURCE_DIR}/src/*")

foreach(dir ${INCLUDE_DIRS})
	if(IS_DIRECTORY ${dir})
		target_include_directories(bitsweeper-ui PUBLIC ${dir})
	endif()
endforeach()

#game
add_executable(bitsweeper-game
	${CMAKE_CURRENT_SOURCE_DIR}/src/main.c
)

target_link_libraries(bitsweeper-game PRIVATE
	bitsweeper-ui
	bitsweeper-core
	raylib
)

#ui-tests
add_subdirectory(test)