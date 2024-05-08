#include "./includes/VulkanInstance.hpp"

#include <GLFW/glfw3.h>
#include <vulkan/vulkan.h>

#include <iostream>
#include <vector>

#ifdef NDEBUG
const bool enableValidationLayers = false;
#else
const bool enableValidationLayers = true;
#endif

void VulkanInstance::init() {
    check_ext_support();
    create_instance();
}

void VulkanInstance::create_instance() {
    // Create application information
    VkApplicationInfo app_info{};
    app_info.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
    app_info.pApplicationName = "SandboxNG";
    app_info.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
    app_info.pEngineName = "Sandbox_NG_VK";
    app_info.engineVersion = VK_MAKE_VERSION(1, 0, 0);
    app_info.apiVersion = VK_API_VERSION_1_0;

    // Create Instance information
    VkInstanceCreateInfo create_info{};
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
    std::cout << "Required Extension: " << std::endl;
    for (uint32_t i = 0; i < glfw_ext_count; i++) {
        req_exts.emplace_back(glfw_exts[i]);
        std::cout << "\t- " << req_exts[i] << std::endl;
    }

    // Setting up extensions for macos compatibility
    req_exts.emplace_back(VK_KHR_PORTABILITY_ENUMERATION_EXTENSION_NAME);
    create_info.flags |= VK_INSTANCE_CREATE_ENUMERATE_PORTABILITY_BIT_KHR;
    create_info.enabledExtensionCount = (uint32_t)req_exts.size();
    create_info.ppEnabledExtensionNames = req_exts.data();

    VkResult result = vkCreateInstance(&create_info, nullptr, &instance);
    if (result != VK_SUCCESS) {
        throw std::runtime_error("failed to create instance!\n\t- Error Code: " + std::to_string(result));
    } else {
        std::cout << "Instance Created:\n\t- Code: " + std::to_string(result) << std::endl;
    }
}

void VulkanInstance::clean() {
    std::cout << "Cleaning up Vulkan instance" << std::endl;
    vkDestroyInstance(instance, nullptr);
}

void VulkanInstance::check_ext_support() {
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

void VulkanInstance::create_info(VkApplicationInfo& app_info) {
    VkInstanceCreateInfo create_info{};
    create_info.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
    create_info.pApplicationInfo = &app_info;
}

bool check_validation_layer() {
    uint32_t layer_count;
    vkEnumerateInstanceLayerProperties(&layer_count, nullptr);

    std::vector<VkLayerProperties> available_layers(layer_count);
    vkEnumerateInstanceLayerProperties(&layer_count, available_layers.data());

    // for (const char* layer_name : validation_layers) {
    //     bool layerFound = false;

    //     for (const auto& layer_props : available_layers) {
    //         if (strcmp(layer_name, layer_props.layerName) == 0) {
    //             layerFound = true;
    //             break;
    //         }
    //     }
    //     if (!layerFound) {
    //         return false;
    //     }
    // }
    return true;
};