#pragma once

#include <Windows.h>
#include "d3dx12.h"

namespace Toy::Graphics
{
	inline void Print(const char* msg) { printf("%s", msg); }
	inline void Print(const wchar_t* msg) { wprintf(L"%ws", msg); }
	
	inline void PrintSubMessage(const char* format, ...)
	{
		Print("-->");
		char buffer[256];
		va_list ap;
		va_start(ap, format);
		vsprintf_s(buffer, 256, format, ap);
		va_end(ap);
		Print(buffer);
		Print("\n");
	}
	
	inline void PrintSubMessage(const wchar_t* format, ...)
	{
		Print("-->");
		wchar_t buffer[256];
		va_list ap;
		va_start(ap, format);
		vswprintf_s(buffer, 256, format, ap);
		va_end(ap);
		Print(buffer);
		Print("\n");
	}
	
	inline void PrintSubMessage(void){}

#ifdef RELEASE
#define ASSERT_SUCCEEDED(hr, ...) (void)(hr)
#else
#define STRINGIFY(x) #x
#define STRINGIFY_BUILTIN(x) STRINGIFY(x)
#define ASSERT_SUCCEEDED(hr, ...)\
	if(FAILED(hr)){\
		Print("\nHRESULT failed in " STRINGIFY_BUILTIN(__FILE__) "@" STRINGIFY_BUILTIN(__LINE__) "\n");\
		PrintSubMessage("hr = 0x%08x", hr);\
		PrintSubMessage(__VA_ARGS__);\
		Print("\n");\
		__debugbreak();\
	}
#endif

#if defined(_DEBUG) || defined(DGB)
	inline void SetName(ID3D12Object* pobj, LPCWSTR name)
	{
		pobj->SetName(name);
	}
	
	inline void SetNameIndexed(ID3D12Object* pobj, LPCWSTR name, UINT index)
	{
		WCHAR fullname[50];
		if (swprintf_s(fullname, L"%s[%u]", name, index) > 0)
		{
			pobj->SetName(fullname);
		}
	}
#else
	inline void SetName(ID3D12Object* pobj, LPCWSTR name)
	{
	}
	
	inline void SetNameIndexed(ID3D12Object* pobj, LPCWSTR name, UINT index)
	{
	}
#endif
	// Naming helper for ComPtr<T>.
// Assigns the name of the variable as the name of the object.
// The indexed variant will include the index in the name of the object.
#define NAME_D3D12_OBJECT(x) SetName((x).Get(), L#x)
#define NAME_D3D12_OBJECT_INDEXED(x, n) SetNameIndexed((x)[n].Get(), L#x, n)
}
