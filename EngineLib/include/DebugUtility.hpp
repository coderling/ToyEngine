#pragma

#include <FormatString.hpp>
#include <Logger.hpp>
#include <cassert>
#include <iostream>

namespace Toy::Debug
{
#ifdef ENGINE_DEBUG
#define ENGINE_ASSERT_ABORT abort();
#else
#define ENGINE_ASSERT_ABORT abort();
#endif

#define ENGINE_CHECK_OUTPUT(tag, msg, ...)                                                                                                 \
    do                                                                                                                                     \
        {                                                                                                                                  \
            const auto amsg = Toy::ConcatString(msg, ##__VA_ARGS__);                                                                       \
            LOG_ERROR(tag, amsg);                                                                                                          \
    } while (false)

#ifdef ENGINE_DEBUG
#define ENGINE_ASSERT_FAILED(msg, ...)                                                                                                     \
    do                                                                                                                                     \
        {                                                                                                                                  \
            ENGINE_CHECK_OUTPUT("[Assert Fail]>", msg, ##__VA_ARGS__);                                                                     \
            abort();                                                                                                                       \
    } while (false)

#define ENGINE_ASSERT(expr, msg, ...)                                                                                                      \
    do                                                                                                                                     \
        {                                                                                                                                  \
            if (!(expr))                                                                                                                   \
                {                                                                                                                          \
                    ENGINE_ASSERT_FAILED(msg, ##__VA_ARGS__);                                                                              \
                }                                                                                                                          \
    } while (false)

#define ENGINE_ASSERT_EXPR(expr, ...)                                                                                                      \
    do                                                                                                                                     \
        {                                                                                                                                  \
            ENGINE_ASSERT(expr, "check expr:", #expr, " failed ", ##__VA_ARGS__);                                                          \
    } while (false)

#else
#define ENGINE_ASSERT_FAILED(msg, ...)                                                                                                     \
    do                                                                                                                                     \
        {                                                                                                                                  \
    } while (false)
#define ENGINE_ASSERT_EXPR(expr, msg, ...)                                                                                                 \
    do                                                                                                                                     \
        {                                                                                                                                  \
    } while (false)
#define ENGINE_ASSERT(expr)                                                                                                                \
    do                                                                                                                                     \
        {                                                                                                                                  \
    } while (false)
#endif  // ENGINE_DEBUG

#ifdef ENGINE_DEBUG
#define ENGINE_DEV_CHECK_EXPR_ ENGINE_ASSERT_EXPR
#elifdef ENGINE_DEVELOPMENT
#define ENGINE_DEV_CHECK_EXPR(expr, ...)                                                                                                   \
    do                                                                                                                                     \
        {                                                                                                                                  \
            if (!(expr))                                                                                                                   \
                {                                                                                                                          \
                    ENGINE_ASSERT(expr, "check exppr:#expr failed", ##__VA_ARGS__);                                                        \
                }                                                                                                                          \
    } while (false)
#endif

}  // namespace Toy::Debug