add_executable(hello_graphics hello_graphics.cpp)
target_link_libraries(hello_graphics
    PRIVATE
    EngineBuildSetting
    CoreBasic
    Common-Interface
    Graphics-D3D12-Shared
    DXC
    EnginePlatform
)

target_compile_definitions(hello_graphics PRIVATE ENGINE_DLL_EXPORT=1)
SetTestCommonProperties(hello_graphics)
CopyRequiredDLLs(hello_graphics)