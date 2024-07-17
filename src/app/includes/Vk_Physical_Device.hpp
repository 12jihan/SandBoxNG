#pragma once

#include <vulkan/vulkan.h>

#include <iostream>
#include <optional>

class Vk_Physical_Device {
   private:
    VkInstance _instance;
    VkPhysicalDevice _physical_device;
    VkPhysicalDeviceProperties _properties;
    VkPhysicalDeviceFeatures _features;
    std::vector<VkQueueFamilyProperties> _queue_family_properties;

    void _pick_physical_device();

   public:
    void init(VkInstance instance);
    void clean();

    VkPhysicalDevice get_physical_device() const;
    VkPhysicalDeviceProperties get_properties() const;
    VkPhysicalDeviceFeatures get_features() const;
    std::vector<VkQueueFamilyProperties> get_queue_family_properties() const;
};