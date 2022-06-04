# Install script for directory: E:/GitProj/ToyEngine/src

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "E:/GitProj/ToyEngine/EngineLib")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "Release")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "FALSE")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("E:/GitProj/ToyEngine/msbuild/src/core/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("E:/GitProj/ToyEngine/msbuild/src/platform/cmake_install.cmake")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  if("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Dd][Ee][Bb][Uu][Gg])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY OPTIONAL FILES "E:/GitProj/ToyEngine/msbuild/src/Debug/ToyEngine_d.lib")
  elseif("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Rr][Ee][Ll][Ee][Aa][Ss][Ee])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY OPTIONAL FILES "E:/GitProj/ToyEngine/msbuild/src/Release/ToyEngine.lib")
  elseif("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Mm][Ii][Nn][Ss][Ii][Zz][Ee][Rr][Ee][Ll])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY OPTIONAL FILES "E:/GitProj/ToyEngine/msbuild/src/MinSizeRel/ToyEngine.lib")
  elseif("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Rr][Ee][Ll][Ww][Ii][Tt][Hh][Dd][Ee][Bb][Ii][Nn][Ff][Oo])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY OPTIONAL FILES "E:/GitProj/ToyEngine/msbuild/src/RelWithDebInfo/ToyEngine.lib")
  endif()
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  if("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Dd][Ee][Bb][Uu][Gg])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin" TYPE SHARED_LIBRARY FILES "E:/GitProj/ToyEngine/msbuild/src/Debug/ToyEngine_d.dll")
  elseif("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Rr][Ee][Ll][Ee][Aa][Ss][Ee])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin" TYPE SHARED_LIBRARY FILES "E:/GitProj/ToyEngine/msbuild/src/Release/ToyEngine.dll")
  elseif("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Mm][Ii][Nn][Ss][Ii][Zz][Ee][Rr][Ee][Ll])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin" TYPE SHARED_LIBRARY FILES "E:/GitProj/ToyEngine/msbuild/src/MinSizeRel/ToyEngine.dll")
  elseif("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Rr][Ee][Ll][Ww][Ii][Tt][Hh][Dd][Ee][Bb][Ii][Nn][Ff][Oo])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin" TYPE SHARED_LIBRARY FILES "E:/GitProj/ToyEngine/msbuild/src/RelWithDebInfo/ToyEngine.dll")
  endif()
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include" TYPE FILE FILES
    "E:/GitProj/ToyEngine/src/core/common/../interface/AppArgs.hpp"
    "E:/GitProj/ToyEngine/src/core/common/../interface/GlobalEnvironment.hpp"
    "E:/GitProj/ToyEngine/src/core/common/../interface/IApp.hpp"
    "E:/GitProj/ToyEngine/src/core/common/../interface/IObject.hpp"
    "E:/GitProj/ToyEngine/src/core/common/../interface/ISystem.hpp"
    "E:/GitProj/ToyEngine/src/core/common/../interface/IAllocator.hpp"
    "E:/GitProj/ToyEngine/src/core/common/Align.hpp"
    "E:/GitProj/ToyEngine/src/core/common/FormatString.hpp"
    "E:/GitProj/ToyEngine/src/core/common/DebugUtility.hpp"
    "E:/GitProj/ToyEngine/src/core/common/EngineUtility.hpp"
    "E:/GitProj/ToyEngine/src/core/common/Logger.hpp"
    "E:/GitProj/ToyEngine/src/core/common/STDAllocator.hpp"
    "E:/GitProj/ToyEngine/src/core/common/VariableSizeAllocationsManager.hpp"
    "E:/GitProj/ToyEngine/src/core/common/DefaultMemoryAllocator.hpp"
    "E:/GitProj/ToyEngine/src/core/graphics/PipelineFragment.hpp"
    "E:/GitProj/ToyEngine/src/core/graphics/GraphicsDef.hpp"
    "E:/GitProj/ToyEngine/src/core/graphics/interface/IPipelineFragmentHandler.hpp"
    "E:/GitProj/ToyEngine/src/core/graphics/interface/IFrameResource.hpp"
    "E:/GitProj/ToyEngine/src/core/graphics/interface/ISwapChain.hpp"
    "E:/GitProj/ToyEngine/src/core/graphics/interface/IGPUResource.hpp"
    "E:/GitProj/ToyEngine/src/core/graphics/interface/IGraphicsCommandQueue.hpp"
    "E:/GitProj/ToyEngine/src/core/graphics/interface/IGraphicsCommandList.hpp"
    "E:/GitProj/ToyEngine/src/core/graphics/interface/IGraphics.hpp"
    "E:/GitProj/ToyEngine/src/core/graphics/interface/IPipeline.hpp"
    "E:/GitProj/ToyEngine/src/core/graphics/interface/IUploadBuffer.hpp"
    "E:/GitProj/ToyEngine/src/core/graphics/PipelineFragment.hpp"
    "E:/GitProj/ToyEngine/src/core/graphics/GraphicsDef.hpp"
    "E:/GitProj/ToyEngine/src/core/graphics/interface/IPipelineFragmentHandler.hpp"
    "E:/GitProj/ToyEngine/src/core/graphics/interface/IFrameResource.hpp"
    "E:/GitProj/ToyEngine/src/core/graphics/interface/ISwapChain.hpp"
    "E:/GitProj/ToyEngine/src/core/graphics/interface/IGPUResource.hpp"
    "E:/GitProj/ToyEngine/src/core/graphics/interface/IGraphicsCommandQueue.hpp"
    "E:/GitProj/ToyEngine/src/core/graphics/interface/IGraphicsCommandList.hpp"
    "E:/GitProj/ToyEngine/src/core/graphics/interface/IGraphics.hpp"
    "E:/GitProj/ToyEngine/src/core/graphics/interface/IPipeline.hpp"
    "E:/GitProj/ToyEngine/src/core/graphics/interface/IUploadBuffer.hpp"
    )
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include" TYPE FILE FILES
    "E:/GitProj/ToyEngine/src/core/common/../interface/AppArgs.hpp"
    "E:/GitProj/ToyEngine/src/core/common/../interface/GlobalEnvironment.hpp"
    "E:/GitProj/ToyEngine/src/core/common/../interface/IApp.hpp"
    "E:/GitProj/ToyEngine/src/core/common/../interface/IObject.hpp"
    "E:/GitProj/ToyEngine/src/core/common/../interface/ISystem.hpp"
    "E:/GitProj/ToyEngine/src/core/common/../interface/IAllocator.hpp"
    "E:/GitProj/ToyEngine/src/core/common/Align.hpp"
    "E:/GitProj/ToyEngine/src/core/common/FormatString.hpp"
    "E:/GitProj/ToyEngine/src/core/common/DebugUtility.hpp"
    "E:/GitProj/ToyEngine/src/core/common/EngineUtility.hpp"
    "E:/GitProj/ToyEngine/src/core/common/Logger.hpp"
    "E:/GitProj/ToyEngine/src/core/common/STDAllocator.hpp"
    "E:/GitProj/ToyEngine/src/core/common/VariableSizeAllocationsManager.hpp"
    "E:/GitProj/ToyEngine/src/core/common/DefaultMemoryAllocator.hpp"
    )
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include" TYPE FILE FILES "E:/GitProj/ToyEngine/src/platform/Platform.hpp")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include" TYPE FILE FILES
    "E:/GitProj/ToyEngine/src/core/graphics/PipelineFragment.hpp"
    "E:/GitProj/ToyEngine/src/core/graphics/GraphicsDef.hpp"
    "E:/GitProj/ToyEngine/src/core/graphics/interface/IPipelineFragmentHandler.hpp"
    "E:/GitProj/ToyEngine/src/core/graphics/interface/IFrameResource.hpp"
    "E:/GitProj/ToyEngine/src/core/graphics/interface/ISwapChain.hpp"
    "E:/GitProj/ToyEngine/src/core/graphics/interface/IGPUResource.hpp"
    "E:/GitProj/ToyEngine/src/core/graphics/interface/IGraphicsCommandQueue.hpp"
    "E:/GitProj/ToyEngine/src/core/graphics/interface/IGraphicsCommandList.hpp"
    "E:/GitProj/ToyEngine/src/core/graphics/interface/IGraphics.hpp"
    "E:/GitProj/ToyEngine/src/core/graphics/interface/IPipeline.hpp"
    "E:/GitProj/ToyEngine/src/core/graphics/interface/IUploadBuffer.hpp"
    )
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include" TYPE FILE FILES "E:/GitProj/ToyEngine/src/include/pch.hpp")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/ToyEngine/ToyEngineTargets.cmake")
    file(DIFFERENT EXPORT_FILE_CHANGED FILES
         "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/ToyEngine/ToyEngineTargets.cmake"
         "E:/GitProj/ToyEngine/msbuild/src/CMakeFiles/Export/lib/cmake/ToyEngine/ToyEngineTargets.cmake")
    if(EXPORT_FILE_CHANGED)
      file(GLOB OLD_CONFIG_FILES "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/ToyEngine/ToyEngineTargets-*.cmake")
      if(OLD_CONFIG_FILES)
        message(STATUS "Old export file \"$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/ToyEngine/ToyEngineTargets.cmake\" will be replaced.  Removing files [${OLD_CONFIG_FILES}].")
        file(REMOVE ${OLD_CONFIG_FILES})
      endif()
    endif()
  endif()
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake/ToyEngine" TYPE FILE FILES "E:/GitProj/ToyEngine/msbuild/src/CMakeFiles/Export/lib/cmake/ToyEngine/ToyEngineTargets.cmake")
  if("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Dd][Ee][Bb][Uu][Gg])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake/ToyEngine" TYPE FILE FILES "E:/GitProj/ToyEngine/msbuild/src/CMakeFiles/Export/lib/cmake/ToyEngine/ToyEngineTargets-debug.cmake")
  endif()
  if("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Mm][Ii][Nn][Ss][Ii][Zz][Ee][Rr][Ee][Ll])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake/ToyEngine" TYPE FILE FILES "E:/GitProj/ToyEngine/msbuild/src/CMakeFiles/Export/lib/cmake/ToyEngine/ToyEngineTargets-minsizerel.cmake")
  endif()
  if("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Rr][Ee][Ll][Ww][Ii][Tt][Hh][Dd][Ee][Bb][Ii][Nn][Ff][Oo])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake/ToyEngine" TYPE FILE FILES "E:/GitProj/ToyEngine/msbuild/src/CMakeFiles/Export/lib/cmake/ToyEngine/ToyEngineTargets-relwithdebinfo.cmake")
  endif()
  if("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Rr][Ee][Ll][Ee][Aa][Ss][Ee])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake/ToyEngine" TYPE FILE FILES "E:/GitProj/ToyEngine/msbuild/src/CMakeFiles/Export/lib/cmake/ToyEngine/ToyEngineTargets-release.cmake")
  endif()
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake/ToyEngine" TYPE FILE FILES
    "E:/GitProj/ToyEngine/msbuild/src/ToyEngineConfig.cmake"
    "E:/GitProj/ToyEngine/msbuild/src/ToyEngineConfigVersion.cmake"
    )
endif()

