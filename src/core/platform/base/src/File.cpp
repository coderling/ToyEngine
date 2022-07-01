#include "File.hpp"
#include "DebugUtility.hpp"
#include "FileSystem.hpp"

namespace Toy::IO
{
File::File(const char* path, const EFileAccess& mode) : file_handle(path, mode) { Open(path, mode); }

File::~File() { Close(); }

bool File::IsExits() const { return FileSystem::FileExits(file_handle.GetPath()); }

void File::Open(const char* path, const EFileAccess& mode) { file_handle.Open(path, mode); }

void File::Close() { file_handle.Close(); }

void File::ReadRaw(void* p_data, const std::size_t& r_size) { file_handle.ReadRaw(p_data, r_size); }

void File::ReadBlob(Engine::IDataBlob* blob)
{
    auto curr = file_handle.GetPosition();
    file_handle.Seek(0, ESeekOrigin::ESEEK_END);
    auto size = file_handle.GetPosition() - curr;
    file_handle.Seek(curr, ESeekOrigin::ESEEK_BEGIN);

    blob->Resize(size);
    ReadRaw(blob->GetDataPointer(), size);
}

std::size_t File::GetLength() const noexcept { return file_handle.GetLength(); }

std::size_t File::GetPosition() const noexcept { return file_handle.GetPosition(); }

void File::WriteRaw(const void* buffer, const std::size_t& w_size)
{
    ENGINE_ASSERT_EXPR(file_handle.GetFileMode() == EFileAccess::OVERWRITE || file_handle.GetFileMode() == EFileAccess::APPEND);
    file_handle.WriteRaw(buffer, w_size);
}

void File::WriteBlob(const Engine::IDataBlob* blob)
{
    ENGINE_ASSERT_EXPR(file_handle.GetFileMode() == EFileAccess::OVERWRITE || file_handle.GetFileMode() == EFileAccess::APPEND);
    WriteRaw(blob->GetDataPointer(), blob->GetDataSize());
}

void File::WriteBlob(const Engine::IDataBlob* blob, const std::size_t& w_size)
{
    ENGINE_ASSERT_EXPR(blob->GetDataSize() >= w_size);
    WriteRaw(blob->GetDataPointer(), w_size);
}

void File::WriteText(const char* text)
{
    auto len = std::strlen(text);
    WriteRaw(reinterpret_cast<const void*>(text), len);
}

std::string File::ReadLine() const { return file_handle.ReadLine(); }

std::string File::ReadToEnd() const { return file_handle.ReadToEnd(); }

void File::Seek(const std::size_t& offset, const ESeekOrigin& orgin) { file_handle.Seek(offset, orgin); }
}  // namespace Toy::IO