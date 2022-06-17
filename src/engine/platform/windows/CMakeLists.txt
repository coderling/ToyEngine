# add_library(EnginePlatform-windows STATIC ${Includes} ${Interfaces} ${Sources})

set(Includes
    "include/Windows.hpp"
)

set(Sources
    "src/Windows.cpp"
    "src/Platform_Win.cpp"
)

set(Interfaces
    "interface/Platform.hpp"
)

add_library(EnginePlatform-windows STATIC ${Includes} ${Interfaces} ${Sources})
set_common_target_properties(EnginePlatform-windows)

target_link_libraries(EnginePlatform-windows PRIVATE EnginePlatform-Basic EngineBuildSetting)

InstallEngineLib(EnginePlatform-Basic)