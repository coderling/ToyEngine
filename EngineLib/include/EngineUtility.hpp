#pragma once
#include "pch.hpp"
#include <string>

#ifdef _WIN32
#include <Windows.h>
#else
#include <locale>
#endif // _WIN32


namespace Toy
{
	inline std::wstring TOY_LIB_API s2ws(const std::string_view& source)
	{
		size_t len;
		size_t slength = source.length() + 1;
#ifdef _WIN32
		len = MultiByteToWideChar(CP_ACP, 0, source.data(), static_cast<int>(slength), 0, 0);
#else
		len = std::mbstowcs(nullptr, source.c_str(), 0) + 1;
#endif // _WIN32
		wchar_t* buf = new wchar_t[len];
#ifdef _WIN32
		MultiByteToWideChar(CP_ACP, 0, source.data(), static_cast<int>(slength), buf, static_cast<int>(len));
#else
		std::mbstowcs(buf, source.c_str(), slength);
#endif // _WIN32
		std::wstring r(buf);
		delete[] buf;
		return r;

	}
}