add_subdirectory(base)

add_library(EnginePlatform INTERFACE)
target_link_libraries(EnginePlatform INTERFACE EnginePlatform-Basic)

if(TARGET_PLATFORM_WIN)
    add_subdirectory(windows)
    target_link_libraries(EnginePlatform INTERFACE EnginePlatform-windows)
endif()