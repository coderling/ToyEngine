#pragma once

#include <string>
#include "pch.hpp"
#include "AppArgs.hpp"

namespace Toy::Platform
{
	int TOY_LIB_API InitEngine(const std::wstring& title);
	int TOY_LIB_API InitEngine(const Toy::Engine::AppArgs& args);
	int TOY_LIB_API StartEngine();
}

