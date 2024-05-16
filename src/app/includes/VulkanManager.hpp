#pragma once
#include <vulkan/vulkan.h>

#include <string>
#include <vector>

class VulkanManager {
   public:
    void init();
    void clean();

   private:
    VkResult result = VK_SUCCESS;
    VkInstance instance;
    VkApplicationInfo app_info;
    VkInstanceCreateInfo create_info;
    // std::vector<const char*> validation_layers;
    // std::vector<const char*> req_ext;

    void create_instance();
    void _app_info();
    void _create_info();
    void check_ext_support();
    bool check_validation_layer();
    bool check_validation_support();
};