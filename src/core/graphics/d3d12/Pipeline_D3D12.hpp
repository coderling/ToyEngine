#pragma once

#include "IPipeline.hpp"

namespace Toy::Graphics
{
	class Pipeline final: public IPipeline
	{
	public:
		int Initialize() override;
		void Render() override;
	};
}