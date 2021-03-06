#pragma once
#include <string>
#include <cstdint>

#include "pch.hpp"

namespace Toy::Engine
{
	struct TOY_LIB_API AppArgs
	{
		explicit AppArgs(const std::string name = "ToyEngine", int32_t width = 1920, int32_t height = 1080)
			: screen_width(width),
			screen_height(height),
			app_name(name),
			use_wrap_device(false)
		{}

		void ParseCommandArgs(int argc, char** argv)
		{
			this->argc = argc;
			this->argv = argv;

			for (int idx = 2; idx < argc; idx += 2)
			{
				char* option = argv[idx - 1];
				if (strcmp(option, "-DataPath") == 0)
				{
					this->data_path = argv[idx];
				}
			}
		}
		const std::string app_name;
		std::string data_path;

		int32_t screen_width{ 1920 };
		int32_t screen_height{ 1080 };
		const bool use_wrap_device;
		int32_t frame_count{ 3 };
		bool hdr{ false };

	private:
		int argc;
		char** argv;
	};
}
