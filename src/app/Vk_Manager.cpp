#include "./includes/Vk_Manager.hpp"

#include <GLFW/glfw3.h>
#include <vulkan/vulkan.h>
#include <vulkan/vulkan_beta.h>

#include <iostream>
#include <map>
#include <vector>

#include "./includes/Vk_Debugger.hpp"
#include "./includes/Vk_Device.hpp"
#include "./includes/Vk_Ext_Handler.hpp"
#include "./includes/Vk_Instance.hpp"

// #define NDEBUG

#ifdef NDEBUG
const bool enableValidationLayers = false;
#else
const bool enableValidationLayers = true;
#endif

const std::vector<const char*> instance_val_layers = {
    "VK_LAYER_KHRONOS_validation",
};

const std::vector<const char*> instance_exts = {
    VK_KHR_GET_PHYSICAL_DEVICE_PROPERTIES_2_EXTENSION_NAME,
};

const std::vector<const char*> device_exts = {
    VK_KHR_PORTABILITY_SUBSET_EXTENSION_NAME,
};

void Vk_Manager::init() {
    _ext_handler._check_instance_ext_support();
   // check_ext_support();
    // check_validation_layer_support();
    _instancer.init();
    _debugger.setup_debug_messenger(_instancer.get_instance(), enableValidationLayers);
    _device.init(_instancer.get_instance(), enableValidationLayers);
    _ext_handler._check_device_ext_support(_device.get_physical_device());
}

void Vk_Manager::clean() {
    _device.clean();
    _debugger.clean(_instancer.get_instance());
    _instancer.clean();
}

void Vk_Manager::check_ext_support() {
    // Enumeration for the amount of extensions available
    uint32_t extension_count = 0;
    vkEnumerateInstanceExtensionProperties(nullptr, &extension_count, nullptr);

    // Create a vector to hold the extension types and queries the extensions
    std::vector<VkExtensionProperties> extensions(extension_count);
    vkEnumerateInstanceExtensionProperties(nullptr, &extension_count, extensions.data());
    // Testing to see the vectors that are currently available
    // std::cout << "available extensions:\n " << std::endl;
    // for (auto ext : extensions) {
    //     std::cout << "- \t" << ext.extensionName << std::endl;
    // }
}

bool Vk_Manager::check_validation_layer_support() {
    // Enumerate layer count
    uint32_t layer_count;
    vkEnumerateInstanceLayerProperties(&layer_count, nullptr);

    // Enumerate available layers
    std::vector<VkLayerProperties> avail_layers(layer_count);
    vkEnumerateInstanceLayerProperties(&layer_count, avail_layers.data());

    for (const char* layer_name : instance_val_layers) {
        bool layer_found = false;

        for (const auto& layer_props : avail_layers) {
            if (strcmp(layer_name, layer_props.layerName) == 0) {
                layer_found = true;
                break;
            }
        }

        if (!layer_found) {
            return false;
        }
    }
    return true;
}

bool Vk_Manager::verify_ext_support() {
    return false;
}

std::vector<const char*> Vk_Manager::get_req_exts() {
    uint32_t glfw_ext_count = 0;
    const char** glfw_exts;
    glfw_exts = glfwGetRequiredInstanceExtensions(&glfw_ext_count);

    // std::vector<const char*> extensions(glfw_exts, glfw_exts + glfw_ext_count);
    std::vector<const char*> extensions = instance_exts;
    extensions.push_back(VK_KHR_PORTABILITY_ENUMERATION_EXTENSION_NAME);

    // Combine GLFW extensions with additional extensions
    std::vector<const char*> combined_extensions(glfw_exts, glfw_exts + glfw_ext_count);
    combined_extensions.insert(combined_extensions.end(), extensions.begin(), extensions.end());

    // If debugging is enabled, add the debug extension
    if (enable_validation_layers) {
        combined_extensions.push_back(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);
    }

    // For testing purposes - start
    // std::cout << "\nGetting all required extensions:" << std::endl;
    // std::cout << "----------------------" << std::endl;
    // for (auto& ext : combined_extensions) {
    //     std::cout << ext << std::endl;
    // }
    // std::cout << "----------------------" << std::endl;
    // For testing purposes - end

    return combined_extensions;
}

void Vk_Manager::get_device_vals() {
    uint32_t layer_count = 0;
    vkEnumerateDeviceLayerProperties(physical_device, &layer_count, nullptr);

    std::vector<VkLayerProperties> avail_layers(layer_count);
    vkEnumerateDeviceLayerProperties(physical_device, &layer_count, avail_layers.data());

    std::cout << "device layers:" << std::endl;
    for (auto layer : avail_layers) {
        std::cout << "+\t" << layer.layerName << std::endl;
    }
}