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
    VkResult result;
    VkInstance instance;
    VkApplicationInfo app_info{};
    VkInstanceCreateInfo create_info{};

    void create_instance();
    void _app_info();
    void _create_info(VkApplicationInfo& app_info);
    bool check_validation_layer();
    void check_req_ext_support();
    void check_ext_support();
};