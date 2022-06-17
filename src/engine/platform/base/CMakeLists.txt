
set(Includes
)

set(Sources
    "src/EngineLoop.cpp"
)

set(Interfaces
    "interface/Client.hpp"
    "interface/EngineLoop.hpp"
)

add_library(EnginePlatform-Basic STATIC ${Includes} ${Interfaces} ${Sources})
SetCommonTargetProperties(EnginePlatform-Basic)

target_link_libraries(
    EnginePlatform-Basic
    PUBLIC Common EngineComponents-Basic
    PRIVATE EngineBuildSetting)

InstallEngineLib(EnginePlatform-Basic)