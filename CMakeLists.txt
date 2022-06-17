cmake_minimum_required(VERSION 3.20)
project(ToyEngine VERSION 0.0.1)

set(CMAKE_INSTALL_PREFIX ${PROJECT_SOURCE_DIR}/../EngineLib)
set(EXternalDIR ${PROJECT_SOURCE_DIR}/external CACHE INTERNAL "external dir root")
set(EngineRootDIR ${CMAKE_CURRENT_SOURCE_DIR} CACHE INTERNAL "cache project root")

add_library(EngineBuildSetting INTERFACE)

if(NOT TARGET_PLATFORM_WIN)
    set(TARGET_PLATFORM_WIN TRUE CACHE INTERNAL "set default target platform")
endif()

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug CACHE STRING "" FORCE)
endif()

if("${CMAKE_SIZEOF_VOID_P}" EQUAL "8")
    set(ARCH 64 CACHE INTERNAL "64-bit architecture")
else()
    set(ARCH 32 CACHE INTERNAL "32-bit architecture")
endif()

set(DEBUG_DLL_SUFFIX _${ARCH}_d CACHE INTERNAL "")
set(RELEASE_DLL_SUFFIX _${ARCH}_r CACHE INTERNAL "")

target_compile_definitions(EngineBuildSetting INTERFACE "$<$<CONFIG:DEBUG>:_DEBUG;DEBUG;ENGINE_DEVELOPMENT;ENGINE_DEBUG>")
target_compile_definitions(EngineBuildSetting INTERFACE "$<$<CONFIG:RELWITHDEBINFO>:ENGINE_DEVELOPMENT;>")

set(DEBUG_CONFIGS DEBUG CACHE INTERNAL "release configs")
set(RELEASE_CONFIGS RELEASE RELWITHDEBINFO MINSIZEREL CACHE INTERNAL "release configs")

foreach(r_config ${RELEASE_CONFIGS})
    target_compile_definitions(EngineBuildSetting INTERFACE "$<$<CONFIG:${r_config}>:NDEBUG;ENGINE_RELEASE>")
endforeach()

set(ENGINE_STATIC_LIBS_LIST "" CACHE INTERNAL "Engine Libraries for install")

include(Common.cmake)
add_subdirectory(src)
InstallCoombinedStaticLib(
    "${CMAKE_STATIC_LIBRARY_PREFIX}ToyEngine${CMAKE_STATIC_LIBRARY_SUFFIX}"
    "${ENGINE_STATIC_LIBS_LIST}"
    Engine-Static
    EngineStatic
    "${CMAKE_INSTALL_LIBDIR}/$<CONFIG>"
)
