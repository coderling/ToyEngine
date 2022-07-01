#pragma once

namespace Toy::IO
{
enum struct EFileAccess
{
    READ,
    OVERWRITE,
    APPEND
};

enum struct ESeekOrigin
{
    ESEEK_BEGIN = 0,
    ESEEK_CUR = 1,
    ESEEK_END = 2
};
}  // namespace Toy::IO