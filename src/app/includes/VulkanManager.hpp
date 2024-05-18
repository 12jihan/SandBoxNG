#pragma once
#include <vulkan/vulkan.h>

#include <iostream>
#include <vector>

class VulkanManager {
   public:
    void init();
    void clean();

   private:
    const std::vector<const char*> validation_layers = {"VK_LAYER_KHRONOS_validation"};
    VkResult result = VK_SUCCESS;
    VkInstance instance;
    VkDebugUtilsMessengerEXT debugMessenger;

    VkApplicationInfo app_info;
    VkInstanceCreateInfo create_info;
    bool enable_validation_layers = true;

    void create_instance();
    void _app_info();
    void _create_info();
    void check_ext_support();
    bool check_validation_layer_support();
    bool verify_ext_support();
    void setup_debug_msgr();
    std::vector<const char*> get_req_exts();

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
    }

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