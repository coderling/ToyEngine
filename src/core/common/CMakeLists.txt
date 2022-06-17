set(Includes "include/PreInc.hpp")

set(Sources
    "src/DefaultMemoryAllocator.cpp"
    "src/Time.cpp"
    "src/VariableSizeAllocationsManager.cpp"
)

set(Interfaces
    "interface/AppArgs.hpp"
    "interface/Align.hpp"
    "interface/CStringTool.hpp"
    "interface/DebugUtility.hpp"
    "interface/DefaultMemoryAllocator.hpp"
    "interface/FormatString.hpp"
    "interface/HashUtils.hpp"
    "interface/IAllocator.hpp"
    "interface/IObject.hpp"
    "interface/Logger.hpp"
    "interface/pch.hpp"
    "interface/STDAllocator.hpp"
    "interface/Time.hpp"
    "interface/CommonDefines.hpp"
    "interface/VariableSizeAllocationsManager.hpp"
)

add_library(Common STATIC ${Sources} ${Includes} ${Interfaces})
SetCommonTargetProperties(Common)

target_link_libraries(Common PRIVATE EngineBuildSetting)

InstallEngineLib(Common)
