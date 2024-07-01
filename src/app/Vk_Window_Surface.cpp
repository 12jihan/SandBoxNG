#include "./includes/Vk_Window_Surface.hpp"

#ifdef _WIN32
#define VK_USE_PLATFORM_WIN32_KHR
#define GLFW_EXPOSE_NATIVE_WIN32
#elif __APPLE__
#define VK_USE_PLATFORM_MACOS_MVK
#define GLFW_EXPOSE_NATIVE_COCOA
#elif __LINUX__
#define VK_USE_PLATFORM_XCB_KHR
#define GLFW_EXPOSE_NATIVE_X11
#endif

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include <GLFW/glfw3native.h>