cmake_minimum_required(VERSION 3.20)
project(set_vs_map)

set(CMAKE_CXX_STANDARD 20)

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup(NO_OUTPUT_DIRS TARGETS)

add_executable(set_vs_map main.cpp)
target_link_libraries(set_vs_map PRIVATE CONAN_PKG::fmt)
