add_executable(HelloWindow test-hello-window.cpp)

target_link_libraries(HelloWindow PRIVATE Engine)

install(TARGETS HelloWindow DESTINATION ${_Install_path})
