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
        if (_is_device_suitable(device) && (devices.size() == 1)) {
            _physical_device = device;
            break;
        } else {
            throw std::runtime_error("Handle finding multiple devices!");
        }
    }
    std::cout << "|------------------|" << std::endl;
    if (_physical_device != VK_NULL_HANDLE) {
        std::cout << "physical device created!" << std::endl;
    }
};

bool Vk_Physical_Device::_is_device_suitable(VkPhysicalDevice device) {
    // VkPhysicalDeviceProperties device_props;
    // VkPhysicalDeviceFeatures device_feats;

    // vkGetPhysicalDeviceProperties(device, &device_props);
    // vkGetPhysicalDeviceFeatures(device, &device_feats);

    // std::cout << "|- " << "device: " << device << std::endl;
    // std::cout << "|- " << "device name: " << device_props.deviceName << std::endl;
    // std::cout << "|- " << "api ver: " << device_props.apiVersion << std::endl;
    // std::cout << "|- " << "driver ver: " << device_props.driverVersion << std::endl;
    // std::cout << "|- " << "device id: " << device_props.deviceID << std::endl;
    // std::cout << "|- " << "device type: " << device_props.deviceType << std::endl;
    // std::cout << "|- " << "vendor id: " << device_props.vendorID << std::endl;
    // std::cout << "|- " << "geometry shader: " << (device_feats.geometryShader ? "true" : "false") << std::endl;

    // return device_props.deviceType == VK_PHYSICAL_DEVICE_TYPE_INTEGRATED_GPU;

    QueueFamilyIndices indices = _find_queue_families(device);

    return indices.is_complete();
};

VkPhysicalDevice Vk_Physical_Device::get_physical_device() {
    return _physical_device;
}

// Look over this but to see exactly what it's doing cuz I have no fucking idea.
Vk_Physical_Device::QueueFamilyIndices Vk_Physical_Device::_find_queue_families(VkPhysicalDevice device) {
    QueueFamilyIndices indices;
    uint32_t queue_family_count = 0;
    vkGetPhysicalDeviceQueueFamilyProperties(device, &queue_family_count, nullptr);

    std::vector<VkQueueFamilyProperties> queue_families(queue_family_count);
    vkGetPhysicalDeviceQueueFamilyProperties(device, &queue_family_count, queue_families.data());

    int i = 0;
    for (const auto& queue_family : queue_families) {
        if (queue_family.queueFlags & VK_QUEUE_GRAPHICS_BIT) {
            indices.graphics_family = i;
        }
        std::cout << "graphics family:" << indices.graphics_family.value() << std::endl;
        if (indices.is_complete()) {
            break;
        }

        i++;
    }
    return indices;
};