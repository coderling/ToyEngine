#pragma once

namespace Toy::IO
{
enum struct EFileAccess
{
    READ,
    OVERWRITE,
    APPEND
};

class TFile
{
    const char* path;

   public:
};
}  // namespace Toy::IO