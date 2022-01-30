#pragma once

#include <cstdint>

namespace Toy::Engine
{
	struct GfxArgs
	{
		explicit GfxArgs(int32_t width = 1920, int32_t height = 1080, const char* name = "ToyEngine")
			: screen_width(width),
			screen_height(height),
			app_name(name) {}

		int32_t screen_width{ 1920 };
		int32_t screen_height{ 1080 };
		const char* app_name;
	};
}