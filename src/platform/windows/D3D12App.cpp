#include "D3D12App.hpp"
#include "d3d12/Graphics_D3D12.hpp"

using namespace Toy::Platform;

int D3D12App::InitGraphics()
{
	IApp::env->graphics = std::make_unique<Toy::Graphics::Graphics>();
	int ret = IApp::env->graphics->Initialize();
	return ret;
}