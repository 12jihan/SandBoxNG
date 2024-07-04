#pragma once

#include <vulkan/vulkan.h>
// #include <vulkan/vulkan_beta.h>

class Vk_Logical_Device {
   private:
    VkDevice _device = VK_NULL_HANDLE;
    VkPhysicalDevice _physical_device = VK_NULL_HANDLE;
    void _create_logical_device();

   public:
    void init(VkPhysicalDevice physical_device);
};