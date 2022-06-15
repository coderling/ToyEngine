cmake_minimum_required(VERSION 3.20)
project(Test)

set(ToyEngine_DIR ${PROJECT_SOURCE_DIR}/../../EngineLIb/Lib/cmake/ToyEngine)
include(../Common.cmake)
add_subdirectory(helloTriangle)
# add_subdirectory(HelloWindow)
# googletest
add_subdirectory(ThirdParty)
add_subdirectory(testUtility)
add_subdirectory(apiTest)
