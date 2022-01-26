#pragma once

#include "ISystem.hpp"

namespace Toy::Engine
{
class IApp : public ISystem
{
public:
	int Initialize() override = 0;
	void Finalize() override = 0;
	void Tick() override = 0;

	[[nodiscard("APP::IsQuit")]] virtual bool IsQuit() const = 0;

	virtual void Quit() = 0;

protected:
	virtual int CreateAppWindow() = 0;
};
}