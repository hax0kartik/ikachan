cmake_minimum_required(VERSION 3.24)

include(${CMAKE_SOURCE_DIR}/project/tc.cmake)
set_toolchain()

project(ikachan3 C CXX ASM)

include(${CMAKE_SOURCE_DIR}/project/ARMCC.cmake)
__compiler_armcc(C)
__compiler_armcc(CXX)
__compiler_armcc(ASM)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

set(THIRDPARTY_C_FLAGS --apcs=//interwork --cpu=MPCore --fpmode=fast --c99 --arm
    --signed_chars --multibyte-chars --locale=japanese -Otime -O3 --data-reorder --split_sections
    --diag_suppress=1294)

file(GLOB ZLIB_SOURCES   ${CMAKE_SOURCE_DIR}/External/zlib-1.1.4/*.c)
file(GLOB LIBPNG_SOURCES ${CMAKE_SOURCE_DIR}/External/libpng/*.c)

add_library(thirdparty OBJECT ${ZLIB_SOURCES} ${LIBPNG_SOURCES})
target_compile_options(thirdparty PRIVATE ${THIRDPARTY_C_FLAGS})
target_compile_definitions(thirdparty PRIVATE NON_MATCHING= PNG_NO_WRITE_sRGB=1 PNG_WRITE_TRANSFORMS_NOT_SUPPORTED=1)
target_include_directories(thirdparty PUBLIC
    ${CMAKE_SOURCE_DIR}/External/zlib-1.1.4
    ${CMAKE_SOURCE_DIR}/External/libpng)

set(ONLY_MATCHING ON)
include(${CMAKE_SOURCE_DIR}/project/global.cmake)
# The original is a release build: no asserts / debug prints inside the SDK.
set(NN_BUILD_RELEASE ON)
add_subdirectory(External/CTR_SDK)

file(GLOB_RECURSE IKACHAN_SOURCES
    ${CMAKE_SOURCE_DIR}/Source/*.c
    ${CMAKE_SOURCE_DIR}/Source/*.cpp)

add_executable(ikachan3 ${IKACHAN_SOURCES} $<TARGET_OBJECTS:thirdparty>)
target_compile_definitions(ikachan3 PRIVATE NON_MATCHING=)
target_include_directories(ikachan3 PRIVATE ${CMAKE_SOURCE_DIR}/Include)
target_compile_options(ikachan3 PRIVATE $<$<COMPILE_LANGUAGE:CXX>:--forceinline --no_rtti --no_rtti_data --force_new_nothrow>)
target_link_libraries(ikachan3 PRIVATE CTR_SDK)
target_include_directories(ikachan3 PRIVATE ${CMAKE_SOURCE_DIR}/External/zlib-1.1.4 ${CMAKE_SOURCE_DIR}/External/libpng)

# build.py writes Linker.ld into the build directory before configuring.
target_link_options(ikachan3 PRIVATE
    --entry=__ctr_start --startup=__ctr_start
    --library_type=standardlib --ref_cpp_init --scanlib --legacyalign
    --tailreorder --datacompressor=off --arm_only --inline
    # Equivalent of --no_remove (keep every section so unreferenced decomp'd code stays in the
    # image), but --no_remove together with --tailreorder hits an armlink internal fault when
    # members are pulled from the SDK/thirdparty archives.
    "--keep=*(*)"
    --verbose --mangled --symbols --paged
    --scatter=${CMAKE_BINARY_DIR}/Linker.ld)
set_target_properties(ikachan3 PROPERTIES SUFFIX ".axf" LINK_DEPENDS ${CMAKE_BINARY_DIR}/Linker.ld)
