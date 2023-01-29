cmake_minimum_required(VERSION 3.24)
set(CMAKE_TOOLCHAIN_FILE ${CMAKE_SOURCE_DIR}/ARMCC.cmake)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

if(NOT DEFINED ENV{ARMCC_PATH})
    message(FATAL_ERROR "please set ARMCC_PATH")
endif()

find_program(ARM_ASM NAMES armasm.exe PATHS $ENV{ARMCC_PATH}/bin REQUIRED NO_DEFAULT_PATH)
find_program(ARM_AR NAMES armar.exe PATHS $ENV{ARMCC_PATH}/bin REQUIRED NO_DEFAULT_PATH)
find_program(ARM_CC NAMES armcc.exe PATHS $ENV{ARMCC_PATH}/bin REQUIRED NO_DEFAULT_PATH)
find_program(ARM_LINK NAMES armlink.exe PATHS $ENV{ARMCC_PATH}/bin REQUIRED NO_DEFAULT_PATH)
# find_program(ARM_FROMELF NAMES fromelf.exe PATHS $ENV{ARMCC_PATH}/bin REQUIRED NO_DEFAULT_PATH) # not important

macro (set_compilers)
    set(CMAKE_CXX_COMPILER_ID ARMCC)

    set(CMAKE_AR ${ARM_AR})
    set(CMAKE_C_COMPILER ${ARM_CC})
    set(CMAKE_CXX_COMPILER ${ARM_CC})
    set(CMAKE_ASM_COMPILER ${ARM_ASM})
    set(CMAKE_LINKER ${ARM_LINK})
endmacro()

if (WIN32)
    set_compilers()
    set(CMAKE_C_COMPILER_WORKS TRUE)
    set(CMAKE_CXX_COMPILER_WORKS TRUE)
    set(CMAKE_ASM_COMPILER_WORKS TRUE)
endif()

project(libpng C CXX)

if (NOT WIN32)
    set_compilers()
endif()

__compiler_armcc(C)
__compiler_armcc(CXX)

file(GLOB_RECURSE csourcefiles "*.c")

add_library(libpng ${csourcefiles} ${cxxsourcefiles})

target_compile_options(libpng PUBLIC $<$<COMPILE_LANGUAGE:CXX>:
    --apcs=//interwork --cpu=MPCore --fpmode=fast --cpp --arm --force_new_nothrow
    --signed_chars --multibyte-chars --locale=japanese --no_vfe # workaround, vfe should be enabled
    --no_rtti_data --no_rtti --no_exceptions -O3 -Otime --data-reorder --split_sections --forceinline
    >)

target_compile_options(libpng PUBLIC $<$<COMPILE_LANGUAGE:C>:
    --apcs=//interwork --cpu=MPCore --fpmode=fast --c90 --dollar --diag_style=ide --arm
    --signed_chars --multibyte-chars --locale=japanese
    -O1 --split_sections
    >)

target_compile_definitions(libpng PUBLIC)

target_include_directories(libpng PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})