function(set_common_target_properties TARGET)
    set_target_properties(${TARGET} PROPERTIES
        CXX_STANDARD 20
        CXX_STANDARD_REQUIRED ON
    )

    target_include_directories(${TARGET}
        PRIVATE
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/interface>
        PUBLIC
        $<INSTALL_INTERFACE:interface>
    )
endfunction()

function(BuildShaders target_name)
    add_custom_target(${target_name})

    file(GLOB_RECURSE sources LIST_DIRECTORIES false "*.hlsl")
    set_source_files_properties(${sources} PROPERTIES ShaderType "")
endfunction()

function(InstallEngineLib _target)
    get_target_property(TARGET_TYPE ${_target} TYPE)

    if(TARGET_TYPE STREQUAL STATIC_LIBRARY)
        list(APPEND ENGINE_STATIC_LIBS_LIST ${_target})
        set(ENGINE_STATIC_LIBS_LIST ${ENGINE_STATIC_LIBS_LIST} CACHE INTERNAL "common libraries installation list")
    else()
        message("unsupportd non static library install!")
    endif()
endfunction()

function(InstallCoombinedStaticLib final_lib_name libs_list target_name target_folder install_path)
    foreach(lib ${libs_list})
        list(APPEND full_path_libs $<TARGET_FILE:${lib}>)
    endforeach()

    message("all libs: " ${full_path_libs})
    add_custom_command(
        OUTPUT ${final_lib_name}

        # Delete all object files from current directory
        COMMAND ${CMAKE_COMMAND} -E remove "*${CMAKE_C_OUTPUT_EXTENSION}"
        DEPENDS ${libs_list}
        COMMENT "Combining libraries..."
    )

    # combined libs
    # unpack libs to ${final_lib_name}
    foreach(lib_target ${full_path_libs})
        add_custom_command(
            OUTPUT ${final_lib_name}
            COMMAND ${CMAKE_AR} -x ${lib_target}
            APPEND
        )
    endforeach()

    # pack object to final
    add_custom_command(
        OUTPUT ${final_lib_name}
        COMMAND ${CMAKE_AR} -crs ${final_lib_name} "*${CMAKE_C_OUTPUT_EXTENSION}"
        APPEND
    )

    # install
    add_custom_target(${target_name} ALL DEPENDS ${final_lib_name})
    install(
        FILES
        "${CMAKE_CURRENT_BINARY_DIR}/${final_lib_name}"
        DESTINATION
        ${install_path}
    )

    if(TARGET ${target_name})
        set_target_properties(${target_name} PROPERTIES
            FOLDER ${target_folder}
        )
    else()
        message("Unable to find librarian tool. Combined ${COMBINED_LIB_NAME} static library will not be produced.")
    endif()
endfunction()

function(SetTargetOutputName target_name out_name)
    foreach(d_config ${DEBUG_CONFIGS})
        set_target_properties(${target_name} PROPERTIES
            OUTPUT_NAME_${d_config} ${out_name}${DEBUG_DLL_SUFFIX}
        )
    endforeach()

    foreach(r_config ${RELEASE_CONFIGS})
        set_target_properties(${target_name} PROPERTIES
            OUTPUT_NAME_${r_config} ${out_name}${RELEASE_DLL_SUFFIX}
        )
    endforeach()
endfunction()