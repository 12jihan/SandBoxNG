#pragma once

#include <vulkan/vulkan.h>

#include <vector>

class Vk_Ext_Handler {
   private:
    std::vector<const char*> _instance_exts;
    std::vector<const char*> _device_exts;

   public:
    void _check_instance_ext_support();

    void _check_device_ext_support(VkPhysicalDevice physical_device);
};