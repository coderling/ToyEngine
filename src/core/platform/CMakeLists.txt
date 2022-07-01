add_subdirectory(base)

add_library(CorePlatform INTERFACE)
target_link_libraries(CorePlatform INTERFACE PlatformBase)

if(TARGET_PLATFORM_WIN)
    add_subdirectory(windows)
endif()