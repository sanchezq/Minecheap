# FindFreeType
# ------------
#
# Created by Félix Pognard
# Locate and configure FreeType
#
# Interface Targets
# ^^^^^^^^^^^^^^^^^
#   FreeType::FreeType
#
# Variables
# ^^^^^^^^^
#   FreeType_ROOT_DIR
#   FreeType_FOUND
#   FreeType_INCLUDE_DIR
#   FreeType_LIBRARIES
#

find_path(FreeType_ROOT_DIR
          NAMES include/freetype/freetype.h
          PATH_SUFFIXES freetype-${FreeType_FIND_VERSION}
                        freetype)

set(FreeType_INCLUDE_DIR ${FreeType_ROOT_DIR}/include)

find_file(FreeType_LIBRARY_RELEASE
            NAMES freetype.dll
            HINTS "${FreeType_ROOT_DIR}/Release/")
find_library(FreeType_IMPORT_LIB_RELEASE
		   NAMES freetype.lib
		   HINTS "${FreeType_ROOT_DIR}/Release/")
mark_as_advanced(FreeType_IMPORT_LIB_RELEASE)

find_file(FreeType_LIBRARY_DEBUG
            NAMES freetype.dll
            HINTS "${FreeType_ROOT_DIR}/Debug/")
find_library(FreeType_IMPORT_LIB_DEBUG
		   NAMES freetype.lib
		   HINTS "${FreeType_ROOT_DIR}/Debug/")
mark_as_advanced(FreeType_IMPORT_LIB_DEBUG)


include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(FreeType DEFAULT_MSG FreeType_ROOT_DIR FreeType_INCLUDE_DIR FreeType_LIBRARY_RELEASE FreeType_LIBRARY_DEBUG FreeType_IMPORT_LIB_RELEASE FreeType_IMPORT_LIB_DEBUG)
