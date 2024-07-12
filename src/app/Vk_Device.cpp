#include "./includes/Vk_Device.hpp"
#include <vulkan/vulkan.h>
#include <vulkan/vulkan_beta.h>

#include <iostream>

#include "./includes/Vk_Logical_Device.hpp"

// TODO: putting the validation and extension layers here for now
const std::vector<const char*> device_exts = {
    VK_KHR_PORTABILITY_SUBSET_EXTENSION_NAME,
};

const std::vector<const char*> instance_val_layers = {
    "VK_LAYER_KHRONOS_validation",
};

void Vk_Device::init(VkInstance instance, VkSurfaceKHR _surface, bool enabled_validation_layers) {
    _enable_validation_layers = enabled_validation_layers;
    _phys_dev.init(instance);
    _log_dev.init(_phys_dev);
}

void Vk_Device::_create_logical_device() {
    QueueFamilyIndices _indices = _find_queue_families(_physical_device);

    // Specifying the queues to be created
    VkDeviceQueueCreateInfo queue_create_info{};
    queue_create_info.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
    queue_create_info.queueFamilyIndex = _indices.graphicsFamily.value();
    queue_create_info.queueCount = 1;

    // setting the queues priority using floating point numbers
    float queue_priority = 1.0f;
    queue_create_info.pQueuePriorities = &queue_priority;

    // specifying the device features
    VkPhysicalDeviceFeatures device_features{};

    // Create the logical device
    VkDeviceCreateInfo create_info{};
    create_info.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;

    create_info.pQueueCreateInfos = &queue_create_info;
    create_info.queueCreateInfoCount = 1;

    create_info.enabledExtensionCount = static_cast<uint32_t>(device_exts.size());
    create_info.ppEnabledExtensionNames = device_exts.data();

    create_info.pEnabledFeatures = &device_features;

    // const char* device_ext = "VK_KHR_portability_subset";

    // Testing a few things here:
    // get_device_exts();
    // get_device_vals();

    if (_enable_validation_layers) {
        create_info.enabledLayerCount = static_cast<uint32_t>(instance_val_layers.size());
        create_info.ppEnabledLayerNames = instance_val_layers.data();
    } else {
        create_info.enabledExtensionCount = 0;
    }

    if (vkCreateDevice(_physical_device, &create_info, nullptr, &_device) != VK_SUCCESS) {
        throw std::runtime_error("failed to create logical device!");
    }

    vkGetDeviceQueue(_device, _indices.graphicsFamily.value(), 0, &_graphics_queue);
}

void Vk_Device::clean() {
}