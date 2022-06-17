cmake_minimum_required(VERSION 3.20)
project(Test)

set(ToyEngine_DIR ${PROJECT_SOURCE_DIR}/../../EngineLIb/Lib/cmake/ToyEngine)
include(../Common.cmake)

# googletest
add_subdirectory(ThirdParty)
add_subdirectory(testUtility)
add_subdirectory(apiTest)
add_subdirectory(samples)
