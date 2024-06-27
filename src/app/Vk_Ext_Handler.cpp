#include "./includes/Vk_Ext_Handler.hpp"

#include <GLFW/glfw3.h>
#include <vulkan/vulkan.h>
#include <vulkan/vulkan_beta.h>

#include <iostream>
#include <vector>

#include "./tools/includes/Blk_Tools.hpp"

std::vector<const char *> exts = {
    VK_KHR_GET_PHYSICAL_DEVICE_PROPERTIES_2_EXTENSION_NAME,
};

void Vk_Ext_Handler::init(VkPhysicalDevice physical_device, bool enable_validation) {
    _enable_validation = enable_validation;
    if (_enable_validation) {
    }
};
// _check_instance_ext_support();
// _check_device_ext_support(physical_device);

// if (Blk_Tools::vector_contains(exts, ext_name)) {
//     std::cout << "Already exists in the list of extensions\n"
//               << std::endl;
//     std::cout << "Request will be ignored\n"
//               << std::endl;
// } else {
// }
void Vk_Ext_Handler::add_ext(const char *ext_name) {
    exts.push_back(ext_name);
};

void Vk_Ext_Handler::_check_instance_ext_support() {
    uint32_t _count = 0;
    vkEnumerateInstanceExtensionProperties(nullptr, &_count, nullptr);

    std::vector<VkExtensionProperties> avail_exts(_count);
    vkEnumerateInstanceExtensionProperties(nullptr, &_count, avail_exts.data());

    std::cout << "|---------------------|" << std::endl;
    std::cout << "| Instance Extensions |" << std::endl;
    std::cout << "|---------------------|" << std::endl;
    for (const auto &ext : avail_exts) {
        std::cout << "- " << ext.extensionName << std::endl;
    };
    std::cout << "|---------------------|\n"
              << std::endl;
};

void Vk_Ext_Handler::_check_device_ext_support(VkPhysicalDevice physical_device) {
    std::cout << "\nphysical device: " << physical_device << std::endl;
    uint32_t _count = 0;
    vkEnumerateDeviceExtensionProperties(physical_device, nullptr, &_count, nullptr);

    std::vector<VkExtensionProperties> avail_exts(_count);
    vkEnumerateDeviceExtensionProperties(physical_device, nullptr, &_count, avail_exts.data());

    std::cout << "|-------------------|" << std::endl;
    std::cout << "| Device Extensions |" << std::endl;
    std::cout << "|-------------------|" << std::endl;
    for (const auto &ext : avail_exts) {
        std::cout << "- " << ext.extensionName << std::endl;
    };
    std::cout << "|-------------------|" << std::endl;
};

std::vector<const char *> Vk_Ext_Handler::_get_required_exts() {
    uint32_t _glfw_ext_count = 0;
    const char **_glfw_exts;
    _glfw_exts = glfwGetRequiredInstanceExtensions(&_glfw_ext_count);

    std::vector<const char *> _exts = exts;
    if (_enable_validation) {
        _exts.push_back(VK_KHR_PORTABILITY_ENUMERATION_EXTENSION_NAME);
    };

    // Combine GLFW extensions with additional extensions
    std::vector<const char *> _combined_exts(_glfw_exts, _glfw_exts + _glfw_ext_count);
    _combined_exts.insert(_combined_exts.end(), _exts.begin(), _exts.end());

    // If debuggin is enabled, add the debug extension
    if (_enable_validation) _combined_exts.push_back(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);

    // Return the vector of extensions
    return _combined_exts;
}

const std::vector<const char *> &Vk_Ext_Handler::_get_ext_list() {
    return exts;
}