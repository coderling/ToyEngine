# gtest
include(FetchContent)
FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/coderling/googletest.git
    GIT_TAG release-1.11.0
    SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/googletest
)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)