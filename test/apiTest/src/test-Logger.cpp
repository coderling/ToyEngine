#include <gtest/gtest.h>
#include <Logger.hpp>

TEST(Logger, Info)
{
    LOG_INFO("Info loag", 1, 2, 3.0);
    LOG_INFO_FORMAT("{} + {} = {}", 1, 1, 2.0);
    LOG_WARNING("Info loag", 1, 2, 3.0);
    LOG_WARNING_FORMAT("{} + {} = {}", 1, 1, 2.0);
    LOG_ERROR("Info loag", 1, 2, 3.0);
    LOG_ERROR_FORMAT("{} + {} = {}", 1, 1, 2.0);
    LOG_FATAL_ERROR("Info loag", 1, 2, 3.0);
    LOG_FATAL_ERROR_FORMAT("{} + {} = {}", 1, 1, 2.0);
    LOG_ERROR_EXCEPTION("{} + {} = {}", 1, 1, 2.0);
    LOG_ERROR_EXCEPTION_FORMAT("{} + {} = {}", 1, 1, 2.0);
    LOG_FATAL_ERROR_FORMAT("{} + {} = {}", 1, 1, 2.0);
    LOG_FATAL_ERROR_EXCEPTION_FORMAT("{} + {} = {}", 1, 1, 2.0);
    EXPECT_TRUE(true);
}