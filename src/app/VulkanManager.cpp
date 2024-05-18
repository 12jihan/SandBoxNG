#include "./includes/VulkanManager.hpp"

#include <GLFW/glfw3.h>
#include <vulkan/vulkan.h>

#include <iostream>
#include <vector>

// #ifdef NDEBUG
// const bool enableValidationLayers = false;
// #else
// const bool enableValidationLayers = true;
// #endif

void VulkanManager::init() {
    check_ext_support();
    check_validation_layer_support();
    create_instance();
}

void VulkanManager::create_instance() {
    // Check to see if validation layers are available
    if (enable_validation_layers && !check_validation_layer_support()) {
        throw new std::runtime_error("Validation layers requested, but not available!");
    }
    // Create the application information
    _app_info();
    // Create Instance information
    _create_info();
}

void VulkanManager::clean() {
    vkDestroyInstance(instance, nullptr);
}

void VulkanManager::check_ext_support() {
    // Enumeration for the amount of extensions available
    uint32_t extension_count = 0;
    vkEnumerateInstanceExtensionProperties(nullptr, &extension_count, nullptr);

    // Create a vector to hold the extension types and queries the extensions
    std::vector<VkExtensionProperties> extensions(extension_count);
    vkEnumerateInstanceExtensionProperties(nullptr, &extension_count, extensions.data());
}

void VulkanManager::_app_info() {
    // Create application information
    app_info.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
    app_info.pApplicationName = "SandboxNG";
    app_info.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
    app_info.pEngineName = "Sandbox_NG_VK";
    app_info.engineVersion = VK_MAKE_VERSION(1, 0, 0);
    app_info.apiVersion = VK_API_VERSION_1_0;
}

void VulkanManager::_create_info() {
    create_info.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
    create_info.pApplicationInfo = &app_info;

    // Keep track of available extensions
    uint32_t glfw_ext_count = 0;
    const char** glfw_exts;
    glfw_exts = glfwGetRequiredInstanceExtensions(&glfw_ext_count);
    create_info.enabledExtensionCount = glfw_ext_count;
    create_info.ppEnabledExtensionNames = glfw_exts;

    // Compatibility required extensions
    create_info.enabledLayerCount = 0;
    std::vector<const char*> req_exts;

    for (uint32_t i = 0; i < glfw_ext_count; i++) {
        req_exts.emplace_back(glfw_exts[i]);
    }

    // Setting up extensions for macos compatibility
    req_exts.emplace_back(VK_KHR_PORTABILITY_ENUMERATION_EXTENSION_NAME);
    create_info.flags |= VK_INSTANCE_CREATE_ENUMERATE_PORTABILITY_BIT_KHR;
    create_info.enabledExtensionCount = (uint32_t)req_exts.size();
    create_info.ppEnabledExtensionNames = req_exts.data();

    result = vkCreateInstance(&create_info, nullptr, &instance);
    if (result != VK_SUCCESS) {
        throw std::runtime_error("failed to create instance!\n\t- Error Code: " + std::to_string(result));
    }
}

bool VulkanManager::check_validation_layer_support() {
    // Enumerate layer count
    uint32_t layer_count;
    vkEnumerateInstanceLayerProperties(&layer_count, nullptr);

    // Enumerate available layers
    std::vector<VkLayerProperties> avail_layers(layer_count);
    vkEnumerateInstanceLayerProperties(&layer_count, avail_layers.data());

    for (const char* layer_name : validation_layers) {
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

bool VulkanManager::verify_ext_support() {
    return false;
}

std::vector<const char*> VulkanManager::get_req_extensions() {
    uint32_t glfw_ext_count = 0;
    const char** glfw_ext;
    glfw_ext = glfwGetRequiredInstanceExtensions(&glfw_ext_count);

    std::vector<const char*> extensions(glfw_ext, glfw_ext + glfw_ext_count);

    return extensions;
}