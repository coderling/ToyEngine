#pragma once

#include "IObject.hpp"

namespace Toy::Engine
{
class ISystem : public IObject
{
public:
	virtual int Initialize() = 0;
	virtual void Finalize() = 0;
	virtual void Tick() = 0;
};
}