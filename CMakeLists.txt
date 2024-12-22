cmake_minimum_required(VERSION 3.23)

project(makedown LANGUAGES C)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

add_subdirectory(${CMAKE_SOURCE_DIR}/external/raylib)

add_executable(${PROJECT_NAME}
	src/main.c 
	src/makedown.c
	include/makedown.h)

target_include_directories(${PROJECT_NAME} PRIVATE
    ${CMAKE_SOURCE_DIR}/include
)
target_link_libraries(${PROJECT_NAME} PRIVATE raylib)

target_compile_options(${PROJECT_NAME} PRIVATE
    -fms-extensions
    -fms-compatibility
    $<$<CONFIG:Debug>:/Od>       # Debug: Disable optimizations
    $<$<CONFIG:Release>:/O2>     # Release: Optimize for speed
)
target_compile_definitions(${PROJECT_NAME} PRIVATE
    $<$<CONFIG:Debug>:DEBUG>
    $<$<CONFIG:Release>:NDEBUG>
)
target_link_options(${PROJECT_NAME} PRIVATE
    "/SUBSYSTEM:CONSOLE"
    "/MANIFEST:EMBED"
    "/DEBUG"
)
