#pragma once

#include <Windows.h>
#include <iostream>

namespace Toy::Engine
{
inline FARPROC LoadDLL(const char* dll_name, const char* function_name)
{
#if _WIN64
    const char* arc = "_x64";
#else
    const char* arc = "_x86";
#endif

#if _DEBUG || ENGINE_DEBUG
    const char* config = "_d";
#else
    const char* config = "_r";
#endif

    const size_t StringBufferSize = 4096;
    char* lib_name = (char*)malloc(StringBufferSize);

    sprintf_s(lib_name, StringBufferSize, "%s%s%s.dll", dll_name, arc, config);

    auto handle = LoadLibraryA(lib_name);
    auto error = GetLastError();

    if (handle == nullptr)
        {
            std::cerr << "failed to load dll: " << lib_name << std::endl;
            return nullptr;
        }

    auto p_func = GetProcAddress(handle, function_name);
    if (p_func == nullptr)
        {
            std::cerr << "failed to get function: " << function_name << std::endl;
            FreeLibrary(handle);
            return nullptr;
        }

    return p_func;
}
}  // namespace Toy::Engine