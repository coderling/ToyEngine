project(EngineLib LANGUAGES CXX)
include(GNUInstallDirs)

add_definitions(
	-DUNICODE
	-D_UNICODE
	-DNOMINMAX #使用stl min max
)

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
add_definitions(
	-DENGINE_DEBUG
)
else()
add_definitions(
	-DENGINE_RELEASE
)
endif()

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 20)

  message(${CMAKE_CXX_STANDARD})

set(d3d12_libs
"d3d12.lib"
"dxgi.lib"
"d3dcompiler.lib"
)

add_library(Engine SHARED)

target_compile_definitions(Engine
	PUBLIC
		"$<BUILD_INTERFACE:Engine_EXPORTS>"
)

add_subdirectory(core)
add_subdirectory(platform)

target_link_libraries(Engine PUBLIC Common Graphics Platform Components)


get_target_property(CommonHeaders Common PUBLIC_HEADER)
get_target_property(GraphicsHeaders Graphics PUBLIC_HEADER)
get_target_property(PlatformHeaders Graphics PUBLIC_HEADER)

set_target_properties(Engine
	PROPERTIES
		POSITION_INDEPENDENT_CODE 1 # 告诉编译器生成位置无关的代码，都采用相对路径。
		CXX_VISIBILITY_PRESET 1 # 
		VERSION ${CMAKE_PROJECT_VERSION}
		SOVERSION ${CMAKE_PROJECT_VERSION_MAJOR} # 版本
		OUTPUT_NAME "ToyEngine" # 输出名称
		DEBUG_POSTFIX "_d" # debug版本output_name后缀
		PUBLIC_HEADER "${CommonHeaders};${GraphicsHeaders};${PlatformHeaders}"
		MACOSX_RPATH ON
)

include(GenerateExportHeader)
generate_export_header(Engine
	BASE_NAME "Engine" # 头文件宏
	EXPORT_MACRO_NAME "TOY_LIB_API" # 导出宏
	EXPORT_FILE_NAME "${CMAKE_CURRENT_SOURCE_DIR}/include/pch.hpp" #导出文件路径
	DEPRECATED_MACRO_NAME "DEPRECATED_TOY_LIB_API" # 废弃代码的宏 
	NO_EXPORT_MACRO_NAME "NOT_TOY_LIB_API" # 不导出的宏
	STATIC_DEFINE "AS_STATIC_LIB" # 编译静态库的宏
	NO_DEPRECATED_MACRO_NAME "WITHOUT_DEPRECATED" # 排除废弃代码的宏
	DEFINE_NO_DEPRECATED # 告诉预处理器，编译排除废弃代码
)

target_include_directories(Engine
	PUBLIC 
		"$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>"
		"$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>"
)

install(TARGETS Engine
	Common Platform Graphics Components
	EXPORT ToyEngineTargets
	ARCHIVE
		DESTINATION  ${CMAKE__INSTALL_LIBDIR}
	RUNTIME 
		DESTINATION ${CMAKE__INSTALL_BINDIR}
	LIBRARY
		DESTINATION ${CMAKE__INSTALL_BINDIR}
	INCLUDES
		DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)


install(
	FILES
		"${CMAKE_CURRENT_SOURCE_DIR}/include/pch.hpp" 
		DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)

install(EXPORT ToyEngineTargets
	FILE ToyEngineTargets.cmake
	NAMESPACE ToyEngine::
	DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/ToyEngine
)

# 
include(CmakePackageConfigHelpers)

write_basic_package_version_file(
	"${CMAKE_CURRENT_BINARY_DIR}/ToyEngineConfigVersion.cmake"
	VERSION "${CMAKE_PROJECT_VERSION}"
	COMPATIBILITY AnyNewerVersion
)

configure_package_config_file(
	${CMAKE_CURRENT_SOURCE_DIR}/cmake/ToyEngine.cmake.in
	"${CMAKE_CURRENT_BINARY_DIR}/ToyEngineConfig.cmake"
	INSTALL_DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/ToyEngine
)

install(
	FILES
		"${CMAKE_CURRENT_BINARY_DIR}/ToyEngineConfig.cmake"
		"${CMAKE_CURRENT_BINARY_DIR}/ToyEngineConfigVersion.cmake"
	DESTINATION
		${CMAKE_INSTALL_LIBDIR}/cmake/ToyEngine
)