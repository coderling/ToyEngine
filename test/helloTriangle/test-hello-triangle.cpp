#include <iostream>

#include "Platform.hpp"

using namespace std;

int main(int argc, char** argv)
{
    cout << "Hello Triangle!" << endl;
    Toy::Platform::StartEngine(L"Hello Triangle");
    return 0;
}