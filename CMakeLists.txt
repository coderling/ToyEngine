cmake_minimum_required(VERSION 3.20)
project(ToyEngine VERSION 0.0.1)

set(CMAKE_INSTALL_PREFIX ${PROJECT_SOURCE_DIR}/../EngineLib)
set(EXternalDIR ${PROJECT_SOURCE_DIR}/external CACHE INTERNAL "external dir root")
set(EngineRootDIR ${CMAKE_CURRENT_SOURCE_DIR} CACHE INTERNAL "cache project root")

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug CACHE STRING "" FORCE)
endif()

if("${CMAKE_SIZEOF_VOID_P}" EQUAL "8")
    set(ARCH 64 CACHE INTERNAL "64-bit architecture")
else()
    set(ARCH 32 CACHE INTERNAL "32-bit architecture")
endif()

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    set(IS_DEBUG_BUILD TRUE CACHE INTERNAL "")
else()
    set(IS_RELEASE_BUILD TRUE CACHE INTERNAL "")
endif()

set(DEBUG_DLL_SUFFIX _x${ARCH}_d CACHE INTERNAL "")
set(RELEASE_DLL_SUFFIX _x${ARCH}_r CACHE INTERNAL "")

set(TARGET_PLATFORM_WIN FALSE CACHE INTERNAL "")

if(WIN32)
    set(TARGET_PLATFORM_WIN TRUE CACHE INTERNAL "set default target platform")
    message("build target platform: Win32 arc: " ${ARCH} " " ${CMAKE_BUILD_TYPE})
else()
    message("Not support platform current platform")
endif()

add_library(EngineBuildSetting INTERFACE)
target_compile_definitions(EngineBuildSetting INTERFACE "$<$<CONFIG:DEBUG>:_DEBUG;DEBUG;ENGINE_DEVELOPMENT;ENGINE_DEBUG>")
target_compile_definitions(EngineBuildSetting INTERFACE "$<$<CONFIG:RELWITHDEBINFO>:ENGINE_DEVELOPMENT;>")

if(TARGET_PLATFORM_WIN)
    target_compile_definitions(EngineBuildSetting INTERFACE PLATFORM_WINDOWS=1)
endif()

set(DEBUG_CONFIGS DEBUG CACHE INTERNAL "release configs")
set(RELEASE_CONFIGS RELEASE RELWITHDEBINFO MINSIZEREL CACHE INTERNAL "release configs")

foreach(r_config ${RELEASE_CONFIGS})
    target_compile_definitions(EngineBuildSetting INTERFACE "$<$<CONFIG:${r_config}>:NDEBUG;ENGINE_RELEASE>")
endforeach()

if(IS_DEBUG_BUILD)
    set(CURRENT_LIB_SUFFIX ${DEBUG_DLL_SUFFIX} CACHE INTERNAL "")
else()
    set(CURRENT_LIB_SUFFIX ${RELEASE_DLL_SUFFIX} CACHE INTERNAL "")
endif()

set(ENGINE_STATIC_LIBS_LIST "" CACHE INTERNAL "Engine Libraries for install")

include(Common.cmake)
add_subdirectory(src)
InstallCoombinedStaticLib(
    "${CMAKE_STATIC_LIBRARY_PREFIX}ToyEngine${CURRENT_LIB_SUFFIX}${CMAKE_STATIC_LIBRARY_SUFFIX}"
    "${ENGINE_STATIC_LIBS_LIST}"
    Engine-Static
    EngineStatic
    "${CMAKE_INSTALL_LIBDIR}/$<CONFIG>"
)

add_subdirectory(test)