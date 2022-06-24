#pragma once

namespace Toy::IO
{
struct Path
{
    static bool FileExits(const char* path);
    static void CreateFile(const char* path);
    static void DeleteFile(const char* path);
};
}  // namespace Toy::IO