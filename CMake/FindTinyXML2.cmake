# Findtinyxml2
# ------------
#
# Created by Félix Pognard
# Locate and configure tinyxml2
#
# Interface Targets
# ^^^^^^^^^^^^^^^^^
#   tinyxml2::tinyxml2
#
# Variables
# ^^^^^^^^^
#   tinyxml2_ROOT_DIR
#   tinyxml2_INCLUDE_DIR
#   tinyxml2_LIBRARIES

set(tinyxml2_INCLUDE_DIR ${tinyxml2_ROOT_DIR}/source)

find_library(tinyxml2_IMPORT_LIB_RELEASE
		   NAMES tinyxml2.lib
		   HINTS "${tinyxml2_ROOT_DIR}/x64-Release-Lib/")
mark_as_advanced(tinyxml2_IMPORT_LIB_RELEASE)

find_library(tinyxml2_IMPORT_LIB_DEBUG
		   NAMES tinyxml2.lib
		   HINTS "${tinyxml2_ROOT_DIR}/x64-Debug-Lib/")
mark_as_advanced(tinyxml2_IMPORT_LIB_DEBUG)


include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(tinyxml2 DEFAULT_MSG tinyxml2_ROOT_DIR tinyxml2_INCLUDE_DIR tinyxml2_IMPORT_LIB_RELEASE tinyxml2_IMPORT_LIB_DEBUG)