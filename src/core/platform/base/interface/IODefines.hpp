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
    ESEEK_BEGIN,
    ESEEK_CUR,
    ESEEK_END
};
}  // namespace Toy::IO