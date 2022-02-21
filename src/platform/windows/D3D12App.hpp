#pragma once

#include "WinApp.hpp"

namespace Toy::Platform
{
	class D3D12App final : public WinApp
	{
	public:
		explicit D3D12App(const AppArgs& args) : WinApp(args){}
		void Tick() override;
	protected:
	
	};
}
