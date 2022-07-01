#include "FileSystem.hpp"
#include <filesystem>
#include "DebugUtility.hpp"
#include "File.hpp"

namespace Toy::IO
{
static std::error_code err_code;

bool FileSystem::FileExits(const char* path) { return std::filesystem::exists(path); }

File FileSystem::Open(const char* path, const EFileAccess& mode) { return File(path, mode); }

bool FileSystem::DeleteFile(const char* path)
{
    if (!FileExits(path))
        {
            LOG_ERROR("file not exits while try to delete!!!");
            return false;
        }

    bool ret = std::filesystem::remove(path, err_code);
    if (!ret)
        {
            LOG_ERROR("remove file error:", err_code.message());
        }

    return ret;
}

bool FileSystem::CreateDirectory(const char* path) { return std::filesystem::create_directory(path); }

bool FileSystem::DeleteDirectory(const char* path)
{
    if (!FileExits(path))
        {
            LOG_ERROR("directory not exits while try to delete!!!");
            return false;
        }

    auto rm_count = std::filesystem::remove_all(path, err_code);
    if (err_code)
        {
            LOG_ERROR("remove directory error:", err_code.message());
            return false;
        }

    return true;
}

std::string FileSystem::GetExtension(const char* path)
{
    static std::filesystem::path sys_path;
    sys_path.assign(path);
    return sys_path.extension().string();
}

std::string FileSystem::GetRelativePath(const char* base_path, const char* path)
{
    auto ret = std::filesystem::relative(path, base_path, err_code);
    if (err_code)
        {
            LOG_ERROR("relative path error: ", err_code.message());
        }

    return ret.string();
}

std::string FileSystem::GetFullPath(const char* path)
{
    auto full_path = std::filesystem::absolute(path, err_code);
    if (err_code)
        {
            LOG_ERROR("can not get full path: ", err_code.message());
        }

    return full_path.string();
}
}  // namespace Toy::IO
