#include <iostream>
#include <direct.h>
#include "Platform.hpp"
#include "GlobalEnvironment.hpp"

using namespace Toy::Engine;

int main(int argc, char** argv)
{
	AppArgs args(L"HelloWindow");
	Toy::Platform::InitEngine(args);
	Toy::Platform::StartEngine();
	return 0;
}