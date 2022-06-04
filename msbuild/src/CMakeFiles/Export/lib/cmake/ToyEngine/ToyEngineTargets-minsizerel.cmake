#----------------------------------------------------------------
# Generated CMake target import file for configuration "MinSizeRel".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "ToyEngine::Engine" for configuration "MinSizeRel"
set_property(TARGET ToyEngine::Engine APPEND PROPERTY IMPORTED_CONFIGURATIONS MINSIZEREL)
set_target_properties(ToyEngine::Engine PROPERTIES
  IMPORTED_IMPLIB_MINSIZEREL "${_IMPORT_PREFIX}/lib/ToyEngine.lib"
  IMPORTED_LOCATION_MINSIZEREL "${_IMPORT_PREFIX}/bin/ToyEngine.dll"
  )

list(APPEND _IMPORT_CHECK_TARGETS ToyEngine::Engine )
list(APPEND _IMPORT_CHECK_FILES_FOR_ToyEngine::Engine "${_IMPORT_PREFIX}/lib/ToyEngine.lib" "${_IMPORT_PREFIX}/bin/ToyEngine.dll" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
