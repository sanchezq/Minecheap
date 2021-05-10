#.rst
# FindIrrklang
# ------------
#
# Created by Walter Gray.
# Locate and configure Irrklang
#
# Interface Targets
# ^^^^^^^^^^^^^^^^^
#   Irrklang::Irrklang
#
# Variables
# ^^^^^^^^^
#   Irrklang_ROOT_DIR
#   Irrklang_FOUND
#   Irrklang_INCLUDE_DIR
#   Irrklang_LIBRARY
#   Irrklang_IMPORT_LIB

find_path(Irrklang_ROOT_DIR
          NAMES include/irrKlang.h
          HINTS ${EXTERNAL_LIBRARY_DIR}
          PATH_SUFFIXES irrKlang-${Irrklang_FIND_VERSION}
                        irrKlang)

find_path(Irrklang_INCLUDE_DIR 
  NAMES irrKlang.h
  HINTS "${Irrklang_ROOT_DIR}/include")

if(MSVC)
  find_file(Irrklang_LIBRARY
            NAMES irrKlang.dll
            HINTS "${Irrklang_ROOT_DIR}/bin/winx64-visualStudio/")
  find_library(Irrklang_IMPORT_LIB
               NAMES irrKlang.lib
               HINTS "${Irrklang_ROOT_DIR}/lib/winx64-visualStudio/")
  mark_as_advanced(Irrklang_IMPORT_LIB)
endif()

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(Irrklang DEFAULT_MSG Irrklang_INCLUDE_DIR Irrklang_LIBRARY)
