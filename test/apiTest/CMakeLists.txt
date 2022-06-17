cmake_minimum_required(VERSION 3.20)
project(apiTest)

set(CMAKE_CXX_STANDARD 20)
add_definitions(
    -DUNICODE
    -D_UNICODE
    -DNOMINMAX # 使用stl min max
)

file(GLOB source LIST_DIRECTORIES false src/*)
file(GLOB include LIST_DIRECTORIES false include/*)

set(all_source ${source} ${include})
add_executable(apiTest ${all_source})
SetTestCommonProperties(apiTest)

target_link_libraries(apiTest
    PRIVATE
    test_utility
    Common
    EngineGraphics
)