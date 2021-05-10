#.rst
# FindAssimp
# ------------
#
# Created by Raffi Bedikian.
# Locate and configure Assimp
#
# Interface Targets
# ^^^^^^^^^^^^^^^^^
#   Assimp::Assimp
#
# Variables
# ^^^^^^^^^
#   Assimp_ROOT_DIR
#   Assimp_FOUND
#   Assimp_INCLUDE_DIR
#   Assimp_LIBRARIES
#

find_path(Assimp_ROOT_DIR
          NAMES include/assimp/scene.h
          PATH_SUFFIXES assimp-${Assimp_FIND_VERSION}
                        assimp)

set(Assimp_INCLUDE_DIR ${Assimp_ROOT_DIR}/include)

find_file(Assimp_LIBRARY_RELEASE
            NAMES assimp-vc142-mt.dll
            HINTS "${Assimp_ROOT_DIR}/Release/")
find_library(Assimp_IMPORT_LIB_RELEASE
		   NAMES assimp-vc142-mt.lib
		   HINTS "${Assimp_ROOT_DIR}/Release/")
mark_as_advanced(Assimp_IMPORT_LIB_RELEASE)
 
find_file(Assimp_LIBRARY_DEBUG
            NAMES assimp-vc142-mtd.dll
            HINTS "${Assimp_ROOT_DIR}/Debug/")
find_library(Assimp_IMPORT_LIB_DEBUG
		   NAMES assimp-vc142-mtd.lib
		   HINTS "${Assimp_ROOT_DIR}/Debug/")
mark_as_advanced(Assimp_IMPORT_LIB_DEBUG)


include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(Assimp DEFAULT_MSG Assimp_ROOT_DIR Assimp_INCLUDE_DIR Assimp_LIBRARY_RELEASE Assimp_LIBRARY_DEBUG Assimp_IMPORT_LIB_RELEASE Assimp_IMPORT_LIB_DEBUG)
