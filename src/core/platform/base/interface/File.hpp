#pragma once
#include "CommonDefines.hpp"
#include "IDataBlob.hpp"
#include "IODefines.hpp"
#include "IncFileHandle.hpp"

namespace Toy::IO
{

class File
{
    char* file_path;
    EFileAccess* file_mode;
    FileHandle file_handle;

   public:
    NOCOPY_AND_NOMOVE(File);

    File(const char* path, const EFileAccess mode) noexcept;

    ~File();

    bool IsExits() const;
};

}  // namespace Toy::IO