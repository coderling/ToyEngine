function(set_common_target_properties TARGET)
	get_target_property(TARGET_TYPE ${TARGET} TYPE)
	set_target_properties(${TARGET} PROPERTIES
        CXX_STANDARD 20
        CXX_STANDARD_REQUIRED ON
    )
endfunction()