#include <vulkan/vulkan.h>
// #include <vulkan/vulkan_beta.h>

class Vk_Physical_Device {
   
   private:
    VkInstance _instance = VK_NULL_HANDLE;
    VkSurfaceKHR _surface = VK_NULL_HANDLE;
    VkPhysicalDevice _physical_device = VK_NULL_HANDLE;

    void _pick_physical_device();
    bool _is_device_suitable();

   public:
    void init(VkInstance instance);
};