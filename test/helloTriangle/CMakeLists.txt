add_executable(HelloTriangle test-hello-triangle.cpp "Scene.hpp")

target_link_libraries(HelloTriangle Engine Platform Graphics)

install(TARGETS HelloTriangle DESTINATION ${_Install_path})