set(Includes
    "include/Graphics_D3D12.hpp"
)

set(Sources
    "src/Graphics_D3D12.cpp"
    "src/DXCCompiler.cpp"
    "src/D3D12Factory.cpp"
)

set(Interfaces
    "interface/d3dx12.h"
    "interface/DXCCompiler.hpp"
    "interface/ID3D12Factory.hpp"
)

add_library(Graphics-D3D12 STATIC ${Includes} ${Sources} ${Interfaces})
SetCommonTargetProperties(Graphics-D3D12)
target_include_directories(Graphics-D3D12
    PRIVATE
    include
)

include(${EngineRootDIR}/DXC.cmake)

add_library(Graphics-D3D12-Interface INTERFACE)
target_link_libraries(Graphics-D3D12-Interface INTERFACE Graphics-Base-Interface)
target_include_directories(Graphics-D3D12-Interface INTERFACE interface)

target_link_libraries(Graphics-D3D12
    PRIVATE
    EngineBuildSetting
    DXC
    Common
    Graphics-Base
    "d3d12.lib"
    "dxgi.lib"
    PUBLIC
    Graphics-D3D12-Interface
)

set(Dll_Source
    "src/DLLMain.cpp"
    "src/GraphicsD3D12.def"
)

add_library(Graphics-D3D12-Shared SHARED ${Dll_Source})
SetCommonTargetProperties(Graphics-D3D12-Shared)

target_link_libraries(Graphics-D3D12-Shared
    PRIVATE
    EngineBuildSetting
    Graphics-D3D12
    PUBLIC
    Graphics-D3D12-Interface
)

target_compile_definitions(Graphics-D3D12-Shared PUBLIC ENGINE_DLL_EXPORT=1)
SetTargetOutputName(Graphics-D3D12-Shared GraphicsD3D12)

InstallEngineLib(Graphics-D3D12)
InstallEngineLib(Graphics-D3D12-Shared)