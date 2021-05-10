#APP
cmake_minimum_required(VERSION 3.16.3)

# Set app_SOURCE content
include(CMake/CMakeLists_app.cmake)

set(APP_TARGET app)

# Set vendor directories (third party librairies)
set(VENDOR_DIR ${PROJECT_SOURCE_DIR}/vendor)

# Set ImGUI
set(IMGUI_SOURCE ${VENDOR_DIR}/imgui)
file(GLOB IMGUI_FILES "${IMGUI_SOURCE}/*.cpp" "${IMGUI_SOURCE}/*.h")
add_executable(${APP_TARGET} ${app_SOURCES} ${IMGUI_FILES})

# Keep folder tree
source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${app_SOURCES})

# Set warning level to 4 and warning as error
if(MSVC)
	target_compile_options(${APP_TARGET} PRIVATE /W4 /WX)
endif()

# Activate Interprocedural optimization in release mode
include(CheckIPOSupported)
check_ipo_supported(RESULT ipo_supported OUTPUT output)
if(ipo_supported)
    message("--APP: IPO is supported!")
    set_property(TARGET ${APP_TARGET} PROPERTY INTERPROCEDURAL_OPTIMIZATION_RELEASE TRUE)
else()
	message(WARNING "IPO is not supported: ${output}")
endif()

# Add dictories path
set(APP_DIR ${PROJECT_SOURCE_DIR}/app/source)
set(VENDOR_DIR ${PROJECT_SOURCE_DIR}/vendor)
set(GLFW3_ROOT ${VENDOR_DIR}/glfw3)
set(GLFW_DLL ${GLFW3_ROOT}/lib/glfw3.dll)

set(GLM_DIR ${VENDOR_DIR}/glm)
set(IMGUI_SOURCE ${VENDOR_DIR}/imgui)
set(Irrklang_ROOT_DIR ${VENDOR_DIR}/irrKlang)
set(Assimp_ROOT_DIR ${VENDOR_DIR}/assimp)
set(FreeType_ROOT_DIR ${VENDOR_DIR}/FreeType2)
set(tinyxml2_ROOT_DIR ${VENDOR_DIR}/tinyxml2)




set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${PROJECT_SOURCE_DIR}/CMake/")
find_package(GLFW3 REQUIRED)
find_package(Irrklang REQUIRED)
find_package(Assimp REQUIRED)
find_package(FreeType REQUIRED)
find_package(tinyxml2 REQUIRED)

message(warning ${tinyxml2_IMPORT_LIB_RELEASE})

target_include_directories(${APP_TARGET}
							PRIVATE 
							${IMGUI_SOURCE}
							${APP_DIR}
							${APP_DIR}/Core
							${APP_DIR}/Gameplay
							${APP_DIR}/Gameplay/Components
							${APP_DIR}/Physics
							${APP_DIR}/States
							${APP_DIR}/Save
							${APP_DIR}/UI
							${APP_DIR}/WorldGeneration
							${VENDOR_DIR}/glfw3/include
							${GLFW3_INCLUDE_DIR}
							${GLM_DIR}
							${Irrklang_INCLUDE_DIR}
							${Assimp_INCLUDE_DIR}
							${FreeType_INCLUDE_DIR}
							${tinyxml2_INCLUDE_DIR}
							)
			
target_link_libraries(${APP_TARGET} PRIVATE general	${GLFW3_LIBRARY} 		
											general	libgfx 
											general	${Irrklang_IMPORT_LIB}
											optimized 	${FreeType_IMPORT_LIB_RELEASE} 
											optimized	${Assimp_IMPORT_LIB_RELEASE} 
											optimized	${tinyxml2_IMPORT_LIB_RELEASE}
											debug  	${FreeType_IMPORT_LIB_DEBUG} 
											debug	${Assimp_IMPORT_LIB_DEBUG} 
											debug	${tinyxml2_IMPORT_LIB_DEBUG})					

#copie the dll and deplace
add_custom_command(TARGET ${APP_TARGET} POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy_if_different ${GLFW_DLL} $<TARGET_FILE_DIR:${APP_TARGET}>)
add_custom_command(TARGET ${APP_TARGET} POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy_if_different ${Irrklang_LIBRARY} $<TARGET_FILE_DIR:${APP_TARGET}>)
add_custom_command(TARGET ${APP_TARGET} POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy_if_different ${Assimp_LIBRARY_DEBUG} $<TARGET_FILE_DIR:${APP_TARGET}>)
add_custom_command(TARGET ${APP_TARGET} POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy_if_different ${FreeType_LIBRARY_DEBUG} $<TARGET_FILE_DIR:${APP_TARGET}>)
add_custom_command(TARGET ${APP_TARGET} POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy_if_different ${Assimp_LIBRARY_RELEASE} $<TARGET_FILE_DIR:${APP_TARGET}>)
add_custom_command(TARGET ${APP_TARGET} POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy_if_different ${FreeType_LIBRARY_RELEASE} $<TARGET_FILE_DIR:${APP_TARGET}>)

#include auto-source regeneration script for this target if there if there is one
set(AUTO_REGEN_SCRIPT "${CMAKE_CURRENT_SOURCE_DIR}/_scripts/generate_cmake_app.sh")
if(EXISTS ${AUTO_REGEN_SCRIPT})
	target_sources(${APP_TARGET} PRIVATE ${AUTO_REGEN_SCRIPT})
endif()


#start the project in my target
set_property(DIRECTORY ${PROJECT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT ${APP_TARGET})

set_property(TARGET ${APP_TARGET} PROPERTY VS_DEBUGGER_WORKING_DIRECTORY "${PROJECT_SOURCE_DIR}")