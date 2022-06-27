#pragma once
#include "IDataBlob.hpp"
#include "IODefines.hpp"

namespace Toy::IO
{
class IFileHandle
{
   public:
    static IFileHandle* CreateFile(const char* path, EFileAccess mode);
    NOCOPY_AND_NOMOVE(IFileHandle);

    virtual void Close();

    virtual void ReadRaw(void* p_data, const std::size_t& r_size) = 0;

    virtual void ReadBlob(Engine::IDataBlob* blob, const std::size_t& r_size) = 0;

    virtual void Seek(const std::size_t& offset, const ESeekOrigin& orgin);

    virtual std::size_t GetLength() const noexcept = 0;
    virtual std::size_t GetPosition() const noexcept = 0;

    virtual void WriteRaw(const void* buff, const std::size_t& w_size) = 0;

    virtual void WriteBlob(const Engine ::IDataBlob* blob, const std::size_t& w_size = 0) = 0;
};
}  // namespace Toy::IO