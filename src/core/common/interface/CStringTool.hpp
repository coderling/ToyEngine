#pragma once
#include <string>
#include "DebugUtility.hpp"

namespace Toy
{
inline bool Num(const char& c) { return c >= '0' && c <= '9'; }

inline bool CStrEqual(const char* lstr, const char* rstr)
{
    if ((lstr == nullptr) != (rstr == nullptr))
        {
            return false;
        }

    if (lstr != nullptr && rstr != nullptr)
        {
            return strcmp(lstr, rstr) == 0;
        }

    return true;
}

inline std::wstring Str2Wstr(const char* str, const std::size_t& len)
{
    auto slen = len;
    if (slen == 0)
        {
            slen = std::strlen(str);
        }
    else
        {
            slen = std::strlen(str);
            ENGINE_DEV_CHECK_EXPR(len <= slen);
            slen = slen < len ? slen : len;
        }

    std::wstring wstr(slen, L'\0');
    const std::ctype<wchar_t>& ctfacet = std::use_facet<std::ctype<wchar_t>>(std::wstringstream().getloc());
    for (std::size_t i = 0; i < slen; i++)
        {
            wstr[i] = ctfacet.widen(str[i]);
        }

    return wstr;
}

inline std::wstring Str2Wstr(const std::string_view& str) { return Str2Wstr(str.data(), str.length()); }

inline std::string Wstr2Str(const wchar_t* wstr, const std::size_t& len)
{
    auto slen = len;
    if (slen == 0)
        {
            slen = std::wcslen(wstr);
        }
    else
        {
            slen = std::wcslen(wstr);
            ENGINE_DEV_CHECK_EXPR(len <= slen);
            slen = slen < len ? slen : len;
        }

    std::string str(slen, '\0');
    const std::ctype<wchar_t>& ctfacet = std::use_facet<std::ctype<wchar_t>>(std::wstringstream().getloc());
    for (std::size_t i = 0; i < slen; i++)
        {
            str[i] = ctfacet.narrow(wstr[i]);
        }

    return str;
}

inline std::string Wstr2Str(const std::wstring_view& wstr) { return Wstr2Str(wstr.data(), wstr.length()); }

inline char* CopyString(const char* cstr, const std::size_t& len)
{
    auto slen = len;
    if (slen == 0)
        {
            slen = std::strlen(cstr);
        }
    else
        {
            slen = std::strlen(cstr);
            ENGINE_DEV_CHECK_EXPR(len <= slen);
            slen = slen < len ? slen : len;
        }

    auto buffer = new char[slen + 1];
    strcpy_s(buffer, slen, cstr);
    buffer[slen] = '\0';

    return buffer;
}

inline char* CopyString(const std::string_view& str) { return CopyString(str.data(), str.length()); }

inline wchar_t* CopyString(const wchar_t* cstr, const std::size_t& len)
{
    auto slen = len;
    if (slen == 0)
        {
            slen = std::wcslen(cstr);
        }
    else
        {
            slen = std::wcslen(cstr);
            ENGINE_DEV_CHECK_EXPR(len <= slen);
            slen = slen < len ? slen : len;
        }

    auto buffer = new wchar_t[slen + 1];
    wcscpy_s(buffer, slen, cstr);
    buffer[slen] = '\0';

    return buffer;
}

inline wchar_t* CopyString(const std::wstring_view& str) { return CopyString(str.data(), str.length()); }

}  // namespace Toy