#pragma once

#include <string>

namespace Toy::Platform
{
	bool StartEngine(const std::wstring& title);
}

// win

#include "windows/WinApp.hpp"
#include "windows/D3D12App.hpp"
