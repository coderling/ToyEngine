add_library(Graphics OBJECT)
add_subdirectory(d3d12)

target_include_directories(Graphics
    PUBLIC       "${CMAKE_CURRENT_SOURCE_DIR}/interface")

target_link_libraries(Graphics ${d3d12_libs})
