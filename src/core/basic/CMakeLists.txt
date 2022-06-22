
set(Includes "")

set(Sources
    "src/SpinLock.cpp"
)

set(Interfaces
    "interface/Align.hpp"
    "interface/Atomics.hpp"
    "interface/CommonDefines.hpp"
    "interface/FormatString.hpp"
    "interface/HashUtils.hpp"
    "interface/IAllocator.hpp"
    "interface/InterfaceUUID.hpp"
    "interface/IObject.hpp"
    "interface/IReferenceCounter.hpp"
    "interface/IDataBlob.hpp"
    "interface/SpinLock.hpp"
)

add_library(CoreBasic STATIC ${Includes} ${Sources} ${Interfaces})
target_include_directories(CoreBasic
    PRIVATE
    include
    PUBLIC
    interface
)

SetCommonTargetProperties(CoreBasic)

target_link_libraries(CoreBasic
    PRIVATE
    EngineBuildSetting
)

InstallEngineLib(CoreBasic)