#define ENGINE_DEBUG
#include <gtest/gtest.h>
#include <DebugUtility.hpp>
TEST(ASSERT, ASSERT)
{
    // ENGINE_ASSERT_FAILED("啊失败了");
    // ENGINE_ASSERT_EXPR(false);
    // ENGINE_ASSERT(false, "又失败了");
    EXPECT_FALSE(false);
}