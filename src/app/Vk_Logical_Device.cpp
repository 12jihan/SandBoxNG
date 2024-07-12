#include "./includes/Vk_Logical_Device.hpp"

#include <iostream>
#include <vulkan/vulkan.h>
#include "Vk_Logical_Device.hpp"
#include "Vk_Physical_Device.hpp"

void Vk_Logical_Device::_create_logical_device() {
    // Setup queuec reate info
    float queue_priority = 1.0f;
    VkDeviceQueueCreateInfo queue_create_info{};
};

void Vk_Logical_Device::init(Vk_Physical_Device physical_device_class) {
    
}