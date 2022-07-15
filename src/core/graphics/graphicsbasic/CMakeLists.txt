set(Includes
    "include/Pipeline.hpp"
)

set(Sources
    "src/PipelineFragment.cpp"
    "src/Pipeline.cpp"
)

set(Interfaces
    "interface/IPipelineFragmentHandler.hpp"
    "interface/IPipeline.hpp"
    "interface/PipelineFragment.hpp"
    "interface/IShader.hpp"
    "interface/ICommandQueue.hpp"
    "interface/ISwapChain.hpp"
    "interface/IDXCCompiler.hpp"
    "interface/IRenderDevice.hpp"
    "interface/RenderDeviceBase.hpp"
    "interface/IPipelineState.hpp"
)

add_library(Graphics-Base STATIC ${Includes} ${Sources} ${Interfaces})
SetCommonTargetProperties(Graphics-Base)
target_include_directories(Graphics-Base
    PRIVATE
    include
)

add_library(Graphics-Base-Interface INTERFACE)
target_include_directories(Graphics-Base-Interface INTERFACE interface)

target_link_libraries(Graphics-Base
    PRIVATE
    Common
    CoreBasic
    EngineBuildSetting
    PUBLIC
    Graphics-Base-Interface
)

InstallEngineLib(Graphics-Base)