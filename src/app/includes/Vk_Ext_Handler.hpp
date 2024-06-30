#pragma once

#include <vulkan/vulkan.h>

#include <vector>

class Vk_Ext_Handler {
   private:
    bool _enable_validation = false;
    std::vector<const char *> _instance_exts;
    std::vector<const char *> _device_exts;

   public:
    // Taking away this parameter for now
    // VkPhysicalDevice physical_device

    void init(bool enable_validation);
    void _check_instance_ext_support();
    void _check_device_ext_support(VkPhysicalDevice physical_device);
    void add_ext(const char *ext_name);
    const std::vector<const char *> &_get_ext_list();
    std::vector<const char *> _get_required_exts();
};