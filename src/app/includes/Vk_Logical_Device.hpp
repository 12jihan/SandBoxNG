#pragma once

#include <vulkan/vulkan.h>
// #include <vulkan/vulkan_beta.h>

class Vk_Logical_Device {
   private:
    VkInstance _instance;
    VkSurfaceKHR _surface;

    void _pick_physical_device(VkInstance instance, VkSurfaceKHR surface);
    void _is_device_suitable(VkPhysicalDevice physical_device, VkSurfaceKHR surface);

   public:
    void init(VkInstance instance, VkSurfaceKHR surface);
    void create_logical_device();
};