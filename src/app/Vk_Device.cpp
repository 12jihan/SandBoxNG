#include "./includes/Vk_Device.hpp"

#include <vulkan/vulkan.h>
#include <vulkan/vulkan_beta.h>

#include <iostream>

#include "./includes/Vk_Logical_Device.hpp"
#include "./includes/Vk_Physical_Device.hpp"

// TODO: putting the validation and extension layers here for now
const std::vector<const char*> device_exts = {
    VK_KHR_PORTABILITY_SUBSET_EXTENSION_NAME,
};

const std::vector<const char*> instance_val_layers = {
    "VK_LAYER_KHRONOS_validation",
};

void Vk_Device::init(VkInstance instance, VkSurfaceKHR _surface, bool enabled_validation_layers) {
    _enable_validation_layers = enabled_validation_layers;
    _physical_device.init(instance);
    _logical_device.init(_physical_device);

    if (!is_device_suitable(_physical_device.get_physical_device())) {
        throw std::runtime_error("Failed to find a suitable GPU!");
    }
}

QueueFamilyIndices Vk_Device::find_queue_families(VkPhysicalDevice physical_device) {
    VkPhysicalDevice _device = physical_device;
    QueueFamilyIndices indices;
    uint32_t queue_family_count = 0;
    vkGetPhysicalDeviceQueueFamilyProperties(_device, &queue_family_count, nullptr);

    std::vector<VkQueueFamilyProperties> queue_families(queue_family_count);
    vkGetPhysicalDeviceQueueFamilyProperties(_device, &queue_family_count, queue_families.data());

    int i = 0;
    for (const auto& queue_family : queue_families) {
        if (queue_family.queueFlags & VK_QUEUE_GRAPHICS_BIT) {
            indices.graphics_family = i;
        }
        std::cout << "|- graphics family:" << indices.graphics_family.value() << std::endl;
        if (indices.is_complete()) {
            break;
        }

        i++;
    }

    return indices;
}

bool Vk_Device::is_device_suitable(VkPhysicalDevice physical_device) {
    VkPhysicalDevice _device = physical_device;

    VkPhysicalDeviceProperties device_props;
    VkPhysicalDeviceFeatures device_feats;

    vkGetPhysicalDeviceProperties(_device, &device_props);
    vkGetPhysicalDeviceFeatures(_device, &device_feats);

    std::cout << "|- " << "device: " << _device << std::endl;
    std::cout << "|- " << "device name: " << device_props.deviceName << std::endl;
    std::cout << "|- " << "api ver: " << device_props.apiVersion << std::endl;
    std::cout << "|- " << "driver ver: " << device_props.driverVersion << std::endl;
    std::cout << "|- " << "device id: " << device_props.deviceID << std::endl;
    std::cout << "|- " << "device type: " << device_props.deviceType << std::endl;
    std::cout << "|- " << "vendor id: " << device_props.vendorID << std::endl;
    std::cout << "|- " << "geometry shader: " << (device_feats.geometryShader ? "true" : "false") << std::endl;

    // return device_props.deviceType == VK_PHYSICAL_DEVICE_TYPE_INTEGRATED_GPU;

    QueueFamilyIndices indices = find_queue_families(_device);
    // std::cout << "|- indices boolean: " << indices.is_complete() << std::endl;
    return indices.is_complete();
}

void Vk_Device::clean() {
}