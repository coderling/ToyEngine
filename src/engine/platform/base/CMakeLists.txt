
set(Includes
)

set(Sources
    "src/Empty.cpp"
)

set(Interfaces
    "interface/Platform.hpp"
    "interface/INativeWindow.hpp"
)

add_library(EnginePlatform-Basic STATIC ${Includes} ${Interfaces} ${Sources})
SetCommonTargetProperties(EnginePlatform-Basic)
target_include_directories(EnginePlatform-Basic
    PRIVATE
    include
    PUBLIC
    interface
)

target_link_libraries(
    EnginePlatform-Basic
    PUBLIC Common EngineComponents-Basic
    PRIVATE EngineBuildSetting)

InstallEngineLib(EnginePlatform-Basic)