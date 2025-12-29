#include <catch2/catch_test_macros.hpp>

namespace {
    TEST_CASE("Sanity check", "[sanity]")
    {
        REQUIRE(1 + 1 == 2);
    }
}
