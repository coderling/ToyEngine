set(Includes
)

set(Sources
    "src/STDFileHandle.cpp"
    "src/File.cpp"
)

set(Interfaces
    "interface/File.hpp"
    "interface/IFileHandle.hpp"
    "interface/IncFileHandle.hpp"
    "interface/IODefines.hpp"
    "interface/FileSystem.hpp"
    "interface/STDFileHandle.hpp"
    "interface/TFile.hpp"
)

add_library(PlatformBase STATIC ${Includes} ${Sources} ${Interfaces})
SetCommonTargetProperties(PlatformBase)
target_include_directories(PlatformBase
    PRIVATE
    include
    PUBLIC
    interface
)

target_link_libraries(PlatformBase
    PRIVATE
    EngineBuildSetting
    CoreBasic
    Common
    Common-Interface
)

InstallEngineLib(PlatformBase)