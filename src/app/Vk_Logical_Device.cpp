#include "./includes/Vk_Logical_Device.hpp"

#include <vulkan/vulkan.h>

#include <iostream>

#include "./includes/Vk_Physical_Device.hpp"

void Vk_Logical_Device::_create_logical_device() {
    // Setup queuec reate info
    float queue_priority = 1.0f;
    VkDeviceQueueCreateInfo queue_create_info{};
};

void Vk_Logical_Device::init(Vk_Physical_Device physical_device_class) {
    _physical_device = physical_device_class.get_physical_device();
};