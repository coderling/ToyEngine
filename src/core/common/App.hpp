#pragma once

#include "IApp.hpp"
#include "../components/SystemMgr.hpp"

#include <memory>
#include <iostream>

namespace Toy::Engine
{
	class App : public IApp
	{
	public:
		explicit App(const AppArgs& args);
		~App() noexcept override { std::cout << "~App()" << std::endl; }
		int  Initialize() override;
		void Finalize() override;
		void Tick() override;

		[[nodiscard("App::IsQuit")]] bool IsQuit() const override;

		[[nodiscard("App::GetArgs")]] const AppArgs* GetArgs() const noexcept override;
	
		void Quit() override;

	protected:
		int CreateAppWindow() override;

		static bool quit;
	private:
		int SystemSetup();

		std::unique_ptr<AppArgs> args;
		std::unique_ptr<SystemMgr> system_mgr;
	};
}