#pragma once
#include <vulkan/vulkan.h>

#include <iostream>

class VulkanInstance {
   public:
    VulkanInstance() = default;  // Ensure there's a constructor if not already defined
    void init();
    void clean();

    VkInstance instance = nullptr;     // Vulkan instance
   private:
    void create_instance();  // Declaration as a private member method
};