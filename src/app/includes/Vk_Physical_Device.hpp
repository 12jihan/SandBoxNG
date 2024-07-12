#include <vulkan/vulkan.h>

#include <iostream>
#include <optional>
// #include <vulkan/vulkan_beta.h>

class Vk_Physical_Device {
   private:
    struct QueueFamilyIndices {
        std::optional<uint32_t> graphics_family;

        bool is_complete() {
            return graphics_family.has_value();
        };
    };

    VkInstance _instance = VK_NULL_HANDLE;
    VkSurfaceKHR _surface = VK_NULL_HANDLE;
    VkPhysicalDevice _physical_device = VK_NULL_HANDLE;
    VkPhysicalDeviceProperties _properties;
    VkPhysicalDeviceProperties _features;

    void _pick_physical_device();
    bool _is_device_suitable(VkPhysicalDevice device);

   public:
    void init(VkInstance instance);
    VkPhysicalDevice get_physical_device();
    QueueFamilyIndices find_queue_families();
};