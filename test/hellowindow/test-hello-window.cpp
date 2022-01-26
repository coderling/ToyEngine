#include <WinApp.hpp>

using namespace Toy::Platform;
using namespace Toy::Engine;

int main(int argc, char** argv)
{
	const AppArgs args;
	IApp* p_app = static_cast<IApp*>(new WinApp(args));
	p_app->Initialize();
	while (!p_app->IsQuit())
	{
		p_app->Tick();
	}
	return 0;
}