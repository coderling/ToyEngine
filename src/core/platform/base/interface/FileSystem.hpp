#pragma once
#include <string>
#include "CommonDefines.hpp"
#include "IODefines.hpp"

namespace Toy::IO
{
class File;

struct FileSystem
{
#ifdef PLATFORM_WINDOWS
    static constexpr const char path_separator = '\\';
#else
    static constexpr const char path_separator = '/';
#endif

    NODISCARD static bool FileExits(const char* path);

    NODISCARD static File Open(const char* path, const EFileAccess& mode);

    static bool DeleteFile(const char* path);

    static bool CreateDirectory(const char* path);

    static bool DeleteDirectory(const char* path);

    NODISCARD static std::string GetExtension(const char* path);

    NODISCARD static bool IsFile(const char* path);

    NODISCARD static std::string GetRelativePath(const char* parent_path, const char* son_path);

    NODISCARD static std::string GetFullPath(const char* path);
};
}  // namespace Toy::IO