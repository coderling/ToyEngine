cmake_minimum_required(VERSION 3.5)
project(ToyEngine LANGUAGES CXX)

add_definitions(-DUNICODE -D_UNICODE)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(_Install_path ${PROJECT_SOURCE_DIR/bin})
if(NOT EXISTS "${_Install_path}")
    execute_process(
        COMMAND New-Item ${_Install_path} -type directory
    )
endif()

set(d3d12_libs
"d3d12.lib"
"dxgi.lib"
"d3dcompiler.lib"
)

include_directories("${PROJECT_SOURCE_DIR}/src/core/interface")
include_directories("${PROJECT_SOURCE_DIR}/src/core/common")
include_directories("${PROJECT_SOURCE_DIR}/src/platform/windows")

add_subdirectory(test)
add_subdirectory(src)