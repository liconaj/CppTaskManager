include(CTest)
include(Catch)

add_executable(taskmaster_tests
    sanity_test.cpp
    command_parser_test.cpp
)

target_link_libraries(taskmaster_tests
    PRIVATE
        TaskMaster::Core
        Catch2::Catch2WithMain
)

catch_discover_tests(taskmaster_tests)
