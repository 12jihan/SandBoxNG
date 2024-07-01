#pragma once

#include <vulkan/vulkan.h>

#include <iostream>
#include <optional>
#include <vector>

class Vk_Device {
   private:
    const std::vector<const char*> _validation_layers = {
        "VK_LAYER_KHRONOS_validation",
    };
    bool _enable_validation_layers = false;
    VkPhysicalDevice _physical_device = VK_NULL_HANDLE;
    VkDevice _device;
    VkSurfaceKHR _surface;
    VkQueue _graphics_queue;

    struct QueueFamilyIndices {
        std::optional<uint32_t> graphicsFamily;
        std::optional<uint32_t> presentFamily;

        bool is_complete() {
            return graphicsFamily.has_value() && presentFamily.has_value();
        }
    };

    std::vector<const char*> get_req_exts();
    QueueFamilyIndices _find_queue_families(VkPhysicalDevice physical_device);

    bool _check_validation_layer_support();
    bool _verify_ext_support();
    bool _verify_device_ext_support();
    bool _is_device_suitable(VkPhysicalDevice physical_device);

    void _pick_physical_device(VkInstance instance);
    void _create_logical_device();
    void _get_device_validations();

   public:
    void init(
        VkInstance instance,
        VkSurfaceKHR _surface,
        bool enabled_validation_layers);

    VkDevice get_logical_device();

    VkPhysicalDevice get_physical_device();

    void clean();
};