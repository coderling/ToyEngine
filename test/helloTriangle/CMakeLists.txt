add_executable(HelloTriangle test-hello-triangle.cpp)

target_link_libraries(HelloTriangle Common Platform Graphics_D3D12)

install(TARGETS HelloTriangle DESTINATION ${_Install_path})