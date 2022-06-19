project(EngineLib LANGUAGES CXX)
include(GNUInstallDirs)

add_definitions(
    -DUNICODE
    -D_UNICODE
    -DNOMINMAX # 使用stl min max
)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_subdirectory(core)
add_subdirectory(engine)