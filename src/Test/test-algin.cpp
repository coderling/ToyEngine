#include <Align.hpp>
#include <iostream>

int main(int argc, char** argv)
{
	// up
	int v = 10;
	v = Toy::AlignUp(v, 4);
	std::cout << "10  alignup is " << v << std::endl;
	return 0;
}