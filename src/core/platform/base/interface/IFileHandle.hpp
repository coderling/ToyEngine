#pragma once
#include <string>
#include "IDataBlob.hpp"
#include "IODefines.hpp"

namespace Toy::IO
{
class IFileHandle
{
   public:
    IFileHandle() = default;
    NOCOPY_AND_NOMOVE(IFileHandle);

    virtual ~IFileHandle() {}

    virtual bool IsOpen() const noexcept = 0;

    virtual void Open(const char* path, const EFileAccess& mode) = 0;

    virtual void Close() = 0;

    virtual void ReadRaw(void* p_data, const std::size_t& r_size) = 0;

    virtual void Seek(const std::size_t& offset, const ESeekOrigin& orgin) = 0;

    virtual std::size_t GetLength() const noexcept = 0;
    virtual std::size_t GetPosition() const noexcept = 0;

    virtual void WriteRaw(const void* buffer, const std::size_t& w_size) = 0;

    virtual const char* GetPath() const noexcept = 0;

    virtual const EFileAccess& GetFileMode() const noexcept = 0;

    virtual std::string ReadLine() const = 0;

    virtual std::string ReadToEnd() const = 0;
};
}  // namespace Toy::IO