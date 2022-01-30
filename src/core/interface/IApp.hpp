#pragma once

#include "ISystem.hpp"
#include "AppArgs.hpp"
#include "GlobalEnvironment.hpp"

namespace Toy::Engine
{
class IApp : public ISystem
{
public:
	explicit IApp(const AppArgs& args):args(args){}
	int Initialize() override = 0;
	void Finalize() override = 0;
	void Tick() override = 0;

	[[nodiscard("APP::IsQuit")]] virtual bool IsQuit() const = 0;

	virtual void Quit() = 0;

	virtual void* GetHwnd() = 0;
	
	const AppArgs& GetArgs()const noexcept { return args; };
	static GlobalEnvironment* const env;
protected:
	virtual int CreateAppWindow() = 0;
		
	AppArgs args;
};
}