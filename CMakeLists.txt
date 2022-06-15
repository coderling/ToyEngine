cmake_minimum_required(VERSION 3.20)
project(ToyEngine VERSION 0.0.1)

set(CMAKE_INSTALL_PREFIX ${PROJECT_SOURCE_DIR}/../EngineLib)
set(EXternalDIR ${PROJECT_SOURCE_DIR}/External)

include(Common.cmake)
include(DXC.cmake)
add_subdirectory(src)
add_subdirectory(ThirdLib)