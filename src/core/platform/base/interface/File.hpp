#pragma once
#include "CommonDefines.hpp"
#include "IDataBlob.hpp"
#include "IODefines.hpp"
#include "IncFileHandle.hpp"

namespace Toy::IO
{

class File final
{
    FileHandle file_handle;

   public:
    NOCOPY_AND_NOMOVE(File);

    File(const char* path, const EFileAccess& mode);

    ~File();

    NODISCARD bool IsExits() const;

    void Open(const char* path, const EFileAccess& mode);

    void Close();

    void ReadRaw(void* p_data, const std::size_t& r_size);

    void ReadBlob(Engine::IDataBlob* blob);

    NODISCARD std::size_t GetLength() const noexcept;

    NODISCARD std::size_t GetPosition() const noexcept;

    void WriteRaw(const void* buffer, const std::size_t& w_size);

    void WriteBlob(const Engine::IDataBlob* blob, const std::size_t& w_size);

    void WriteBlob(const Engine::IDataBlob* blob);

    void WriteText(const char* text);

    NODISCARD std::string ReadLine() const;

    NODISCARD std::string ReadToEnd() const;

    void Seek(const std::size_t& offset, const ESeekOrigin& orgin);
};

}  // namespace Toy::IO