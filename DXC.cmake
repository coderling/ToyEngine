if(WIN32)
    add_library(DXC SHARED IMPORTED GLOBAL)
    set_target_properties(DXC PROPERTIES
        INTERFACE_COMPILE_DEFINITIONS "USE_dxc"
        INTERFACE_INCLUDE_DIRECTORIES "${EXternalDIR}/dxc"
    )

    set_target_properties(DXC PROPERTIES IMPORTED_LOCATION "${EXternalDIR}/dxc/bin/x64/dxcompiler.dll")
    set_target_properties(DXC PROPERTIES IMPORTED_IMPLIB "${EXternalDIR}/dxc/lib/x64/dxcompiler.lib")
    set_target_properties(DXC PROPERTIES INTERFACE_LINK_LIBRARIES "${EXternalDIR}/dxc/lib/x64/dxcompiler.lib")
    set_target_properties(DXC PROPERTIES DXIL_PATH "${EXternalDIR}/dxc/bin/x64/dxil.dll")
endif()
