#pragma once
#include <Windows.h>
#include <windowsx.h>

#include <App.hpp>

using namespace Toy::Engine;

namespace Toy::Platform
{
	class WinApp : public App
	{
	public:
		explicit WinApp(const AppArgs& args) : hwnd(NULL), hdc(NULL), App(args) { }
		void Finalize() override;

		void Tick() override;
		void* GetHwnd() override;
	protected:
		int CreateAppWindow() override;
		int InitGraphics() override;

	private:
		static LRESULT CALLBACK WindowProc(HWND hwnd, UINT message, WPARAM wparam, LPARAM lparam);

	protected:
		HWND hwnd;
		HDC hdc;
	};
}