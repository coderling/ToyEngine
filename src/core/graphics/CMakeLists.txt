add_subdirectory(graphicsbasic)
add_subdirectory(d3d12)

add_library(EngineGraphics INTERFACE)
target_link_libraries(EngineGraphics INTERFACE Graphics-Base)

if(ENABLE_D3D12)
    target_link_libraries(EngineGraphics PRIVATE Graphics-D3D12)
endif()
