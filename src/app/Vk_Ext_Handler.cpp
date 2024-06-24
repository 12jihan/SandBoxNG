#include "./includes/Vk_Ext_Handler.hpp"

#include <vulkan/vulkan.h>
#include <vulkan/vulkan_beta.h>

#include <iostream>
#include <vector>

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
    std::cout << "physical device: " << physical_device << std::endl;
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