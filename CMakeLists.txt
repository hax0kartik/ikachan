cmake_minimum_required(VERSION 3.24)
set(CMAKE_TOOLCHAIN_FILE ${CMAKE_SOURCE_DIR}/ARMCC.cmake)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

if(NOT DEFINED ENV{ARMCC_PATH})
    message(FATAL_ERROR "please set ARMCC_PATH")
endif()

if(NOT DEFINED ENV{DEVKITARM})
    message(FATAL_ERROR "please set DEVKITARM")
endif()

find_program(ARM_ASM NAMES armasm.exe PATHS $ENV{ARMCC_PATH}/bin REQUIRED NO_DEFAULT_PATH)
find_program(ARM_AR NAMES armar.exe PATHS $ENV{ARMCC_PATH}/bin REQUIRED NO_DEFAULT_PATH)
find_program(ARM_CC NAMES armcc.exe PATHS $ENV{ARMCC_PATH}/bin REQUIRED NO_DEFAULT_PATH)
find_program(ARM_LINK NAMES armlink.exe PATHS $ENV{ARMCC_PATH}/bin REQUIRED NO_DEFAULT_PATH)
# find_program(ARM_FROMELF NAMES fromelf.exe PATHS $ENV{ARMCC_PATH}/bin REQUIRED NO_DEFAULT_PATH) # not important

add_subdirectory(External/nnsdk)

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

project(ikachan3 C CXX ASM)

if (NOT WIN32)
    set_compilers()
endif()

set(CMAKE_EXECUTABLE_SUFFIX ".axf")

__compiler_armcc(C)
__compiler_armcc(CXX)
__compiler_armcc(ASM)

file(GLOB_RECURSE csourcefiles "Source/*.c" "External/zlib-1.1.4/*.c" "External/libpng/*.c")
file(GLOB_RECURSE cxxsourcefiles "Source/*.cpp")

add_executable(ikachan3 ${csourcefiles} ${cxxsourcefiles})

target_link_options(ikachan3 PUBLIC
    --cpu=MPCore --entry=__ctr_start --startup=__ctr_start --library_type=standardlib
    --ref_cpp_init --scanlib --legacyalign
    --tailreorder --no_remove --datacompressor=off --arm_only
    --inline 
    --verbose --mangled --symbols --paged
    --scatter=${CMAKE_CURRENT_BINARY_DIR}/Linker.ld
    )

target_compile_options(ikachan3 PUBLIC $<$<COMPILE_LANGUAGE:CXX>:
    --apcs=//interwork --cpu=MPCore --fpmode=fast --cpp --arm --force_new_nothrow
    --signed_chars --multibyte-chars --locale=japanese --no_vfe # workaround, vfe should be enabled
    --no_rtti_data --no_rtti --no_exceptions -Otime -O3 --data-reorder --split_sections --forceinline
    >)

target_compile_options(ikachan3 PUBLIC $<$<COMPILE_LANGUAGE:C>:
    --apcs=//interwork --cpu=MPCore --fpmode=fast --c99 --arm
    --signed_chars --multibyte-chars --locale=japanese
    -Otime -O3 --data-reorder --split_sections --diag_suppress=1294
    >)

target_compile_definitions(ikachan3 PUBLIC NON_MATCHING=)

target_include_directories(ikachan3 PUBLIC ${CMAKE_SOURCE_DIR}/include External/libpng External/nnsdk/include External/zlib-1.1.4/)
target_link_libraries(ikachan3 nnsdk)