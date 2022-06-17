set(Includes
    "include/Graphics_D3D12.hpp"
)

set(Sources
    "src/Graphics_D3D12.cpp"
    "src/DXCCompiler.cpp"
)

set(Interfaces
    "interface/d3dx12.h"
    "interface/DXCCompiler.hpp"
)

add_library(Graphics-D3D12 STATIC ${Includes} ${Sources} ${Interfaces})
SetCommonTargetProperties(Graphics-D3D12)

include(${EngineRootDIR}/DXC.cmake)
target_link_libraries(Graphics-D3D12
    PRIVATE EngineBuildSetting DXC
    PUBLIC Common Graphics-Base
)

InstallEngineLib(Graphics-D3D12)