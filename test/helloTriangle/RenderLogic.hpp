#pragma once

#include <IPipelineFragmentHandler.hpp>
#include <iostream>

class RenderLogic : public Toy::Graphics::IPipelineFragmentHandler
{
public:
	void Load() override
	{
		std::cout << "RenderLogic::Load" << std::endl;
	}

	void Render() override
	{
		std::cout << "RenderLogic::OnRender()" << std::endl;
	}
	
	void Unload() override
	{
		std::cout << "RenderLogic::Unload()" << std::endl;
	}

protected:
	void OnDestroy() override
	{
		std::cout << "RenderLogic::Destroy()" << std::endl;
	}
};
