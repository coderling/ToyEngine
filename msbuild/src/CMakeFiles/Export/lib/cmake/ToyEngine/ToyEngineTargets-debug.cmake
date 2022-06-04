#----------------------------------------------------------------
# Generated CMake target import file for configuration "Debug".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "ToyEngine::Engine" for configuration "Debug"
set_property(TARGET ToyEngine::Engine APPEND PROPERTY IMPORTED_CONFIGURATIONS DEBUG)
set_target_properties(ToyEngine::Engine PROPERTIES
  IMPORTED_IMPLIB_DEBUG "${_IMPORT_PREFIX}/lib/ToyEngine_d.lib"
  IMPORTED_LOCATION_DEBUG "${_IMPORT_PREFIX}/bin/ToyEngine_d.dll"
  )

list(APPEND _IMPORT_CHECK_TARGETS ToyEngine::Engine )
list(APPEND _IMPORT_CHECK_FILES_FOR_ToyEngine::Engine "${_IMPORT_PREFIX}/lib/ToyEngine_d.lib" "${_IMPORT_PREFIX}/bin/ToyEngine_d.dll" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
