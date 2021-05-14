cmake_minimum_required(VERSION 3.5)

option(FIBER_EV "Use libev" OFF)
option(FIBER_FAST_SWITCHING "Use libev" ON)
option(USE_VALGRIND "Use valgring" OFF)
set(STACK_STRATEGY "split" CACHE STRING "Stack strategy (split, mmap, malloc)")

option(BUILD_TEST "Build tests" ON)

include (CheckFunctionExists)
include (CheckIncludeFiles)
include (CheckSymbolExists)

project (libfiber)

#include (CPM.cmake)

include_directories (include)

include_directories (../libconcurrent/include)

set(REQURED_LIBS)

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O0")
  set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -O0")
  add_definitions(-DDEBUG)
endif(CMAKE_BUILD_TYPE STREQUAL "Debug")

add_definitions(-D_REENTRANT)

if (CMAKE_COMPILER_IS_GNUCC AND CMAKE_CXX_COMPILER_VERSION VERSION_LESS 4.6)
    set(STACK_STRATEGY "")
endif()

if (STACK_STRATEGY STREQUAL "split")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fsplit-stack")
    add_definitions(-DFIBER_STACK_SPLIT)
elseif (STACK_STRATEGY STREQUAL "mmap")
    add_definitions(-DFIBER_STACK_MMAP)
elseif (STACK_STRATEGY STREQUAL "malloc")
    add_definitions(-DFIBER_STACK_MALLOC)
else()
    message(FATAL_ERROR "Unknown STACK_STRATEGY ${STACK_STRATEGY}")
endif()

if (USE_VALGRIND)
    add_definitions(-DUSE_VALGRIND=1)
endif(USE_VALGRIND)

if (CMAKE_SYSTEM_NAME MATCHES "Darwin")
    add_definitions(-DMACOS)
    set(CMAKE_MODULE_LINKER_FLAGS "${CMAKE_MODULE_LINKER_FLAGS} -read_only_relocs suppress")
    set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} -read_only_relocs suppress")
    set(CMAKE_STATIC_LINKER_FLAGS "${CMAKE_STATIC_LINKER_FLAGS} -read_only_relocs suppress")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -read_only_relocs suppress")
elseif (CMAKE_SYSTEM_NAME MATCHES "Linux")
    add_definitions(-DLINUX)
    #set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -Wl,--no-as-needed")
    list(APPEND REQUIRED_LIBS "dl" "m" "rt")
elseif (CMAKE_SYSTEM_NAME MATCHES "(SunOS|Solaris)")
    add_definitions(-DSOLARIS)
    list(APPEND REQUIRED_LIBS "rt" "socket")
endif()

if (FIBER_FAST_SWITCHING)
    add_definitions(-DFIBER_FAST_SWITCHING)
endif()

set (CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set (CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set (CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

#CPMAddPackage(
#    GITHUB_REPOSITORY msaf1980/libfibconcurrent
#    VERSION 0.1.1
#    OPTIONS "BUILD_TEST OFF"
#)

add_subdirectory (src)

if (BUILD_TEST)
    include(CTest)
    add_subdirectory(test)
endif() # END TEST
