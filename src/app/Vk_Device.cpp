#include "./includes/Vk_Device.hpp"
#include <vulkan/vulkan.h>
#include <iostream>

// void Vk_Device::create_logical_device() {
//     QueueFamilyIndices indices = find_queue_family(physical_device);
// }

// Vk_Device::QueueFamilyIndices Vk_Device::find_queue_families(VkPhysicalDevice device) {
//     VulkanManager::QueueFamilyIndices indices;
//     uint32_t queue_family_count = 0;
//     vkGetPhysicalDeviceQueueFamilyProperties(device, &queue_family_count, nullptr);

//     std::vector<VkQueueFamilyProperties> queue_families(queue_family_count);
//     vkGetPhysicalDeviceQueueFamilyProperties(device, &queue_family_count, queue_families.data());
//     // Logic to find queue family indices to populate struct with
//     int i = 0;
//     for (const auto& queue_family : queue_families) {
//         if (queue_family.queueFlags & VK_QUEUE_GRAPHICS_BIT) {
//             indices.graphicsFamily = i;
//         }

//         if (indices.is_complete()) {
//             break;
//         }

//         i++;
//     }
//     return indices;
// }