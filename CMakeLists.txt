cmake_minimum_required(VERSION 3.28)

set(CMAKE_C_COMPILER "clang-18")
set(CMAKE_CXX_COMPILER "clang++-18")
project(llvm_obf LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Automatically look for LLVM 18
find_package(LLVM REQUIRED CONFIG HINTS "/usr/lib/llvm-18/lib/cmake/llvm")
if(NOT "${LLVM_VERSION_MAJOR}" VERSION_EQUAL "18")
    message(FATAL_ERROR "Expected LLVM 18, but found ${LLVM_PACKAGE_VERSION}")
endif()
message(STATUS "Found LLVM ${LLVM_PACKAGE_VERSION} in ${LLVM_INSTALL_PREFIX}")

include_directories(SYSTEM ${LLVM_INCLUDE_DIRS})
separate_arguments(LLVM_DEFINITIONS_LIST NATIVE_COMMAND ${LLVM_DEFINITIONS})
add_definitions(${LLVM_DEFINITIONS_LIST})

add_library(mba_pass MODULE src/mba_pass.cpp)  # Build shared library for pass plugin
target_compile_options(mba_pass PRIVATE -fno-rtti -Wall -Wextra)
set_target_properties(mba_pass PROPERTIES PREFIX "")  # Disable "lib" prefix

if(CMAKE_EXPORT_COMPILE_COMMANDS)
    file(CREATE_LINK "${CMAKE_BINARY_DIR}/compile_commands.json"
                     "${CMAKE_SOURCE_DIR}/compile_commands.json" SYMBOLIC)
endif()
