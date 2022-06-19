# add_library(EnginePlatform-windows STATIC ${Includes} ${Interfaces} ${Sources})

set(Includes
    "include/Windows.hpp"
)

set(Sources
    "src/Windows.cpp"
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

set(Dll_Source
    "src/DLLMain.cpp"
    "src/windows.def"
)

add_library(EnginePlatform-windows-Shared SHARED ${Dll_Source})
target_link_libraries(EnginePlatform-windows-Shared
    PRIVATE
    EngineBuildSetting
    EnginePlatform-windows
    PUBLIC
    EnginePlatform-windows-Interface
)

target_compile_definitions(EnginePlatform-windows-Shared PUBLIC ENGINE_DLL_EXPORT=1)

SetTargetOutputName(EnginePlatform-windows-Shared Platform-Windows)

InstallEngineLib(EnginePlatform-windows)
InstallEngineLib(EnginePlatform-windows-Shared)