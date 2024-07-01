#pragma once

// #ifdef _WIN32
// #define VK_USE_PLATFORM_WIN32_KHR
// #define GLFW_EXPOSE_NATIVE_WIN32
// #include <GLFW/glfw3native.h>
// #elif __APPLE__
// #define VK_USE_PLATFORM_METAL_EXT
// #define GLFW_EXPOSE_NATIVE_COCOA
// #include <GLFW/glfw3native.h>
// #include <vulkan/vulkan_metal.h>
// #elif __LINUX__
// #define VK_USE_PLATFORM_XCB_KHR
// #define GLFW_EXPOSE_NATIVE_X11
// #include <GLFW/glfw3native.h>
// #endif

#ifdef __APPLE__
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include <vulkan/vulkan.h>
#include <vulkan/vulkan_beta.h>
#endif

class Vk_Window_Surface {
   private:
    VkSurfaceKHR _surface = VK_NULL_HANDLE;
    VkInstance _instance;
    GLFWwindow* _window;
    void _create_surface();

   public:
    void init(VkInstance& instance, GLFWwindow* window);
    void clean();
    VkSurfaceKHR get_surface();
};