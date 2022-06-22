set(Includes)

set(Sources
    "src/DefaultMemoryAllocator.cpp"
    "src/Time.cpp"
    "src/GlobalEnviroment.cpp"
    "src/VariableSizeAllocationsManager.cpp"
)

set(Interfaces
    "interface/AppArgs.hpp"
    "interface/CStringTool.hpp"
    "interface/DebugUtility.hpp"
    "interface/DefaultMemoryAllocator.hpp"
    "interface/STDAllocator.hpp"
    "interface/Time.hpp"
    "interface/VariableSizeAllocationsManager.hpp"
    "interface/LoadDLL.hpp"
    "interface/ReferenceCounterObject.hpp"
    "interface/ReferenceCounter.hpp"
    "interface/RefCountPtr.hpp"
    "interface/RefCountWeakPtr.hpp"
    "interface/TObject.hpp"
)

add_library(Common-Interface INTERFACE)
target_include_directories(Common-Interface INTERFACE interface)

add_library(Common STATIC ${Sources} ${Includes} ${Interfaces})
SetCommonTargetProperties(Common)
target_include_directories(Common
    PRIVATE include
)

target_link_libraries(Common
    PRIVATE
    EngineBuildSetting
    PUBLIC
    CoreBasic
    Common-Interface
)

InstallEngineLib(Common)
