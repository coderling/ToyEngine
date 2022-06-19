
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
SetCommonTargetProperties(EngineComponents-Basic)
target_include_directories(EngineComponents-Basic
    PRIVATE
    include
)

add_library(EngineComponents-Interface INTERFACE)
target_include_directories(EngineComponents-Interface INTERFACE interface)

target_link_libraries(EngineComponents-Basic
    PRIVATE
    EngineBuildSetting
    Common
    EngineGraphics
    PUBLIC
    EngineComponents-Interface
)

InstallEngineLib(EngineComponents-Basic)