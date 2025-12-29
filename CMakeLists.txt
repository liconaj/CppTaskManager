cmake_minimum_required(VERSION 3.16)

project(TaskMaster
    VERSION 0.1.0
    DESCRIPTION "A to do list manager"
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Include scripts in cmake/ folder
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

# Project options
option(TASKMASTER_BUILD_TESTS "Build tests" ON)

# Dependencies
include(Dependencies)

# Source code
add_subdirectory(src)

# Tests
if(TASKMASTER_BUILD_TESTS)
    enable_testing()
    add_subdirectory(tests)
endif()
