include(FetchContent)

# -----------------------------------------------------------------------------
# Catch2 - Testing Framework

# Only include testing framework if build tests
if(TASKMASTER_BUILD_TESTS)
    FetchContent_Declare(
        Catch2
        GIT_REPOSITORY https://github.com/catchorg/Catch2.git
        GIT_TAG v3.12.0
    )

    set(CATCH_BUILD_TESTING OFF CACHE BOOL "Do not build Catch2 tests" FORCE)
    set(CATCH_INSTALL_DOCS OFF CACHE BOOL "Do not install Catch2 docs" FORCE)
    set(CATCH_INSTALL_EXTRAS ON CACHE BOOL "Install extras for Catch.cmake module" FORCE)

    FetchContent_MakeAvailable(Catch2)

    # Make availabale Catch.cmake module for catch_discover_tests()
    list(APPEND CMAKE_MODULE_PATH ${catch2_SOURCE_DIR}/extras)
endif()
