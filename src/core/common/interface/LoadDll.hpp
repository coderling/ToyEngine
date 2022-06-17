#pragma once

#ifdef EXPORT_DLL
#include <Windows.h>
#include "Logger.hpp"
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

    auto lib_name = ConcatString(dll_name, arc, config, ".dll");
    auto handle = LoadLibraryA(lib_name.c_str());

    if (handle == nullptr)
        {
            LOG_ERROR("faile to Load ", dll_name);
            return nullptr;
        }

    auto p_func = GetProcAddress(handle, function_name);
    if (p_func == nullptr)
        {
            LOG_ERROR("fail to get function: ", function_name);
            FreeLibrary(handle);
            return nullptr;
        }

    return p_func;
}
}  // namespace Toy::Engine
#endif