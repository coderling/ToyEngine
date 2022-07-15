#pragma once

#include <string>
#include "AppArgs.hpp"
#include "Client.hpp"
#include "INativeWindow.hpp"

namespace Toy::Platform
{
int InitEngine(const std::string& title);
int InitEngine(const Toy::Engine::AppArgs& args);
int StartEngine();

void CreateNativeWndow(INativeWindow** pp_nativewindow);
}  // namespace Toy::Platform
