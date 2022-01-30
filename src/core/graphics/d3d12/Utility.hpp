#pragma once

#include <Windows.h>


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
}
