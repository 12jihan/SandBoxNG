#include <vulkan/vulkan.h>

#include <iostream>
#include <optional>
// #include <vulkan/vulkan_beta.h>

class Vk_Physical_Device {
   private:
    struct QueueFamilyIndices {
        std::optional<uint32_t> graphics_family;
        // std::optional<uint32_t> present_family;

        bool is_complete() {
            // std::cout << "|- graphics family:" << graphics_family.value() << std::endl;
            std::cout << "|- graphics has value:" << graphics_family.has_value() << std::endl;

            // std::cout << "present family:" << present_family.value() << std::endl;
            // std::cout << "present has value:" << present_family.has_value() << std::endl;

            return graphics_family.has_value();
            //  && present_family.has_value();
        };
    };

    VkInstance _instance = VK_NULL_HANDLE;
    VkSurfaceKHR _surface = VK_NULL_HANDLE;
    VkPhysicalDevice _physical_device = VK_NULL_HANDLE;
    VkPhysicalDeviceProperties _properties;
    VkPhysicalDeviceProperties _features;

    void _pick_physical_device();
    bool _is_device_suitable(VkPhysicalDevice device);
    QueueFamilyIndices _find_queue_families(VkPhysicalDevice device);

   public:
    void init(VkInstance instance);
    VkPhysicalDevice get_physical_device();
};