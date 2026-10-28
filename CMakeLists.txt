cmake_minimum_required(VERSION 3.20)

project(StaticRingBuffer CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# ADD LIBRARY

add_library(ring_buffer_lib INTERFACE)
target_include_directories(ring_buffer_lib INTERFACE 
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)
target_compile_features(ring_buffer_lib INTERFACE cxx_std_20)
target_compile_options(ring_buffer_lib INTERFACE
    $<$<OR:$<CXX_COMPILER_ID:GNU>,$<CXX_COMPILER_ID:Clang>,$<CXX_COMPILER_ID:AppleClang>>:
        -Wall -Wextra -Wpedantic -Wconversion -Wshadow -fdiagnostics-color=always
    >
    $<$<CXX_COMPILER_ID:MSVC>:
        /W4 /permissive-
    >
)

# ADD SUBDIRECTORY

# ADD TEST
enable_testing()
add_subdirectory(tests)