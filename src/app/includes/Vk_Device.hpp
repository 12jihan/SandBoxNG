#pragma once

#include <vulkan/vulkan.h>

#include <iostream>
#include <optional>
#include <vector>

#include "./Vk_Logical_Device.hpp"
#include "./Vk_Physical_Device.hpp"

struct QueueFamilyIndices {
    std::optional<uint32_t> graphics_family;
    std::optional<uint32_t> present_family;

    bool is_complete() {
        return graphics_family.has_value() && present_family.has_value();
    }
};

class Vk_Device {
   private:
    bool _enable_validation_layers = false;

    const std::vector<const char*> _validation_layers = {
        "VK_LAYER_KHRONOS_validation",
    };

    VkInstance _instance;
    Vk_Physical_Device _physical_device;
    Vk_Logical_Device _logical_device;

    std::vector<const char*> get_req_exts();
    bool _check_validation_layer_support();
    bool _verify_ext_support();
    void _get_device_validations();
    bool _verify_device_ext_support();

   public:
    void init(
        VkInstance instance,
        VkSurfaceKHR _surface,
        bool enabled_validation_layers);
    void clean();

    Vk_Physical_Device& get_physical_device();
    Vk_Logical_Device& get_logical_device();

    QueueFamilyIndices find_queue_families(VkPhysicalDevice physical_device);
    bool is_device_suitable(VkPhysicalDevice physical_device);
};