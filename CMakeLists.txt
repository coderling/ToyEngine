cmake_minimum_required(VERSION 3.20)
project(ToyEngine VERSION 0.0.1)

set(CMAKE_INSTALL_PREFIX ${PROJECT_SOURCE_DIR}/../EngineLib)
set(DXCFolder ${PROJECT_SOURCE_DIR}/External/dxc)
set(DXCFolder_Lib ${PROJECT_SOURCE_DIR}/External/dxc/lib/x64)

include(Common.cmake)
add_subdirectory(src)
add_subdirectory(ThirdLib)