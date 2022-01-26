#pragma once

namespace Toy::Engine
{
	class IObject
	{
	public:
		virtual ~IObject() = default;
		virtual void Destroy() = 0;
	};
}