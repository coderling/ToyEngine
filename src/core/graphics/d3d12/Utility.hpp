#pragma once

#include <Windows.h>
#include <DebugUtility.hpp>
#include "d3dx12.h"

namespace Toy::Graphics
{
#ifdef RELEASE
#define ASSERT_SUCCEEDED(hr, ...)                                                                                                          \
    do                                                                                                                                     \
        {                                                                                                                                  \
    } while (false)
#else
#define ASSERT_SUCCEEDED(hr, ...)                                                                                                          \
    do                                                                                                                                     \
        {                                                                                                                                  \
            if (FAILED(hr))                                                                                                                \
                {                                                                                                                          \
                    const auto& result_str = Toy::FormatString("hr = {:#08X}", (unsigned long)hr);                                         \
                    ENGINE_ASSERT_FAILED("\n\tHRESULT failed ", result_str, ##__VA_ARGS__);                                                \
                    __debugbreak();                                                                                                        \
                }                                                                                                                          \
    } while (false)
#endif

#if defined(_DEBUG) || defined(DGB)
inline void SetName(ID3D12Object* pobj, LPCWSTR name) { pobj->SetName(name); }

inline void SetNameIndexed(ID3D12Object* pobj, LPCWSTR name, UINT index)
{
    WCHAR fullname[50];
    if (swprintf_s(fullname, L"%s[%u]", name, index) > 0)
        {
            pobj->SetName(fullname);
        }
}
#else
inline void SetName(ID3D12Object* pobj, LPCWSTR name) {}

inline void SetNameIndexed(ID3D12Object* pobj, LPCWSTR name, UINT index) {}
#endif
// Naming helper for ComPtr<T>.
// Assigns the name of the variable as the name of the object.
// The indexed variant will include the index in the name of the object.
#define NAME_D3D12_OBJECT(x) SetName((x).Get(), L#x)
#define NAME_D3D12_OBJECT_INDEXED(x, n) SetNameIndexed((x)[n].Get(), L#x, n)
}  // namespace Toy::Graphics
