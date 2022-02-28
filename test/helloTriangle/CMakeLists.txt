cmake_minimum_required(VERSION 3.20)
project(hello_triangle)

set(CMAKE_CXX_STANDARD 20)

find_package(ToyEngine REQUIRED CONFIG) 

add_executable(helloTriangle "test-hello-triangle.cpp")
target_sources(helloTriangle 
	PRIVATE 
					"RenderLogic.hpp"
)

target_link_libraries(helloTriangle PRIVATE ToyEngine::Engine)
