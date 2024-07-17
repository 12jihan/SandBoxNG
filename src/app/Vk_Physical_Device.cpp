#include "./includes/Vk_Physical_Device.hpp"

#include <vulkan/vulkan.h>

#include <iostream>
#include <vector>

void Vk_Physical_Device::init(VkInstance instance) {
    _instance = instance;
    _pick_physical_device();
};

void Vk_Physical_Device::_pick_physical_device() {
    // Devices Count
    uint32_t _device_count = 0;
    vkEnumeratePhysicalDevices(_instance, &_device_count, nullptr);
    if (_device_count == 0) {
        throw std::runtime_error("Failed to find GPUs with Vulkan support!");
    }
    // Vector of devices
    std::vector<VkPhysicalDevice> devices(_device_count);
    vkEnumeratePhysicalDevices(_instance, &_device_count, devices.data());

    std::cout << "|------------------|" << std::endl;
    std::cout << "| Physical Devices |" << std::endl;
    std::cout << "|------------------|" << std::endl;

    // Loop through the available devices and set
    for (const auto& device : devices) {
        vkGetPhysicalDeviceProperties(device, &_properties);
        vkGetPhysicalDeviceFeatures(device, &_features);

        // Add further checks for suitablility here
        _physical_device = device;
        break;
    }
    std::cout << "|------------------|" << std::endl;
    if (_physical_device != VK_NULL_HANDLE) {
        std::cout << "|- physical device created!" << std::endl;
    }

    vkGetPhysicalDeviceQueueFamilyProperties(_physical_device, &_device_count, nullptr);
    _queue_family_properties.resize(_device_count);
    vkGetPhysicalDeviceQueueFamilyProperties(_physical_device, &_device_count, _queue_family_properties.data());
};

VkPhysicalDevice Vk_Physical_Device::get_physical_device() const {
    return _physical_device;
}

VkPhysicalDeviceProperties Vk_Physical_Device::get_properties() const {
    return _properties;
}

VkPhysicalDeviceFeatures Vk_Physical_Device::get_features() const {
    return _features;
}
std::vector<VkQueueFamilyProperties> Vk_Physical_Device::get_queue_family_properties() const {
    return _queue_family_properties;
}