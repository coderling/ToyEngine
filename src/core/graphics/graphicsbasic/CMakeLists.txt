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
)

add_library(Graphics-Base STATIC ${Includes} ${Sources} ${Interfaces})
set_common_target_properties(Graphics-Base)

target_link_libraries(Graphics-Base
    PRIVATE Common EngineBuildSetting
)

InstallEngineLib(Graphics-Base)