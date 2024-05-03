cmake_minimum_required(VERSION 3.10)
project(sandbox)
set(CMAKE_CXX_STANDARD 17)

# Find the GLFW library
find_package(GLFW3 REQUIRED)

# Find the Vulkan library
find_package(Vulkan REQUIRED)

# Include the GLFW header files
include_directories(${GLFW3_INCLUDE_DIR} ${Vulkan_INCLUDE_DIRS})

# Add your executables
add_executable(sandbox main.cpp)

# Link against GLFW
target_link_libraries(sandbox ${GLFW3_LIBRARY} ${Vulkan_LIBRARIES})