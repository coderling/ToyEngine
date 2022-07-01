#include "STDFileHandle.hpp"
#include "DebugUtility.hpp"

namespace Toy::IO
{
STDFileHandle::STDFileHandle(const char *path, const EFileAccess &mode) : file_path(path), file_mode(mode) { Open(path, mode); }

STDFileHandle::~STDFileHandle() { Close(); }

bool STDFileHandle::IsOpen() const noexcept { return fs.is_open(); }

void STDFileHandle::Open(const char *path, const EFileAccess &mode)
{
    Close();

    int open_mode = std::ios::binary;
    switch (mode)
        {
            case EFileAccess::OVERWRITE:
                open_mode = open_mode | std::ios::trunc | std::ios::out;
                break;
            case EFileAccess::APPEND:
                open_mode = open_mode | std::ios::ate | std::ios::out;
                break;
            case EFileAccess::READ:
                open_mode = open_mode | std::ios::in;
                break;
            default:
                break;
        }
    fs.open(file_path, open_mode);
}

void STDFileHandle::Close()
{
    if (IsOpen())
        {
            fs.close();
        }
}

void STDFileHandle::ReadRaw(void *p_data, const std::size_t &r_size)
{
    ENGINE_ASSERT_EXPR(this->IsOpen());
    fs.read(reinterpret_cast<char *>(p_data), r_size);
}

void STDFileHandle::Seek(const std::size_t &offset, const ESeekOrigin &orgin)
{
    ENGINE_ASSERT_EXPR(this->IsOpen());
    auto seek_dir = std::ios::beg;
    switch (orgin)
        {
            case ESeekOrigin::ESEEK_BEGIN:
                seek_dir = std::ios::beg;
                break;
            case ESeekOrigin::ESEEK_CUR:
                seek_dir = std::ios::cur;
                break;
            case ESeekOrigin::ESEEK_END:
                seek_dir = std::ios::end;
                break;
        }

    fs.seekg(offset, seek_dir);
}

std::size_t STDFileHandle::GetLength() const noexcept
{
    ENGINE_ASSERT_EXPR(this->IsOpen());
    auto curr = fs.tellg();
    fs.seekg(0, std::ios::end);

    auto size = fs.tellg();
    fs.seekg(curr, std::ios::beg);
    return size;
}

std::size_t STDFileHandle::GetPosition() const noexcept
{
    ENGINE_ASSERT_EXPR(this->IsOpen());

    return fs.tellg();
}

void STDFileHandle::WriteRaw(const void *buffer, const std::size_t &w_size)
{
    ENGINE_ASSERT_EXPR(this->IsOpen());
    fs.write(reinterpret_cast<const char *>(buffer), w_size);
}

const char *STDFileHandle::GetPath() const noexcept { return file_path; }

const EFileAccess &STDFileHandle::GetFileMode() const noexcept { return file_mode; }

std::string STDFileHandle::ReadLine() const
{
    std::string line;
    std::getline(fs, line);
    return line;
}

std::string STDFileHandle::ReadToEnd() const
{
    std::string content;
    content.assign(std::istreambuf_iterator<char>(fs), std::istreambuf_iterator<char>());
    return content;
}

}  // namespace Toy::IO