add_subdirectory(base)

if(TARGET_PLATFORM_WIN)
    add_subdirectory(windows)
    add_library(EnginePlatform ALIAS EnginePlatform-windows)
endif()