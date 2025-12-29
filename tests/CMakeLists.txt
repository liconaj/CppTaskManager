include(CTest)
include(Catch)

add_executable(taskmaster_tests "tests.cpp")

target_link_libraries(taskmaster_tests
    PRIVATE
        Catch2::Catch2WithMain
)

catch_discover_tests(taskmaster_tests)
