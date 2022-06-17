set(Includes
    "include/Graphics_D3D12.hpp"
    "include/DXCCompiler.hpp"
)

set(Sources
    "src/Graphics_D3D12.cpp"
    "src/DXCCompiler.cpp"
)

set(Interfaces
    "interface/d3dx12.h"
)

add_library(Graphics-D3D12 STATIC ${Includes} ${Sources} ${Interfaces})
set_common_target_properties(Graphics-D3D12)

include(${EngineRootDIR}/DXC.cmake)
target_link_libraries(Graphics-D3D12
    PRIVATE Common EngineBuildSetting DXC
)

InstallEngineLib(Graphics-D3D12)