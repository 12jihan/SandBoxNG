#include "./includes/VulkanManager.hpp"

#include <GLFW/glfw3.h>
#include <vulkan/vulkan.h>

#include <iostream>
#include <vector>

#ifdef NDEBUG
const bool enableValidationLayers = false;
#else
const bool enableValidationLayers = true;
#endif

// const std::vector<const char*> validation_layers = {"VK_LAYER_KHRONOS_validation"};

void VulkanManager::init() {
    std::cout << "~~~~~~ Vulkan Instance Being Created ~~~~~~" << std::endl;
    check_ext_support();
    check_validation_layer_support();
    create_instance();
}

void VulkanManager::create_instance() {
    if (!check_validation_layer_support()) {
        throw new std::runtime_error("Validation layers requested, but not available!");
    }
    _app_info();
    // Create Instance information
    _create_info();
}

void VulkanManager::clean() {
    std::cout << "Cleaning up Vulkan instance\n";
    vkDestroyInstance(instance, nullptr);
}

void VulkanManager::check_ext_support() {
    // Enumeration for the amount of extensions available
    uint32_t extension_count = 0;
    vkEnumerateInstanceExtensionProperties(nullptr, &extension_count, nullptr);

    // Create a vector to hold the extension types and queries the extensions
    std::vector<VkExtensionProperties> extensions(extension_count);
    vkEnumerateInstanceExtensionProperties(nullptr, &extension_count, extensions.data());

    // Output the available extensions
    std::cout << "Available Extensions:\n";
    for (const auto& extension : extensions) {
        std::cout << "\t - " << extension.extensionName << "\n";
    }
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
    std::cout << "Required Extension:" << std::endl;
    for (uint32_t i = 0; i < glfw_ext_count; i++) {
        req_exts.emplace_back(glfw_exts[i]);
        std::cout << "\n\t- " << req_exts[i];
    }

    // Setting up extensions for macos compatibility
    req_exts.emplace_back(VK_KHR_PORTABILITY_ENUMERATION_EXTENSION_NAME);
    create_info.flags |= VK_INSTANCE_CREATE_ENUMERATE_PORTABILITY_BIT_KHR;
    create_info.enabledExtensionCount = (uint32_t)req_exts.size();
    create_info.ppEnabledExtensionNames = req_exts.data();

    result = vkCreateInstance(&create_info, nullptr, &instance);
    if (result != VK_SUCCESS) {
        throw std::runtime_error("failed to create instance!\n\t- Error Code: " + std::to_string(result));
    } else {
        std::cout << "Instance Created:\n\t- Code: " + std::to_string(result) + "\n";
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
            std::cout << "Layer: " << layer_props.layerName << std::endl;
            if (strcmp(layer_name, layer_props.layerName) == 0) {
                layer_found = true;
                break;
            }
        }

        if (!layer_found) {
            return false;
        }
    }
    return false;
}

bool VulkanManager::verify_ext_support() {
    return false;
}