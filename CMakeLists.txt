cmake_minimum_required(VERSION 3.24)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/output)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib) # shared libraries
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib) # static libraries

project(rpc_test)

add_subdirectory(3rdparty)
add_subdirectory(src)
add_subdirectory(test)
add_subdirectory(example)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
