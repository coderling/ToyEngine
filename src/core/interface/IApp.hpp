#pragma once

#include "ISystem.hpp"
#include<cstdint>

namespace Toy::Engine
{
	struct GlobalEnvironment;
	
	struct AppArgs
	{
		explicit AppArgs(int32_t width = 1920, int32_t height = 1080, const char* name = "ToyEngine")
			: screen_width(width),
			screen_height(height),
			app_name(name) ,
			use_wrap_device(false)
		{}

		const char* app_name;
		
		int32_t screen_width{ 1920 };
		int32_t screen_height{ 1080 };
		const bool use_wrap_device;
		int32_t frame_count{ 3 };
		bool hdr{ false };
		
	};
	
	class IApp : public ISystem
	{
	public:
		int Initialize() override = 0;
		void Finalize() override = 0;
		void Tick() override = 0;

		[[nodiscard("APP::IsQuit")]] virtual bool IsQuit() const = 0;

		virtual void Quit() = 0;

		virtual void* GetHwnd() = 0;

		virtual const AppArgs* GetArgs()const noexcept = 0;
		static GlobalEnvironment* const env;
	protected:
		virtual int CreateAppWindow() = 0;
	};
}