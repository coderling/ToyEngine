cmake_minimum_required(VERSION 3.20)
project(test_utility)

set(CMAKE_CXX_STANDARD 20)

add_library(test_utility
	STATIC
		src/TestEnv.cpp
		include/TestEnv.hpp
)

target_link_libraries(test_utility
	PUBLIC
		GTest::gtest
)

target_include_directories(test_utility 
	PUBLIC
		include
)
