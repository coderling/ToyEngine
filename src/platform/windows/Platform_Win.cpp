#include "Platform.hpp"
#include "D3D12App.hpp"

using namespace Toy::Platform;

bool StartEngine(const std::wstring& title)
{
	const AppArgs args;
	IApp* p_app = new D3D12App(args);
	const int& ret = p_app->Initialize();
	if(ret != 0)
	{
		return ret;
	}

	while (!p_app->IsQuit())
	{
		p_app->Tick();
	}

	return true;
}