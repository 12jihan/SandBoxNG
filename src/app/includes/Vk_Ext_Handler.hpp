#pragma once

#include <vulkan/vulkan.h>

#include <vector>

class Vk_Ext_Handler {
   private:
    bool _enable_validation = false;
    std::vector<const char *> _instance_exts;
    std::vector<const char *> _device_exts;

   public:
    void init(VkPhysicalDevice physical_device, bool enable_validation);
    void _check_instance_ext_support();
    void _check_device_ext_support(VkPhysicalDevice physical_device);
    void add_ext(const char *ext_name);

    std::vector<const char *> _get_required_exts();
};