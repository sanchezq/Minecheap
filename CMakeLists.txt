cmake_minimum_required(VERSION 3.16.3)

#Create C++ project
set(PROJECT_NAME "Minecheap")

#C++ Version
project(${PROJECT_NAME} C CXX)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Set output directory
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# Add the graphic library
add_subdirectory(libgfx/)
#Add application project
add_subdirectory(app/)

set_source_files_properties("${GLAD_SOURCE}" PROPERTIES LANGUAGE CXX)
target_compile_definitions(app PRIVATE "GLFW_INCLUDE_NONE")
