# add_library(EnginePlatform-windows STATIC ${Includes} ${Interfaces} ${Sources})

set(Includes
    "include/WindowsDesktop.hpp"
)

set(Sources
    "src/WindowsDesktop.cpp"
    "src/Platform_Win.cpp"
)

set(Interfaces
)

add_library(EnginePlatform-windows-Interface INTERFACE)
target_include_directories(EnginePlatform-windows-Interface INTERFACE interface)

add_library(EnginePlatform-windows STATIC ${Includes} ${Interfaces} ${Sources})
SetCommonTargetProperties(EnginePlatform-windows)
target_include_directories(EnginePlatform-windows
    PRIVATE
    include
    PUBLIC
    EnginePlatform-windows-Interface
)

target_link_libraries(EnginePlatform-windows
    PRIVATE
    EngineBuildSetting
    EnginePlatform-Basic
)

InstallEngineLib(EnginePlatform-windows)