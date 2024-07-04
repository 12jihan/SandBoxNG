#include "./includes/Vk_Logical_Device.hpp"

#include <iostream>
#include <vulkan/vulkan.h>

void Vk_Logical_Device::_create_logical_device() {
    // Setup queuec reate info
    float queue_priority = 1.0f;
    VkDeviceQueueCreateInfo queue_create_info{};
};