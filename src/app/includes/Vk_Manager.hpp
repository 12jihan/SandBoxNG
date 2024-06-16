#pragma once
#include <vulkan/vulkan.h>

#include <iostream>
#include <optional>
#include <vector>

#include "./Vk_Instance.hpp"
#include "./Vk_Debugger.hpp"

class Vk_Manager {
   public:
    void init();
    void clean();

   private:
    Vk_Debugger _debugger;
    struct QueueFamilyIndices {
        std::optional<uint32_t> graphicsFamily;

        bool is_complete() {
            return graphicsFamily.has_value();
        }
    };

    const std::vector<const char*> validation_layers = {
        "VK_LAYER_KHRONOS_validation",
    };

    Vk_Instance _inst;
    VkPhysicalDevice physical_device = VK_NULL_HANDLE;
    VkResult result = VK_SUCCESS;
    VkInstance instance;
    VkDebugUtilsMessengerEXT debugMessenger;
    VkQueue graphics_queue;
    VkDevice device;
    VkSurfaceKHR surface;

    VkApplicationInfo app_info;
    VkInstanceCreateInfo create_info;
    bool enable_validation_layers = true;

    void create_instance();
    void _app_info();
    void _create_info();
    void check_ext_support();
    void setup_debug_msgr();
    void pick_physical_device();
    void create_logical_device();

    int rate_device_suitability(VkPhysicalDevice device);

    bool check_validation_layer_support();
    bool verify_ext_support();
    bool verify_device_ext_support();
    bool is_device_suitable(VkPhysicalDevice device);

    // check if the device supports the required extensions and validation layers

    // Get the device's required extensions and validation layers
    void get_device_exts();
    void get_device_vals();

    std::vector<const char*> get_req_exts();

    QueueFamilyIndices find_queue_families(VkPhysicalDevice device);

    void pop_debug_msgr_create_info(VkDebugUtilsMessengerCreateInfoEXT& msgr_create_info);

    static VKAPI_ATTR VkBool32 VKAPI_CALL debug_callback(
        VkDebugUtilsMessageSeverityFlagBitsEXT msg_severity,
        VkDebugUtilsMessageTypeFlagsEXT msg_type,
        const VkDebugUtilsMessengerCallbackDataEXT* callback_data,
        void* user_data) {
        std::cerr << "Validation Layers: " << callback_data->pMessage << std::endl;

        return VK_FALSE;
    };

    VkResult CreateDebugUtilsMessengerEXT(
        VkInstance instance,
        const VkDebugUtilsMessengerCreateInfoEXT* pCreateInfo,
        const VkAllocationCallbacks* pAllocator,
        VkDebugUtilsMessengerEXT* pDebugMessenger) {
        auto func = (PFN_vkCreateDebugUtilsMessengerEXT)vkGetInstanceProcAddr(instance, "vkCreateDebugUtilsMessengerEXT");
        if (func != nullptr) {
            return func(instance, pCreateInfo, pAllocator, pDebugMessenger);
        } else {
            return VK_ERROR_EXTENSION_NOT_PRESENT;
        }
    };

    static void DestroyDebugUtilsMessengerEXT(
        VkInstance instance,
        VkDebugUtilsMessengerEXT debugMessenger,
        const VkAllocationCallbacks* pAllocator) {
        auto func = (PFN_vkDestroyDebugUtilsMessengerEXT)vkGetInstanceProcAddr(instance, "vkDestroyDebugUtilsMessengerEXT");
        if (func != nullptr) {
            func(instance, debugMessenger, pAllocator);
        }
    }
};