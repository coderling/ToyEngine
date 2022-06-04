#pragma once

#include <format>
#include <iostream>
#include <sstream>
#include <string>

namespace Toy
{
template <typename StreamType, typename ArgsType>
inline void StreamOutput(StreamType& st)
{
}

template <typename StreamType, typename ArgsType>
inline void StreamOutput(StreamType& st, const ArgsType& args)
{
    st << args;
}

template <typename StreamType, typename FArgsType, typename... ArgsType>
void StreamOutput(StreamType& st, const FArgsType f_args, const ArgsType&... args)
{
    StreamOutput(st, f_args);
    StreamOutput(st, args...);
}

template <typename StreamType, typename... ArgsType>
void StreamFormatOutput(StreamType& st, const std::string_view& format, const ArgsType&... args)
{
    auto o = std::vformat(format, std::make_format_args(args...));
    StreamOutput(st, o);
}

template <typename... ArgsType>
void FormatOutput(const std::string_view& format, const ArgsType&... args)
{
    StreamFormatOutput(std::cout, format, args...);
}

template <typename... ArgsType>
std::string FormatString(const std::string_view& format, const ArgsType&... args)
{
    std::stringstream sst;
    StreamFormatOutput(sst, format, args...);
    return sst.str();
}

template <typename... ArgsType>
std::string ConcatString(const ArgsType&... args)
{
    std::stringstream sst;
    StreamOutput(sst, args...);
    return sst.str();
}
}  // namespace Toy