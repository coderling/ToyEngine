#pragma once
#include <fstream>
#include "IFileHandle.hpp"

namespace Toy::IO
{
class STDFileHandle : public IFileHandle
{
    const char* file_path;
    EFileAccess file_mode;
    mutable std::fstream fs;

   public:
    STDFileHandle(const char* path, const EFileAccess& mode);

    ~STDFileHandle();

    bool IsOpen() const noexcept override;

    void Open(const char* path, const EFileAccess& mode) override;

    void Close() override;

    void ReadRaw(void* p_data, const std::size_t& r_size) override;

    void Seek(const std::size_t& offset, const ESeekOrigin& orgin) override;

    std::size_t GetLength() const noexcept override;
    std::size_t GetPosition() const noexcept override;

    void WriteRaw(const void* buffer, const std::size_t& w_size) override;

    const char* GetPath() const noexcept override;

    const EFileAccess& GetFileMode() const noexcept override;

    std::string ReadLine() const override;

    std::string ReadToEnd() const override;
};
}  // namespace Toy::IO