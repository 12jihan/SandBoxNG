#include "./includes/Vk_Debugger.hpp"

#include <vulkan/vulkan.h>

VkResult CreateDebugUtilsMessengerEXT(
    VkInstance _instance,
    const VkDebugUtilsMessengerCreateInfoEXT* pCreateInfo,
    const VkAllocationCallbacks* pAllocator,
    VkDebugUtilsMessengerEXT* pDebugMessenger) {
    auto func = (PFN_vkCreateDebugUtilsMessengerEXT)vkGetInstanceProcAddr(_instance, "vkCreateDebugUtilsMessengerEXT");
    if (func != nullptr) {
        return func(_instance, pCreateInfo, pAllocator, pDebugMessenger);
    } else {
        return VK_ERROR_EXTENSION_NOT_PRESENT;
    }
}

static void DestroyDebugUtilsMessengerEXT(
    VkInstance _instance,
    VkDebugUtilsMessengerEXT debug_messenger,
    const VkAllocationCallbacks* pAllocator) {
    auto func = (PFN_vkDestroyDebugUtilsMessengerEXT)vkGetInstanceProcAddr(_instance, "vkDestroyDebugUtilsMessengerEXT");
    if (func != nullptr) {
        func(_instance, debug_messenger, pAllocator);
    }
}

void Vk_Debugger::pop_debug_msgr_create_info(VkDebugUtilsMessengerCreateInfoEXT& msgr_create_info) {
    msgr_create_info = {};
    msgr_create_info.sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT;
    msgr_create_info.messageSeverity = VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT;
    msgr_create_info.messageType = VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT;
    msgr_create_info.pfnUserCallback = debug_callback;
}

void Vk_Debugger::setup_debug_msgr(VkInstance _instance, bool enable_validation) {
    if (!enable_validation) return;
    
    VkDebugUtilsMessengerCreateInfoEXT msgr_create_info{};
    pop_debug_msgr_create_info(msgr_create_info);

    if (CreateDebugUtilsMessengerEXT(_instance, &msgr_create_info, nullptr, &debug_messenger) != VK_SUCCESS) {
        throw std::runtime_error("failed to set up debug messenger!");
    }
}