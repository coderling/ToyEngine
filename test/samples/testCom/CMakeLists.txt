add_executable(dll-test test-TimerInDll.cpp)
target_link_libraries(dll-test
    PRIVATE
    EngineBuildSetting
    Common-Interface
    Graphics-D3D12-Shared
    DXC)

SetTestCommonProperties(dll-test)
target_compile_definitions(dll-test PRIVATE ENGINE_DLL_EXPORT=1)
CopyRequiredDLLs(dll-test)