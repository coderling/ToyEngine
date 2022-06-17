
set(Includes
    ""
)

set(Sources
    "src/SystemMgr.cpp"
)

set(Interfaces
    "interface/SystemMgr.hpp"
)

add_library(EngineComponents-Basic STATIC ${Interfaces} ${Sources})
set_common_target_properties(EngineComponents-Basic)

target_link_libraries(EngineComponents-Basic
    PRIVATE EngineBuildSetting
    PUBLIC Common EngineGraphics
)

InstallEngineLib(EngineComponents-Basic)