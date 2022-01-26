#pragma once

#include "IApp.hpp"
#include "AppArgs.hpp"

namespace Toy::Engine
{
	class App : public IApp
	{
	public:
		explicit App(const AppArgs& args);
		int  Initialize() override;
		void Finalize() override;
		void Tick() override;

		[[nodiscard("App::IsQuit")]] bool IsQuit() const override;

		void Quit() override;
		void Destroy() override;
	protected:
		int CreateAppWindow() override;

		static bool quit;
		AppArgs args;
	private:
		App() = delete;
	};
}