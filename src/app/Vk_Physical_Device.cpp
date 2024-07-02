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
    // Loop through the devices and set
    for (const auto& device : devices) {
        VkPhysicalDeviceProperties device_props;
        VkPhysicalDeviceFeatures device_feats;
        std::cout << "|- " << device << std::endl;

        // vkGetPhysicalDeviceProperties(device, &device_props);
        // vkGetPhysicalDeviceFeatures(device, &device_feats);

        // if (_is_device_suitable()) {
        //     _physical_device = device;
        //     break;
        // }
    }
    std::cout << "|------------------|" << std::endl;
};

bool Vk_Physical_Device::_is_device_suitable() {
    return true;
};
