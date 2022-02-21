#pragma once

#include "../interface/IApp.hpp"

#include <memory>

namespace Toy::Engine
{
	class App : public IApp
	{
	public:
		explicit App(const AppArgs& args);
		~App() noexcept {}
		int  Initialize() override;
		void Finalize() override;
		void Tick() override;

		[[nodiscard("App::IsQuit")]] bool IsQuit() const override;

		[[nodiscard("App::GetArgs")]] const AppArgs* GetArgs() const noexcept override;
	
		void Quit() override;
		void Destroy() override;

	protected:
		int CreateAppWindow() override;

		static bool quit;
	private:
		int InitGraphics();

		std::unique_ptr<AppArgs> args;
	};
}