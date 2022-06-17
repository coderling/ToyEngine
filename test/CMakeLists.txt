cmake_minimum_required(VERSION 3.20)
project(Test)

# googletest
add_subdirectory(ThirdParty)

# tests
add_subdirectory(testUtility)

add_subdirectory(apiTest)
add_subdirectory(samples)
