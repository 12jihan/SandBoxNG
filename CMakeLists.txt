cmake_minimum_required(VERSION 3.10)
project(sandbox)

#specify the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Configure Vulkan and GLFW
find_package(Vulkan REQUIRED)
find_package(glfw3 REQUIRED)

# Include directories for the project
include_directories(${Vulkan_INCLUDE_DIRS} include)

# Add source files
file(GLOB_RECURSE SOURCE_FILES "${CMAKE_SOURCE_DIR}/src/*.cpp")

# Add executable
add_executable(${PROJECT_NAME} ${SOURCE_FILES})

# Target include directories
target_include_directories(${PROJECT_NAME} PRIVATE ${GLFW_INCLUDE_DIRS})

# Link libraries
target_link_libraries(${PROJECT_NAME} ${Vulkan_LIBRARIES} glfw)

# Optionally set up shaders
file(GLOB_RECURSE SHADERS "shaders/*.frag" "shaders/*.vert")
source_group("Shaders" FILES ${SHADERS})

# Copy shader files to build directory
foreach(SHADER ${SHADERS})
    message(STATUS "Copying shader file: ${SHADER}")
    get_filename_component(SHADER_NAME ${SHADER} NAME)
    configure_file(${SHADER} ${CMAKE_BINARY_DIR}/shaders/${SHADER_NAME} COPYONLY)
endforeach()