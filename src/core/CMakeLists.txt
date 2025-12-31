add_library(taskmaster_core STATIC
    command.h
    parse_error.h
    command_parser.h
    command_parser.cpp
)

add_library(TaskMaster::Core ALIAS taskmaster_core)

target_include_directories(taskmaster_core
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
)

target_compile_features(taskmaster_core PUBLIC cxx_std_17)
