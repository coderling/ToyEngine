add_executable(dll-test test-TimerInDll.cpp)
target_link_libraries(dll-test PRIVATE Common Graphics-D3D12)
SetTestCommonProperties(dll-test)