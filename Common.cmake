function(set_common_target_properties TARGET)
	get_target_property(TARGET_TYPE ${TARGET} TYPE)
	set_target_properties(${TARGET} PROPERTIES
        CXX_STANDARD 20
        CXX_STANDARD_REQUIRED ON
    )
endfunction()

function(BuildShaders target_name)
    add_custom_target(${target_name})

    file(GLOB_RECURSE sources LIST_DIRECTORIES false "*.hlsl")
    message("shaders:" ${PROJECT_SOURCE_DIR} ${sources})
    set_source_files_properties(${sources} PROPERTIES ShaderType "")
endfunction()