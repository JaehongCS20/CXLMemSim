cmake_minimum_required(VERSION 3.11.0)
project(CXLMemSim VERSION 0.1.0)
set(CMAKE_CXX_STANDARD 23)

if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
    add_compile_options (-fdiagnostics-color=always)
elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
    add_compile_options (-fcolor-diagnostics)
endif ()

set(PKG_CONFIG_USE_CMAKE_PREFIX_PATH TRUE)
list(APPEND CMAKE_PREFIX_PATH ${CMAKE_BINARY_DIR})

# Find libelf package
find_package(PkgConfig REQUIRED)
pkg_check_modules(LIBELF REQUIRED libelf)
include_directories(${LIBELF_INCLUDE_DIRS})
link_directories(${LIBELF_LIBRARY_DIRS})

# Find libbpf package
pkg_check_modules(LIBBPF REQUIRED libbpf)
include_directories(${LIBBPF_INCLUDE_DIRS})
link_directories(${LIBBPF_LIBRARY_DIRS})

find_package(cxxopts REQUIRED)
find_package(fmt REQUIRED)
file(GLOB_RECURSE SOURCE_FILES src/*.cpp)

execute_process(COMMAND uname -r OUTPUT_VARIABLE arch OUTPUT_STRIP_TRAILING_WHITESPACE)
set(CMAKE_CXX_FLAGS "-Wall -fPIC -pthread -ldl -lrt -mavx512f -mpreferred-stack-boundary=4 -g -O0")

add_executable(CXLMemSim ${SOURCE_FILES} src/main.cc)

include_directories(CXLMemSim include ${cxxopts_INCLUDE_DIR} ${fmt_INCLUDE_DIR})
target_link_libraries(CXLMemSim fmt::fmt cxxopts::cxxopts ${LIBELF_LIBRARIES} ${LIBBPF_LIBRARIES})

add_library(CXLMemSimHook SHARED src/module.cc)
add_executable(CXLMemSimSock ${SOURCE_FILES} src/sock.cc)
target_link_libraries(CXLMemSimSock fmt::fmt cxxopts::cxxopts ${LIBELF_LIBRARIES} ${LIBBPF_LIBRARIES})
