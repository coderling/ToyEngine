#pragma once
#include <FormatString.hpp>
#include <iostream>
#include <string>

namespace Toy::Debug
{
enum ELOG_LEVEL
{
    LOG_LV_INFO = 0,
    LOG_LV_WARNING,
    LOG_LV_ERROR,
    LOG_LV_FATAL_ERROR
};

template <bool>
inline void ThrowIf(const std::string &&msg)
{
}

template <>
inline void ThrowIf<true>(const std::string &&msg)
{
    std::runtime_error(std::move(msg));
}

template <bool throwException, typename... ArgsType>
void Log(ELOG_LEVEL level, const char *file, const char *function, const int &line, const ArgsType... args)
{
    std::stringstream sst;
    switch (level)
        {
            case LOG_LV_WARNING:
                sst << "[Warning]>";
                break;
            case LOG_LV_ERROR:
                sst << "[Error]>";
                break;
            case LOG_LV_FATAL_ERROR:
                sst << "[Fatal Error]>";
                break;
            default:
                sst << "[Info]>";
                break;
        }

    sst << "in " << file << " Func:" << function << " Line:" << line << ":";

    const auto &msg = Toy::ConcatString(args...);
    if (level >= LOG_LV_ERROR)
        {
            std::cout << sst.str() << msg << std::endl;
        }
    else
        {
            std::cout << sst.str() << msg << std::endl;
        }

    ThrowIf<throwException>(std::move(msg));
}

template <bool throwException, typename... ArgsType>
void LogFormat(ELOG_LEVEL level, const char *file, const char *function, const int &line, const std::string_view &format,
               const ArgsType &...args)
{
    const auto &msg = Toy::FormatString(format, args...);
    Log<throwException>(level, file, function, line, msg);
}

#define LOG(level, exception, ...)                                                                                                         \
    do                                                                                                                                     \
        {                                                                                                                                  \
            Log<exception>(level, __FILE__, __FUNCTION__, __LINE__, ##__VA_ARGS__);                                                        \
    } while (false)

#define LOG_FORMAT(level, exception, format, ...)                                                                                          \
    do                                                                                                                                     \
        {                                                                                                                                  \
            LogFormat<exception>(level, __FILE__, __FUNCTION__, __LINE__, format, ##__VA_ARGS__);                                          \
    } while (false)

#define LOG_INFO(...)                                                                                                                      \
    do                                                                                                                                     \
        {                                                                                                                                  \
            LOG(Toy::Debug::LOG_LV_INFO, false, ##__VA_ARGS__);                                                                            \
    } while (false)

#define LOG_INFO_FORMAT(format, ...)                                                                                                       \
    do                                                                                                                                     \
        {                                                                                                                                  \
            LOG_FORMAT(Toy::Debug::LOG_LV_INFO, false, format, ##__VA_ARGS__);                                                             \
    } while (false)

#define LOG_WARNING(...)                                                                                                                   \
    do                                                                                                                                     \
        {                                                                                                                                  \
            LOG(Toy::Debug::LOG_LV_WARNING, false, ##__VA_ARGS__);                                                                         \
    } while (false)

#define LOG_WARNING_FORMAT(format, ...)                                                                                                    \
    do                                                                                                                                     \
        {                                                                                                                                  \
            LOG_FORMAT(Toy::Debug::LOG_LV_WARNING, false, format, ##__VA_ARGS__);                                                          \
    } while (false)

#define LOG_ERROR(...)                                                                                                                     \
    do                                                                                                                                     \
        {                                                                                                                                  \
            LOG(Toy::Debug::LOG_LV_ERROR, false, ##__VA_ARGS__);                                                                           \
    } while (false)

#define LOG_ERROR_EXCEPTION(...)                                                                                                           \
    do                                                                                                                                     \
        {                                                                                                                                  \
            LOG(Toy::Debug::LOG_LV_ERROR, true, ##__VA_ARGS__);                                                                            \
    } while (false)

#define LOG_ERROR_FORMAT(format, ...)                                                                                                      \
    do                                                                                                                                     \
        {                                                                                                                                  \
            LOG_FORMAT(Toy::Debug::LOG_LV_ERROR, false, format, ##__VA_ARGS__);                                                            \
    } while (false)

#define LOG_ERROR_EXCEPTION_FORMAT(format, ...)                                                                                            \
    do                                                                                                                                     \
        {                                                                                                                                  \
            LOG_FORMAT(Toy::Debug::LOG_LV_ERROR, true, format, ##__VA_ARGS__);                                                             \
    } while (false)

#define LOG_FATAL_ERROR(...)                                                                                                               \
    do                                                                                                                                     \
        {                                                                                                                                  \
            LOG(Toy::Debug::LOG_LV_FATAL_ERROR, false, ##__VA_ARGS__);                                                                     \
    } while (false)

#define LOG_FATAL_ERROR_EXCEPTION(...)                                                                                                     \
    do                                                                                                                                     \
        {                                                                                                                                  \
            LOG(Toy::Debug::LOG_LV_FATAL_ERROR, true, ##__VA_ARGS__);                                                                      \
    } while (false)

#define LOG_FATAL_ERROR_FORMAT(format, ...)                                                                                                \
    do                                                                                                                                     \
        {                                                                                                                                  \
            LOG_FORMAT(Toy::Debug::LOG_LV_FATAL_ERROR, false, format, ##__VA_ARGS__);                                                      \
    } while (false)

#define LOG_FATAL_ERROR_EXCEPTION_FORMAT(format, ...)                                                                                      \
    do                                                                                                                                     \
        {                                                                                                                                  \
            LOG_FORMAT(Toy::Debug::LOG_LV_FATAL_ERROR, true, format, ##__VA_ARGS__);                                                       \
    } while (false)
}  // namespace Toy::Debug