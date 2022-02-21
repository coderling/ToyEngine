add_library(Platform OBJECT)

add_subdirectory(windows)

target_include_directories(Platform
PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")
