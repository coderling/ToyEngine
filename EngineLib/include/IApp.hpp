#pragma once

#include "pch.hpp"
#include "ISystem.hpp"
#include "AppArgs.hpp"
#include<cstdint>
#include<string>

namespace Toy::Engine
{
	struct GlobalEnvironment;
	
	class TOY_LIB_API  IApp : public ISystem
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