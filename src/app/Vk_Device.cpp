#include "./includes/Vk_Device.hpp"

#include <vulkan/vulkan.h>
#include <vulkan/vulkan_beta.h>

#include <iostream>

// TODO: putting the validation and extension layers here for now
const std::vector<const char*> device_exts = {
    VK_KHR_PORTABILITY_SUBSET_EXTENSION_NAME,
};

const std::vector<const char*> instance_val_layers = {
    "VK_LAYER_KHRONOS_validation",
};

void Vk_Device::init(VkInstance instance, bool enabled_validation_layers) {
    _enable_validation_layers = enabled_validation_layers;
    _pick_physical_device(instance);
    _create_logical_device();
}

void Vk_Device::_pick_physical_device(VkInstance instance) {
    // Takes in the instance for use
    const VkInstance _instance = instance;

    // Count the devices that are available for use
    uint32_t device_count = 0;
    vkEnumeratePhysicalDevices(_instance, &device_count, nullptr);
    if (device_count == 0) throw std::runtime_error("failed to find GPUs with Vulkan support!");

    // Get the devices
    std::vector<VkPhysicalDevice> devices(device_count);
    vkEnumeratePhysicalDevices(_instance, &device_count, devices.data());

    for (const auto& device : devices) {
        VkPhysicalDeviceProperties device_props;
        VkPhysicalDeviceFeatures device_feats;
        vkGetPhysicalDeviceProperties(device, &device_props);
        vkGetPhysicalDeviceFeatures(device, &device_feats);

        if (_is_device_suitable(device)) {
            _physical_device = device;
            break;
        }
    }

    if (_physical_device == VK_NULL_HANDLE) {
        throw std::runtime_error("failed to find a suitable GPU!");
    }
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

bool Vk_Device::_is_device_suitable(VkPhysicalDevice physical_device) {
    Vk_Device::QueueFamilyIndices indices = _find_queue_families(physical_device);
    return indices.is_complete();
};

Vk_Device::QueueFamilyIndices Vk_Device::_find_queue_families(VkPhysicalDevice physical_device) {
    QueueFamilyIndices indices;

    uint32_t queue_family_count = 0;
    vkGetPhysicalDeviceQueueFamilyProperties(physical_device, &queue_family_count, nullptr);

    std::vector<VkQueueFamilyProperties> queue_families(queue_family_count);
    vkGetPhysicalDeviceQueueFamilyProperties(physical_device, &queue_family_count, queue_families.data());

    // Logic to find queue family indices to populate struct with
    int i = 0;
    for (const auto& queue_family : queue_families) {
        if (queue_family.queueFlags & VK_QUEUE_GRAPHICS_BIT) {
            indices.graphicsFamily = i;
        }

        if (indices.is_complete()) {
            break;
        }

        i++;
    }
    return indices;
};

VkDevice Vk_Device::get_logical_device() {
    return _device;
};

VkPhysicalDevice Vk_Device::get_physical_device() {
    return _physical_device;
};

void Vk_Device::_get_device_validations() {
    uint32_t layer_count = 0;
    vkEnumerateDeviceLayerProperties(_physical_device, &layer_count, nullptr);

    std::vector<VkLayerProperties> avail_layers(layer_count);
    vkEnumerateDeviceLayerProperties(_physical_device, &layer_count, avail_layers.data());

    std::cout << "|-------------------|" << std::endl;
    std::cout << "|   device layers:  |" << std::endl;
    std::cout << "|-------------------|" << std::endl;
    for (auto layer : avail_layers) {
        std::cout << "-\t" << layer.layerName << std::endl;
    }
    std::cout << "|-------------------|" << std::endl;
}

void Vk_Device::clean() {
    vkDestroyDevice(_device, nullptr);
}