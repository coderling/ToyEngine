#pragma once
#include <string>
#include <cstdint>

#include "pch.hpp"

namespace Toy::Engine
{
	struct TOY_LIB_API AppArgs
	{
		explicit AppArgs(const std::wstring name = L"ToyEngine", int32_t width = 1920, int32_t height = 1080)
			: screen_width(width),
			screen_height(height),
			app_name(name),
			use_wrap_device(false)
		{}

		const std::wstring app_name;

		int32_t screen_width{ 1920 };
		int32_t screen_height{ 1080 };
		const bool use_wrap_device;
		int32_t frame_count{ 3 };
		bool hdr{ false };

	};
}
