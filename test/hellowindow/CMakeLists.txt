add_executable(HelloWindow test-hello-window.cpp)

target_link_libraries(HelloWindow Common Platform)

install(TARGETS HelloWindow DESTINATION ${_Install_path})
