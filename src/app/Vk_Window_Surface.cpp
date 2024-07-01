#include "./includes/Vk_Window_Surface.hpp"

#include <iostream>

#ifdef __APPLE__
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include <vulkan/vulkan.h>
#include <vulkan/vulkan_beta.h>
#endif

void Vk_Window_Surface::init(VkInstance &instance, GLFWwindow *window) {
    _instance = instance;
    _window = window;
    _create_surface();
}

void Vk_Window_Surface::_create_surface() {
    VkSurfaceKHR surface;
    VkResult result = glfwCreateWindowSurface(_instance, _window, nullptr, &_surface);
    if (result != VK_SUCCESS) {
        throw std::runtime_error("failed to create window surface!");
    }
}

VkSurfaceKHR Vk_Window_Surface::get_surface() {
    return _surface;
}

void Vk_Window_Surface::clean() {
    if (_surface != VK_NULL_HANDLE) {
        vkDestroySurfaceKHR(_instance, _surface, nullptr);
    }
}