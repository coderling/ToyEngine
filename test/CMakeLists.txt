cmake_minimum_required(VERSION 3.20)
project(Test)

# add_subdirectory(helloTriangle)
# add_subdirectory(HelloWindow)
# googletest
set(ToyEngine_DIR ${PROJECT_SOURCE_DIR}/../EngineLIb/Lib/cmake/ToyEngine)
add_subdirectory(ThirdParty)
add_subdirectory(testUtility)
add_subdirectory(apiTest)
