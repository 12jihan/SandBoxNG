#pragma once
#include <vulkan/vulkan.h>

#include <iostream>
#include <vector>

class VulkanInstance {
   public:
    VulkanInstance() = default;  // Ensure there's a constructor if not already defined
    void init();
    void clean();

   private:
    VkInstance instance;
    const std::vector<const char*> validation_layers = {"VK_LAYER_KHRONOS_validation"};
    void create_instance();
    void create_info(VkApplicationInfo& app_info);
    bool check_validation_layer();
    void check_req_ext_support();
    void check_ext_support();
};